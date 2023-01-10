#include <stdio.h>
#include <string.h>

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[29]; //Assuming the full name contains five names with 4 spaces
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_serverError_t
{
	SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;

typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;
typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_accountState_t
{
	RUNNING,
	BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
	float balance;
	EN_accountState_t state;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;


ST_cardData_t CardData[4] = { { "Abdelrahman Almahdy hasan1", "12345678912345677","12/23" },
								{ "Abdelrahman Almahdy hasan2", "12345678454451177","12/23" },
								{ "Abdelrahman Almahdy hasan3", "14725836914725835","12/23" } ,
								{ "Abdelrahman Almahdy hasan4", "10475211910475217","12/23" } };

ST_terminalData_t TerminalData[3] = { { 5000.0f, 20000.0f, "25/12/2022" },
										{ 5000.0f, 20000.0f, "25/12/2022" },
										{ 5000.0f, 20000.0f, "25/12/2022" }, };

uint8_t ExpectedResult[4][20] = { {"APPROVED"},{"FRAUD_CARD"},{"INSUFFECIENT_FUND"},{"STOLEN_CARD"} };


ST_accountsDB_t accountsDB[6] = { {90000.0f,	RUNNING, "12345678912345677"},
									{1000.0f, RUNNING, "14725836914725835"},
									{820000.0f, BLOCKED, "10475211910475217"} };

ST_accountsDB_t* AccountReference = NULL;

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountReference)
{
	for (uint32_t AccountCase = 0; AccountCase < 6; AccountCase++)
	{
		if (!strcmp(cardData->primaryAccountNumber, accountsDB[AccountCase].primaryAccountNumber))
		{
			AccountReference = &accountsDB[AccountCase];
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
	
void recieveTransactionDataTest(void)
{
	for (int Case = 0; Case < 4; Case++)
	{
		printf("\nTest Case %d\n", Case);
		printf("Input Data: %s\n", CardData[Case].primaryAccountNumber);
		printf("Expected Result: %s\n", ExpectedResult[Case]);

		if (isValidAccount(&CardData[Case], accountsDB) == SERVER_OK)
		{
			if (isBlockedAccount(AccountReference) == SERVER_OK)
			{
				if (isAmountAvailable(TerminalData, AccountReference) == SERVER_OK)
				{
					AccountReference->balance -= TerminalData->transAmount;
					printf("Actual Result: APPROVED\n");
				}
				else
				{
					printf("Actual Result: DECLINED_INSUFFECIENT_FUND\n");
				}
			}
			else
			{
				printf("Actual Result: DECLINED_STOLEN_CARD\n");
			}
		}
		else
		{
			printf("Actual Result: FRAUD_CARD\n");
		}
		AccountReference = NULL;
	}
}



int main()
{
	printf("Tester Name  : Abdelrahman Almahdy\n");
	printf("Function Name: recieveTransactionData\n");
	recieveTransactionDataTest();


	return 0;
}