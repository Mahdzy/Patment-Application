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

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef struct ST_accountsDB_t
{
	float balance;
	EN_accountState_t state;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;


ST_transaction_t AccountsTrans = { { "Abdelrahman Almahdy hasan", "12345678912345677","12/23"},{ 5000.0f, 20000.0f, "25/12/2022"},{APPROVED},{111000} };



void listSavedTransactionstest(void)
{
	printf("\n#########################\n");
	printf("Transaction Sequence Number: %d\n", AccountsTrans.transactionSequenceNumber);
	printf("Transaction Date: %s\n", AccountsTrans.terminalData.transactionDate);
	printf("Transaction Amount: %.2f\n", AccountsTrans.terminalData.transAmount);
	switch (AccountsTrans.transState)
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
	}
	printf("Terminal Max Amount: %.2f\n", AccountsTrans.terminalData.maxTransAmount);
	printf("Cardholder Name: %s\n", AccountsTrans.cardHolderData.cardHolderName);
	printf("Primary Account Number: %s\n", AccountsTrans.cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date: %s\n", AccountsTrans.cardHolderData.cardExpirationDate);
	printf("#########################\n");

}





int main()
{
	printf("Tester Name  : Abdelrahman Almahdy\n");
	printf("Function Name: listSavedTransactions\n");
	listSavedTransactionstest();
	

	return 0;
}