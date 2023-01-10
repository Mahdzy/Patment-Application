#include <stdio.h>
#include <string.h>

typedef unsigned char uint8_t;
typedef struct ST_cardData_t
{
	uint8_t primaryAccountNumber[20];
	uint8_t ExpectedResult[20];
}ST_cardData_t;

ST_cardData_t CardData[5] = { { "12345678912345677", "FOUND"},
								{ "11409876513216541", "NOT FOUND"},
								{ "25268269252682690", "FOUND"},
								{ "11409855112165423", "NOT FOUND"},
								{ "10475211910475217", "FOUND"} };

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

ST_accountsDB_t accountsDB[255] = { {7000.0f,	RUNNING, "25268269252682690"},
									{90000.0f,	RUNNING, "12345678912345677"},
									{1000.0f, RUNNING, "14725836914725835"},
									{500.0f,	RUNNING, "78945612378945618"},
									{90100.0f,	BLOCKED, "10993655911099363"},
									{820000.0f, BLOCKED, "10475211910475217"} };

ST_accountsDB_t* AccountReference = NULL;

void isValidAccountTest(void)
{
	for (int Case = 0; Case < 5; Case++)
	{
		printf("\nTest Case %d\n", Case);
		printf("Input Data: %s\n", CardData[Case].primaryAccountNumber);
		printf("Expected Result: %s\n", CardData[Case].ExpectedResult);

		for (int AccountIndex = 0; AccountIndex < 6; AccountIndex++)
		{
			if (!strcmp(CardData[Case].primaryAccountNumber, accountsDB[AccountIndex].primaryAccountNumber))
			{
				AccountReference = &accountsDB[AccountIndex];
				break;
			}
		}

		if (AccountReference != NULL)
		{
			printf("Actual Result: Account Found\n");
		}
		else
		{
			printf("Actual Result: Account Not Found\n");
		}

		AccountReference = NULL;
	}

}

int main()
{
	printf("Tester Name  : Abdelrahman Almahdy\n");
	printf("Function Name: isValidAccount\n");
	isValidAccountTest();

	return 0;
}