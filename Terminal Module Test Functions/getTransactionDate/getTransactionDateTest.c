#define _CRT_SECURE_NO_WARNINGS_GLOBALS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <time.h>

void getTransactionDateTest(void)
{
	unsigned char Exp_Date[11] = { "xx/xx/xxxx" };
	int day, month, year;
	const unsigned int conversion_const = '1' - 1; // Conervts int to char type

	time_t current;
	time(&current);// Obtain current time
	struct tm* local = localtime(&current);

	day = local->tm_mday;            // get day of month (1 to 31)
	month = local->tm_mon + 1;      // get month of year (0 to 11)
	year = local->tm_year + 1900;   // get year since 1900

	Exp_Date[0] = (day / 10) + conversion_const;
	Exp_Date[1] = (day % 10) + conversion_const;
	Exp_Date[3] = (month / 10) + conversion_const;
	Exp_Date[4] = (month % 10) + conversion_const;
	Exp_Date[6] = (year / 1000) + conversion_const;
	Exp_Date[7] = ((year % 1000) / 100) + conversion_const;
	Exp_Date[8] = (((year % 1000) % 100) / 10) + conversion_const;
	Exp_Date[9] = (((year % 1000) % 100) % 10) + conversion_const;

	printf("Date is: %s\n", Exp_Date);
}


int main(void)
{
	printf("Tester Name  : Abdelrahman Almahdy\n");
	printf("Function Name: getTransactionDate\n");
	getTransactionDateTest();

	return 0;
}