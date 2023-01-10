#include <stdio.h>
#include <string.h>

typedef unsigned char uint8_t;
typedef struct ST_cardData_t
{
	uint8_t primaryAccountNumber[20];
	uint8_t ExpectedResult[20];
}ST_cardData_t;

ST_cardData_t CardData[4] = { { "12345678912345677", "RUNNING"},
								{ "10993655911099363", "BLOCKED"},
								{ "25268269252682690", "RUNNING"},
								{ "10475211910475217", "BLOCKED"} };

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

ST_accountsDB_t accountsDB[6] = { {7000.0f,	RUNNING, "25268269252682690"},
									{90000.0f,	RUNNING, "12345678912345677"},
									{1000.0f, RUNNING, "14725836914725835"},
									{500.0f,	RUNNING, "78945612378945618"},
									{90100.0f,	BLOCKED, "10993655911099363"},
									{820000.0f, BLOCKED, "10475211910475217"} };

ST_accountsDB_t* AccountReference = NULL;

void isBlockedAccounttest(void)
{
	for (int Case = 0; Case < 4; Case++)
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

		if (AccountReference->state == RUNNING) {
			printf("Actual Result: Account RUNNING\n");
		}
		else
		{
			printf("Actual Result: Account BLOCKED\n");
		}

		AccountReference = NULL;
	}
}

int main()
{
	printf("Tester Name  : Abdelrahman Almahdy\n");
	printf("Function Name: isBlockedAccount\n");
	isBlockedAccounttest();

	return 0;
}