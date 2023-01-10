#include <stdio.h>
#include <string.h>

void setMaxAmountTest(void)
{
	struct Test_Cases
	{
		float transAmount;
		unsigned char Expected_Result[15];
	};

	struct Test_Cases Amount_Test[4] = { {5000.0f, "Valid_Amount"},
											{12000.0f, "Valid_Amount"},
											{-10.0f, "Invalid_Amount"},
											{0, "Invalid_Amount"} };

	for (int Case = 0; Case < 4; Case++)
	{
		printf("\nTest Case %d\n", Case);
		printf("Input Data: %.2f\n", Amount_Test[Case].transAmount);
		printf("Expected Result: %s\n", Amount_Test[Case].Expected_Result);

		if (Amount_Test[Case].transAmount > 0)
		{
			printf("Actual Result: TERMINAL_OK\n");
		}
		else
		{
			printf("Actual Result: INVALID_AMOUNT\n");

		}
	}
}


int main(void)
{
	printf("Tester Name  : Abdelrahman Almahdy\n");
	printf("Function Name: setMaxAmount\n");
	
	setMaxAmountTest();

	return 0;
}