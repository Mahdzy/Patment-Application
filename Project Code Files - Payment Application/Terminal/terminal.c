#include <stdlib.h>
#include "../Card/card.h"
#include "terminal.h"


ST_terminalData_t TerminalData = { 0.0f, 0.0f, "xx/xx/xxxx" };
extern ST_terminalData_t* TerminalDataPtr = &TerminalData;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	uint32_t Day, Month, Year;
	const uint32_t ConvConst = '1' - 1; // Convertion from int to char type

	struct tm local;
	time_t Current = time(0);
	localtime_s(&local, &Current);

	Day = local.tm_mday; // get day of month (1 to 31)
	Month = local.tm_mon + 1; // get month of year (0 to 11)
	Year = local.tm_year + 1900; // get year since 1900

	/* Conversion of Date from int to string */
	termData->transactionDate[0] = (Day / 10) + ConvConst;
	termData->transactionDate[1] = (Day % 10) + ConvConst;
	termData->transactionDate[3] = (Month / 10) + ConvConst;
	termData->transactionDate[4] = (Month % 10) + ConvConst;
	termData->transactionDate[6] = (Year / 1000) + ConvConst;
	termData->transactionDate[7] = ((Year % 1000) / 100) + ConvConst;
	termData->transactionDate[8] = (((Year % 1000) % 100) / 10) + ConvConst;
	termData->transactionDate[9] = (((Year % 1000) % 100) % 10) + ConvConst;

	return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	const uint32_t ConvConst = '1' - 1; // Convertion from int to char type
	uint32_t CurrentYear, CurrentMonth, ExpiryYear, ExpiryMonth;

	/* Conversion of Current and Expiry Date from string to int */
	CurrentYear = 10 * (termData->transactionDate[8] - ConvConst) + (termData->transactionDate[9] - ConvConst); // Current year in integer format
	CurrentMonth = 10 * (termData->transactionDate[3] - ConvConst) + (termData->transactionDate[4] - ConvConst);// Current month in integer format
	ExpiryYear = 10 * (cardData->cardExpirationDate[3] - ConvConst) + (cardData->cardExpirationDate[4] - ConvConst); // Expiration year in integer format
	ExpiryMonth = 10 * (cardData->cardExpirationDate[0] - ConvConst) + (cardData->cardExpirationDate[1] - ConvConst); // Expiration month in integer format

	if (ExpiryYear > CurrentYear)
	{
		return TERMINAL_OK;
	}
	else if (ExpiryYear == CurrentYear)
	{
		if (ExpiryMonth >= CurrentMonth)
		{
			return TERMINAL_OK;
		}
		else
		{
			return EXPIRED_CARD;
		}
	}
	else
	{
		return EXPIRED_CARD;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	char StrTransactionAmount[20]; // Temporary String to store Transaction Amount

	printf("\nEnter The Transaction Amount: ");
	fgets(StrTransactionAmount, 20, stdin);

	termData->transAmount = strtof(StrTransactionAmount, NULL); // Converts String to float

	if (termData->transAmount > 0)
	{
		return TERMINAL_OK;
	}
	else
	{
		return INVALID_AMOUNT;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	if (maxAmount > 0)
	{
		termData->maxTransAmount = maxAmount;
		return TERMINAL_OK;
	}
	else
	{
		return INVALID_MAX_AMOUNT;
	}
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	uint32_t PAN[20] = { 0 }; // Integer Version of PAN
	const uint32_t ConvConst = '1' - 1; // Convertion from int to char type
	uint32_t LastDigit = 0; // Stores the last digit of the PAN
	uint32_t CheckSum = 0; // Stores the CheckSum of the PAN
	uint32_t Counter = 0; // Counts even positions of PAN

	/* Converts PAN from string to int */
	for (uint32_t Index = 0; Index < strlen(cardData->primaryAccountNumber); Index++)
	{
		PAN[Index] = cardData->primaryAccountNumber[Index] - ConvConst;
	}

	LastDigit = PAN[strlen(cardData->primaryAccountNumber) - 1];

	/* Checksum Calculations */
	for (int Index = (int)(strlen(cardData->primaryAccountNumber) - 2); Index >= 0; Index--)
	{
		if ((Counter % 2) == 0)
		{
			PAN[Index] *= 2;

			if (PAN[Index] < 10)
			{
				CheckSum += PAN[Index];
			}
			else
			{
				CheckSum += (PAN[Index] / 10) + (PAN[Index] % 10);
			}
		}
		else
		{
			CheckSum += PAN[Index];
		}

		Counter += 1;
	}

	CheckSum = ((10 - (CheckSum % 10)) % 10);

	if (CheckSum == LastDigit)
	{
		return TERMINAL_OK;
	}
	else
	{
		return INVALID_CARD;
	}
}
