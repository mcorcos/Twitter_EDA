#include <iostream>
#include "Client.h"
#include "AllegroLCD.h"

int main(void)
{
	//AllegroLCD displayLCD;
	int tweet_count = 10, i = 1;
	BasicLCD* lcd = new AllegroLCD();
	bool searchingfortweets = true;
	Client EDA_Client("NicoTrozzo", tweet_count);
	EDA_Client.getBearerToken();

	while (searchingfortweets)
	{

		loading(lcd,10);
		searchingfortweets = EDA_Client.getTweets();

	}

	EDA_Client.displayTweets();


	delete lcd;
	return 0;
}



