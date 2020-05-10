#include <iostream>
#include "Client.h"

int main(void)
{
	bool searchingfortweets = true;
	Client EDA_Client("NicoTrozzo", 10);
	EDA_Client.getBearerToken();
	while (searchingfortweets)
	{
		cout << "Donwloading Tweet ..." << endl;
		searchingfortweets = EDA_Client.getTweets();
	}
	EDA_Client.displayTweets();
	
	return 0;
}



