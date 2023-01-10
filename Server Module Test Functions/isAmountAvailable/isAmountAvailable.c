#include <stdio.h>
#include <string.h>

typedef unsigned char uint8_t;
typedef struct ST_cardData_t
{
	uint8_t primaryAccountNumber[20];
	uint8_t ExpectedResult[20];
	float TransactionAmount;
}ST_cardData_t;

ST_cardData_t CardData[4] = { { "12345678912345677", "OK", 5000.0f},
								{ "14725836914725835", "LOW BALANCE",2000.0f },
								{ "25268269252682690", "OK", 7000.0f},
								{ "78945612378945618", "LOW BALANCE", 1000.0f} };

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

ST_accountsDB_t accountsDB[6] = { {90000.0f,	RUNNING, "12345678912345677"},
									{1000.0f, RUNNING, "14725836914725835"},
								{7000.0f,	RUNNING, "25268269252682690"},
									{500.0f,	RUNNING, "78945612378945618"} };

ST_accountsDB_t* AccountReference = NULL;

void isAmountAvailabletest(void)
{
	for (int Case = 0; Case < 4; Case++)
	{
		printf("\nTest Case %d\n", Case);
		printf("Input Data: %.2f\n", CardData[Case].TransactionAmount);
		printf("Available Balance: %.2f\n", accountsDB[Case].balance);
		printf("Expected Result: %s\n", CardData[Case].ExpectedResult);

		for (int AccountIndex = 0; AccountIndex < 6; AccountIndex++)
		{
			if (!strcmp(CardData[Case].primaryAccountNumber, accountsDB[AccountIndex].primaryAccountNumber))
			{
				AccountReference = &accountsDB[AccountIndex];
				break;
			}
		}

		if (CardData[Case].TransactionAmount <= AccountReference->balance)
		{
			printf("Actual Result: Transaction OK\n");
		}
		else
		{
			printf("Actual Result: LOW BALANCE\n");
		}

		AccountReference = NULL;
	}
}

int main()
{
	printf("Tester Name  : Abdelrahman Almahdy\n");
	printf("Function Name: isAmountAvailable\n");
	isAmountAvailabletest();

	return 0;
}