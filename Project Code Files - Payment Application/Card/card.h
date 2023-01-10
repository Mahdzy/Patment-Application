#ifndef CARD_H
#define CARD_H

#include <string.h>
#include <stdio.h>

/* Definitions */
typedef unsigned char uint8_t;

typedef struct ST_cardData_t
{
	uint8_t cardHolderName[29]; //Assuming the full name contains five names with 4 spaces
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

/* Pointers Declerations */
extern ST_cardData_t* CardDataPtr;

/* Functions Declerations */
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

#endif

