#include <stdio.h>
#include <string.h>

void getCardPANTest(void)
{
	struct Test_Cases
	{
		unsigned char PAN_No[25];
		unsigned char Expected_Result[40];
	};

	struct Test_Cases PAN_Test[6] = {	{"3652149885632145#8", "WRONG_PAN (Non_Numeric)"},							
										{"1526347916498923154612", "WRONG_PAN (more than 19 characters)"},
										{"567837194682", "WRONG_PAN (less than 16 character)"},
										{"\0", "WRONG_PAN (Null)"},
										{"2315947873634955", "Correct_PAN"},
										{"2315947873631049551", "Correct_PAN"} };

	unsigned char invalid = 0;


	for (int Case = 0; Case < 6; Case++)
	{
		printf("\nTest Case %d\n", Case);
		printf("Input Data: %s\n", PAN_Test[Case].PAN_No);
		printf("Expected Result: %s\n", PAN_Test[Case].Expected_Result);

		if ((strlen(PAN_Test[Case].PAN_No) <= 19) && (strlen(PAN_Test[Case].PAN_No) >= 16)) // Check PAN length
		{
			for (int x = 0; x < strlen(PAN_Test[Case].PAN_No); x++)
			{
				if (!(PAN_Test[Case].PAN_No[x] <= '9' && PAN_Test[Case].PAN_No[x] >= '0')) // Ensure only numeric character
				{
					invalid = 1;
					break;
				}
			}

			if (invalid == 0)
			{
				printf("Actual Result: CARD_OK\n");
			}
			else printf("Actual Result: WRONG_PAN\n");

		}
		else printf("Actual Result: WRONG_PAN\n");

		invalid = 0; // Reset
	}

}


	





int main(void)
{
	printf("Tester Name  : Abdelrahman Almahdy\n");
	printf("Function Name: getCardPAN\n");

	getCardPANTest();

	return 0;
}