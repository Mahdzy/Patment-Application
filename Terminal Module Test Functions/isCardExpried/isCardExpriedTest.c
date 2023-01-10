#include <stdio.h>
#include <string.h>


void isCardExpriedTest(void)
{
	struct Test_Cases
	{
		unsigned char cardExpirationDate[10];
		unsigned char Expected_Result[15];
	};

	struct Test_Cases ExpDate_Test[3] = {	{"12/50", "Valid_Date"},
											{"09/23", "Valid_Date"},
											{"05/11", "EXPIRED_CARD"} };

	const unsigned int conv_const = '1' - 1; // Conervts int to char type
	int Current_Year, Current_Month, Exp_Year, Exp_Month;
	unsigned char transactionDate[10] = {"24/09/2023"};

	Current_Year = 10 * (transactionDate[8] - conv_const) + (transactionDate[9] - conv_const);
	Current_Month = 10 * (transactionDate[3] - conv_const) + (transactionDate[4] - conv_const);
	

	for (int Case = 0; Case < 3; Case++)
	{
		Exp_Year = 10 * (ExpDate_Test[Case].cardExpirationDate[3] - conv_const) + (ExpDate_Test[Case].cardExpirationDate[4] - conv_const);
		Exp_Month = 10 * (ExpDate_Test[Case].cardExpirationDate[0] - conv_const) + (ExpDate_Test[Case].cardExpirationDate[1] - conv_const);
		
		printf("\nTest Case %d\n", Case);
		printf("Current Date %d/%d\n", Current_Month, Current_Year);
		printf("Expiration Date: %d/%d\n", Exp_Month, Exp_Year);
		printf("Expected Result: %s\n", ExpDate_Test[Case].Expected_Result);

		if (Exp_Year > Current_Year)
		{
			printf("Actual Result: TERMINAL_OK\n");
		}
		else if (Exp_Year == Current_Year)
		{
			if (Exp_Month >= Current_Month)
			{
				printf("Actual Result: TERMINAL_OK\n");
			}
			else
			{
				printf("Actual Result: EXPIRED_CARD\n");
			}
		}
		else
		{
			printf("Actual Result: EXPIRED_CARD\n");
		}
	}
	Exp_Year = 0;
	Exp_Month = 0;
}

int main(void)
{
	printf("Tester Name  : Abdelrahman Almahdy\n");
	printf("Function Name: isCardExpried\n");
	
	isCardExpriedTest();

	return 0;
}