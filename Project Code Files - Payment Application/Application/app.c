#include "app.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"

void appStart(void)
{
	EN_StageState_t State = -1;

	/* First Stage - Card Data Entry */
	if (getCardHolderName(CardDataPtr) == CARD_OK)
	{
		if (getCardPAN(CardDataPtr) == CARD_OK)
		{
			if (getCardExpiryDate(CardDataPtr) == CARD_OK)
			{
				State = CARD_STAGE_SUCCEEDED;
			}
			else
			{
				printf("\nInvalid Expiration Date!\nProcess Terminated\n");
			}
		}
		else
		{
			printf("\nIncorrect PAN!\nProcess Terminated\n");
		}
	}
	else
	{
		printf("\nInvalid Name!\nProcess Terminated\n");
	}

	/* Second Stage - Terminal Data Processing */
	if (State == CARD_STAGE_SUCCEEDED)
	{
		/* Initiating Terminal Data*/
		getTransactionDate(TerminalDataPtr);
		setMaxAmount(TerminalDataPtr, 20000.0f);
	
		if (isValidCardPAN(CardDataPtr) == TERMINAL_OK)
		{
			if (isCardExpired(CardDataPtr, TerminalDataPtr) == TERMINAL_OK)
			{
				if (getTransactionAmount(TerminalDataPtr) == TERMINAL_OK)
				{
					if (isBelowMaxAmount(TerminalDataPtr) == TERMINAL_OK)
					{
						State = Terminal_STAGE_SUCCEEDED;
					}
					else
					{
						printf("\nYou Excedded The Maximum Transaction Amount, The Maximum Transaction Amount is %.2f LE\nProcess Terminated\n", TerminalDataPtr->maxTransAmount);
					}
				}
				else
				{
					printf("\nInvalid Transaction Amount!\nProcess Terminated\n");
				}
			}
			else
			{
				printf("\nYour Card is Expired\nProcess Terminated\n");
			}
		}
		else
		{
			State = Terminal_STAGE_SUCCEEDED;
			printf("\nFraud Card Detected\nProcess Terminated\n");
		}
	}

	/* Third Stage - Server Data Processing */
	if (State == Terminal_STAGE_SUCCEEDED)
	{
		switch (recieveTransactionData(AccountsTransPtr))
		{
		case APPROVED:
			printf("\nYour Transaction is Done Successfully\nYour balance is: %.2f\n", AccountReference->balance);
			break;

		case FRAUD_CARD:
			printf("\nFraud Card Detected\nProcess Terminated\n");
			break;

		case DECLINED_INSUFFECIENT_FUND:
			printf("\nYour Balance is Lower Than The Transaction Amount\nProcess Terminated\n");
			break;

		case DECLINED_STOLEN_CARD:
			printf("\nStolen Card Detected\nProcess Terminated\n");
			break;

		default:
			printf("\nInternal Server Error\nProcess Terminated\n");
			break;
		}

		saveTransaction(AccountsTransPtr);
	}

	State = -1; //Reset
}

