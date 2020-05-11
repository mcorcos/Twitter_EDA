#include <iostream>
#include "Client.h"
#include "AllegroLCD.h"

int main(void)
{
	//AllegroLCD displayLCD;

	BasicLCD* lcd = new AllegroLCD();

	bool searchingfortweets = true;
	Client EDA_Client("NicoTrozzo", 10);
	EDA_Client.getBearerToken();
	while (searchingfortweets)
	{
		cout << "Donwloading Tweet ..." << endl;
		searchingfortweets = EDA_Client.getTweets();
	}

	EDA_Client.displayTweets();
	
	BasicLCD* lcd= new AllegroLCD;
	return 0;
}



