#include "card.h"

ST_cardData_t CardData = { "\0", "\0", "xx/xx" };
extern ST_cardData_t* CardDataPtr = &CardData;

/* Card Holder Name Entry */
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t Invalid = 0;  // Flag to check name validity
	uint8_t Stringlength = 0; // Store the length of the alphabetic characters
	ST_cardData_t CardData = { "\0", "\0", "xx/xx" };
	printf("\nEnter The Card Holder Name: ");
	fgets(cardData->cardHolderName, sizeof(cardData->cardHolderName), stdin);
	_strupr_s(cardData->cardHolderName, sizeof(cardData->cardHolderName)); // Convert string to upper case letters

	for (int Index = 0; Index < (strlen(cardData->cardHolderName) - 1); Index++)
	{
		if ((cardData->cardHolderName[Index] <= 'Z' && cardData->cardHolderName[Index] >= 'A') || cardData->cardHolderName[Index] == ' ') // Check if the character is alphabetic or space
		{
			if (cardData->cardHolderName[Index] != ' ')
			{
				Stringlength += 1;
			}
		}
		else
		{
			Invalid = 1;
			break; // break once non-alphabetic character is found
		}
	}

	if (Invalid == 0)
	{
		if ((Stringlength > 19) && ((Stringlength < 25))) // Check the length of the alphabetic characters
		{
			return CARD_OK;
		}
		else
		{
			return WRONG_NAME;
		}

	}
	else
	{
		return WRONG_NAME;
	}
}

/* Card Expiration Date Entry */
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("\nEnter The Card Expiration Date: ");
	gets(cardData->cardExpirationDate);

	if (strlen(cardData->cardExpirationDate) == 5) // Checks the length of the date
	{
		if (cardData->cardExpirationDate[2] == '/') // Ensures proper format
		{
			if (((cardData->cardExpirationDate[0] == '0') && (cardData->cardExpirationDate[1] > '0' && cardData->cardExpirationDate[1] <= '9')) || ((cardData->cardExpirationDate[0] == '1') && (cardData->cardExpirationDate[1] >= '0' && cardData->cardExpirationDate[1] <= '2'))) // Checks if 1 <= Month <= 12
			{
				if (((cardData->cardExpirationDate[3] == '2') && (cardData->cardExpirationDate[4] > '1' && cardData->cardExpirationDate[4] <= '9')) || ((cardData->cardExpirationDate[3] >= '3' && cardData->cardExpirationDate[1] <= '9') && (cardData->cardExpirationDate[1] >= '0' && cardData->cardExpirationDate[1] <= '9'))) // Checks if 22 <= Year <= 99
				{
					return CARD_OK;
				}
				else
				{
					printf("Please Enter The Date Correctly\n"); // Wrong year condition
					return WRONG_EXP_DATE;
				}
			}
			else
			{
				printf("Please Enter The Date Correctly\n"); // Wrong month condition
				return WRONG_EXP_DATE;
			}
		}
		else
		{
			printf("Please Enter The Date Correctly\n"); // Wrong format condition
			return WRONG_EXP_DATE;
		}
	}
	else
	{
		printf("Please Enter The Date Correctly\n");  // Wrong format condition
		return WRONG_EXP_DATE;
	}
}

/* Card PAN Entry */
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint8_t Invalid = 0; // Flag to check PAN validity

	printf("\nEnter The Primary Account Number: ");
	gets(cardData->primaryAccountNumber);

	if ((strlen(cardData->primaryAccountNumber) <= 19) && (strlen(cardData->primaryAccountNumber) >= 16)) // Check the length of the PAN
	{
		for (int Index = 0; Index < strlen(cardData->primaryAccountNumber); Index++)
		{
			if (!(cardData->primaryAccountNumber[Index] <= '9' && cardData->primaryAccountNumber[Index] >= '0')) // Check if the character is numeric
			{
				Invalid = 1;
				break; // break once non-numeric character is found
			}
		}

		if (Invalid == 0)
		{
			return CARD_OK;
		}
		else
		{
			return WRONG_PAN;
		}
	}
	else
	{
		return WRONG_PAN;
	}
}
