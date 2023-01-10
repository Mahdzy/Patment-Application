#define _CRT_SECURE_NO_WARNINGS_GLOBALS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>


void getCardHolderNameTest(void) // Testing getCardHolderName
{
	struct Test_Cases
	{
		unsigned char Name_Case[40];
		unsigned char Expected_Result[40];
	};

	struct Test_Cases CardHolderName[7] = { {"Abdelrahman", "WRONG_NAME (less than 20 characters)"},
											{"Abdelrahman Almahdy Hasan Ahmed", "WRONG_NAME (more than 24 characters)"},
											{"Abdelrahman Almahdy Hasan#", "WRONG_NAME (Non_alphabetic)"},
											{"Mohammed Sayed2 Abdullah", "WRONG_NAME (Non_alphabetic)"},
											{"\0", "WRONG_NAME (Null)"},
											{"Abdelrahman Almahdy Hasan", "Correct_NAME"},
											{"Mohammed Ahmed Abdullah", "Correct_NAME"} };

	unsigned char invalid = 0; // To check name validity
	unsigned char strlength = 0; // To store number of alphabetic characters

	for (int Case = 0; Case < 7; Case++)
	{
		printf("\nTest Case %d\n", Case);
		printf("Input Data: %s\n", CardHolderName[Case].Name_Case);
		printf("Expected Result: %s\n", CardHolderName[Case].Expected_Result);

		_strupr(CardHolderName[Case].Name_Case); // Conversion upper letters to reduce comaprison operation

		for (int x = 0; x < (strlen(CardHolderName[Case].Name_Case)); x++)
		{

			if ((CardHolderName[Case].Name_Case[x] <= 'Z' && CardHolderName[Case].Name_Case[x] >= 'A') || CardHolderName[Case].Name_Case[x] == ' ')
			{
				if (CardHolderName[Case].Name_Case[x] != ' ')
				{
					strlength += 1;
				}
			}
			else
			{
				invalid = 1;
				break;
			}
		}

		if (invalid == 0)
		{
			if ((strlength > 19) && ((strlength < 25)))
			{
				printf("Actual Result: CARD_OK\n");
			}
			else printf("Actual Result: WRONG_NAME\n");
		}
		else printf("Actual Result: WRONG_NAME\n");

		invalid = 0; // Reset
		strlength = 0; // Reset
	}
}



int main(void)
{
	printf("Tester Name  : Abdelrahman Almahdy\n");
	printf("Function Name: getCardHolderName\n");

	getCardHolderNameTest();

	return 0;
}