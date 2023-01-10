#include <stdio.h>
#include <string.h>

void isValidCardPANTest(void)
{
	struct Test_Cases
	{
		unsigned char PAN_No[25];
		unsigned char Expected_Result[15];
	};

	struct Test_Cases Valid_PAN_Test[6] = { {"25268269252682690", "Valid_PAN"},
											{"12345678912345677", "Valid_PAN"},
											{"10475211910475217", "Valid_PAN"},
											{"10993655911099365", "Invalid_PAN"},
											{"7894561237894561822", "Invalid_PAN"},
											{"1472583691472583595", "Invalid_PAN"} };
	
	unsigned int Int_PAN[20] = { 0 }; // Integer Version of PAN
	const unsigned int conversion_const = '1' - 1; // Conversion between int and char type
	unsigned int Last_Digit = 0, Check_Sum = 0, Counter = 0;

	for (int Case = 0; Case < 6; Case++)
	{
		/* Converts char PAN to int PAN */
		for (int Index = 0; Index < strlen(Valid_PAN_Test[Case].PAN_No); Index++)
		{
			Int_PAN[Index] = Valid_PAN_Test[Case].PAN_No[Index] - conversion_const;
		}
		printf("\nTest Case %d\n", Case);
		printf("Input Data: %s\n", Valid_PAN_Test[Case].PAN_No);
		printf("Expected Result: %s\n", Valid_PAN_Test[Case].Expected_Result);
		Last_Digit = Int_PAN[strlen(Valid_PAN_Test[Case].PAN_No) - 1];
		printf("Last_Digit is %d ", Last_Digit);

		for (int Index = (strlen(Valid_PAN_Test[Case].PAN_No) - 2); Index >= 0; Index--)
		{
			if ((Counter % 2) == 0) // to count only even indexes
			{
				Int_PAN[Index] *= 2;
				if (Int_PAN[Index] < 10)
				{
					Check_Sum += Int_PAN[Index];
				}
				else
				{
					Check_Sum += (Int_PAN[Index] / 10) + (Int_PAN[Index] % 10);
				}
			}
			else
			{
				Check_Sum += Int_PAN[Index];
			}
			Counter += 1;
		}
		
		Counter = 0; // Reset

		Check_Sum = ((10 - (Check_Sum % 10)) % 10);
		printf("and Check Sum is %d\n", Check_Sum);

		if (Check_Sum == Last_Digit)
		{
			printf("Actual Result: Valid_PAN\n");
		}
		else
		{
			printf("Actual Result: Invalid_PAN\n");
		}

		Last_Digit = 0; // Reset
		Check_Sum = 0; // Reset
	}
}



int main(void)
{
	printf("Tester Name  : Abdelrahman Almahdy\n");
	printf("Function Name: isValidCardPAN\n");
	
	isValidCardPANTest();

	return 0;
}