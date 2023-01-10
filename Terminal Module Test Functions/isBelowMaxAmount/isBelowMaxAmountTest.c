#include <stdio.h>
#include <string.h>

void isBelowMaxAmountTest(void)
{
	struct Test_Cases
	{
		float transAmount;
		unsigned char Expected_Result[15];
	};

	struct Test_Cases Amount_Test[4] = { {15000.0f, "Valid_Amount"},
											{20000.0f, "Valid_Amount"},
											{55200.0, "Invalid_Amount"},
											{70000.0, "Invalid_Amount"} };

	float maxTransAmount = 20000.0f;

	for (int Case = 0; Case < 4; Case++)
	{
		printf("\nTest Case %d\n", Case);
		printf("Input Data: %.2f\n", Amount_Test[Case].transAmount);
		printf("Maximum Amount: %.2f\n", maxTransAmount);
		printf("Expected Result: %s\n", Amount_Test[Case].Expected_Result);

		if (Amount_Test[Case].transAmount > maxTransAmount)
		{
			printf("Actual Result: EXCEED_MAX_AMOUNT\n");
		}
		else
		{
			printf("Actual Result: TERMINAL_OK\n");

		}
	}

}


int main(void)
{
	printf("Tester Name  : Abdelrahman Almahdy\n");
	printf("Function Name: isBelowMaxAmount\n");
	
	isBelowMaxAmountTest();

	return 0;
}