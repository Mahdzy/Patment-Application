#include <stdio.h>
#include <string.h>


void getCardExpiryDateTest(void)
{
	struct Test_Cases
	{
		unsigned char EXP_Date[10];
		unsigned char Expected_Result[40];
	};

	struct Test_Cases Date_Test[8] = {		{"13/50", "WRONG_EXP_DATE (Invalid Month)"},
											{"05/11", "WRONG_EXP_DATE (Past Year)"},
											{"11-23", "WRONG_EXP_DATE (Wrong Format)"},
											{"12/2022", "WRONG_EXP_DATE (more than 5 characters)"},
											{"12/2", "WRONG_EXP_DATE (less than 5 characters)"},
											{"\0", "WRONG_EXP_DATE (Null)"},
											{"05/40", "Correct_Date"},
											{"10/23", "Correct_Date"} };

	for (int Case = 0; Case < 8; Case++)
	{
		printf("\nTest Case %d\n", Case);
		printf("Input Data: %s\n", Date_Test[Case].EXP_Date);
		printf("Expected Result: %s\n", Date_Test[Case].Expected_Result);

		if (strlen(Date_Test[Case].EXP_Date) == 5) // To check String length (5 characters)
		{
			if (Date_Test[Case].EXP_Date[2] == '/') // Chech proper format
			{
				if (((Date_Test[Case].EXP_Date[0] == '0') && (Date_Test[Case].EXP_Date[1] > '0' && Date_Test[Case].EXP_Date[1] <= '9')) || ((Date_Test[Case].EXP_Date[0] == '1') && (Date_Test[Case].EXP_Date[1] >= '0' && Date_Test[Case].EXP_Date[1] <= '2'))) //Check if 1 <= month <= 12
				{
					if (((Date_Test[Case].EXP_Date[3] == '2') && (Date_Test[Case].EXP_Date[4] > '1' && Date_Test[Case].EXP_Date[4] <= '9')) || ((Date_Test[Case].EXP_Date[3] >= '3' && Date_Test[Case].EXP_Date[1] <= '9') && (Date_Test[Case].EXP_Date[1] >= '0' && Date_Test[Case].EXP_Date[1] <= '9'))) // Check if 22 <= Year <= 99
					{
						printf("Actual Result: CARD_OK\n");
					}
					else printf("Actual Result: WRONG_EXP_DATE\n");
				}
				else printf("Actual Result: WRONG_EXP_DATE\n");
			}
			else printf("Actual Result: WRONG_EXP_DATE\n");
		}
		else printf("Actual Result: WRONG_EXP_DATE\n");
	}
}


int main(void)
{
	printf("Tester Name  : Abdelrahman Almahdy\n");
	printf("Function Name: getCardExpiryDateTest\n");

	getCardExpiryDateTest();

	return 0;
}