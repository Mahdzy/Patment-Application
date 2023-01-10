#include "Application/app.h"


int main(void)
{
	printf("********* Welcome *********\n");
	char Running = 1;
	
	while (1)
	{
		appStart();
		printf("\nDo You Want to Start a New Transaction? (Y/N)\n");
		
		Running = getch();
		{
			if (!((Running == 'y') || (Running == 'Y')))
			{
				Running = 0;
				printf("\n********* Thank You *********\n");
				break;
			}
		}
	}
	
	return 0;
}

