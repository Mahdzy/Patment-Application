#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"

ST_accountsDB_t accountsDB[255] = { {7000.0f,	RUNNING, "25268269252682690"},
									{90000.0f,	RUNNING, "12345678912345677"},
									{1000.0f, RUNNING, "14725836914725835"},
									{500.0f,	RUNNING, "78945612378945618"},
									{90100.0f,	BLOCKED, "10993655911099363"},
									{820000.0f, BLOCKED, "10475211910475217"} };
extern ST_accountsDB_t* AccountsDBPtr = &accountsDB;

ST_transaction_t AccountsTrans[255] = { 0 };
extern ST_transaction_t* AccountsTransPtr = AccountsTrans;

int FirstEmpty = -1; // Stores the first empty place in transactions database
EN_transState_t TransactionState = -1; // Stores Transaction State to be globally used

extern ST_accountsDB_t* AccountReference = NULL;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if (isValidAccount(CardDataPtr, AccountsDBPtr) == SERVER_OK)
	{
		if (isBlockedAccount(AccountReference) == SERVER_OK)
		{
			if (isAmountAvailable(TerminalDataPtr, AccountReference) == SERVER_OK)
			{
				AccountReference->balance -= TerminalDataPtr->transAmount;
				return TransactionState = APPROVED;
			}
			else
			{
				return TransactionState = DECLINED_INSUFFECIENT_FUND;
			}
		}
		else
		{
			return TransactionState = DECLINED_STOLEN_CARD;
		}
	}
	else
	{
		return TransactionState = FRAUD_CARD;
	}
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountReference)
{
	for (uint32_t AccountIndex = 0; AccountIndex < 6; AccountIndex++)
	{
		if (!strcmp(cardData->primaryAccountNumber, AccountsDBPtr[AccountIndex].primaryAccountNumber))
		{
			AccountReference = &accountsDB[AccountIndex];
			break;
		}
	}

	if (AccountReference != NULL)
	{
		return SERVER_OK;
	}
	else
	{
		return ACCOUNT_NOT_FOUND;
	}
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountReference)
{
	if (accountReference->state == RUNNING)
	{
		return SERVER_OK;
	}
	else
	{
		return BLOCKED_ACCOUNT;
	}
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountReference)
{
	if (termData->transAmount <= accountReference->balance)
	{
		return SERVER_OK;
	}
	else
	{
		return LOW_BALANCE;
	}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	if (FirstEmpty < 256 || FirstEmpty == -1)
	{
		uint8_t Print = 'N'; // Choose to print Transaction Data or no

		for (uint8_t Index = 0; Index < 255; Index++)
		{
			if (transData[Index].transactionSequenceNumber == 0)
			{
				FirstEmpty = Index;
				break;
			}
		}

		/* Storing Card Data */
		strcpy_s(transData[FirstEmpty].cardHolderData.cardHolderName, sizeof(CardDataPtr->cardHolderName), CardDataPtr->cardHolderName);
		strcpy_s(transData[FirstEmpty].cardHolderData.primaryAccountNumber, sizeof(CardDataPtr->primaryAccountNumber), CardDataPtr->primaryAccountNumber);
		strcpy_s(transData[FirstEmpty].cardHolderData.cardExpirationDate, sizeof(CardDataPtr->cardExpirationDate), CardDataPtr->cardExpirationDate);

		/* Storing Terminal Data */
		transData[FirstEmpty].terminalData.transAmount = TerminalDataPtr->transAmount;
		transData[FirstEmpty].terminalData.maxTransAmount = TerminalDataPtr->maxTransAmount;
		strcpy_s(transData[FirstEmpty].terminalData.transactionDate, sizeof(TerminalDataPtr->transactionDate), TerminalDataPtr->transactionDate);

		/* Storing Transactions State */
		transData[FirstEmpty].transState = TransactionState;
		transData[FirstEmpty].transactionSequenceNumber = 111000 + FirstEmpty;

		printf("\nDo You Want to print Transaction Data? (Y/N)\n");
		Print = getch();
		{
			if ((Print == 'Y') || (Print == 'y'))
			{
				listSavedTransactions();
			}
		}
		return SERVER_OK;
	}
	else
	{
		return INTERNAL_SERVER_ERROR;
	}

}

void listSavedTransactions(void)
{
	if (FirstEmpty != -1)
	{
		for (uint8_t Index = 0; Index < FirstEmpty + 1; Index++)
		{
			printf("\n#########################\n");
			printf("Transaction Sequence Number: %d\n", AccountsTransPtr[Index].transactionSequenceNumber);
			printf("Transaction Date: %s\n", AccountsTransPtr[Index].terminalData.transactionDate);
			printf("Transaction Amount: %.2f\n", AccountsTransPtr[Index].terminalData.transAmount);
			switch (AccountsTransPtr[Index].transState)
			{
			case 0:
				printf("Transaction State: APPROVED\n");
				break;
			case 1:
				printf("Transaction State: DECLINED_INSUFFECIENT_FUND\n");
				break;
			case 2:
				printf("Transaction State: DECLINED_STOLEN_CARD\n");
				break;
			case 3:
				printf("Transaction State: FRAUD_CARD\n");
				break;
			case 4:
				printf("Transaction State: INTERNAL_SERVER_ERROR\n");
				break;
			default:
				if (isBelowMaxAmount(TerminalDataPtr) == EXCEED_MAX_AMOUNT)
				{
					printf("Transaction State: EXCEED_MAX_AMOUNT\n");
				}
				break;
			}
			printf("Terminal Max Amount: %.2f\n", AccountsTransPtr[Index].terminalData.maxTransAmount);
			printf("Cardholder Name: %s", AccountsTransPtr[Index].cardHolderData.cardHolderName);
			printf("Primary Account Number: %s\n", AccountsTransPtr[Index].cardHolderData.primaryAccountNumber);
			printf("Card Expiration Date: %s\n", AccountsTransPtr[Index].cardHolderData.cardExpirationDate);
		}

		printf("#########################\n");
	}
}
