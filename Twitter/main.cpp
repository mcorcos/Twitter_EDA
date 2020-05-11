#include <iostream>
#include "Client.h"
#include "AllegroLCD.h"

int main(void)
{
	//AllegroLCD displayLCD;

	BasicLCD* lcd = new AllegroLCD();
	int i = 1;

	bool searchingfortweets = true;
	Client EDA_Client("NicoTrozzo", 10);
	EDA_Client.getBearerToken();
	while (searchingfortweets)
	{
		//cout << "Donwloading Tweet ..." << endl;
		loading(lcd,i);
		searchingfortweets = EDA_Client.getTweets();
		i++;
	}
	EDA_Client.displayTweets();
	
	delete lcd;
	return 0;
}



