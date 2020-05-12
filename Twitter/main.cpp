#include <iostream>
#include "Client.h"
#include "AllegroLCD.h"
#include "Simulation.h"

int main(char argc, char **argv)
{
	char* errormessage1 = "invalid input";
	int tweet_count = 10, i = 1;
	Simulation* sim = new Simulation();
	sim->initialize();
	BasicLCD* lcd = new AllegroLCD();
	bool searchingfortweets = true;
	Client EDA_Client("N.;89899", tweet_count);
		EDA_Client.getBearerToken();

		while (searchingfortweets)
		{

			loading(lcd, 10);
			searchingfortweets = EDA_Client.getTweets();

		}
		sim->displayTweets(EDA_Client.getTweetList(), lcd);
		//EDA_Client.displayTweets();
	delete lcd;
	delete sim;
	return 0;
}



