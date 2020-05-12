
#include <iostream>
#include "Client.h"
#include "AllegroLCD.h"
#include "Simulation.h"

int main(char argc, char **argv)
{
	int tweet_count = 10, i = 1;
	Simulation* sim = new Simulation();
	sim->initialize();
	BasicLCD* lcd = new AllegroLCD();
	bool searchingfortweets = true;

	Client* ClientPtr= new Client("lanacion", tweet_count);
	ClientPtr->getBearerToken();

		while (searchingfortweets)
		{

			loading(lcd, 32);
			searchingfortweets = ClientPtr->getTweets();

		}
		sim->displayTweets(ClientPtr, lcd);
		//EDA_Client.displayTweets();
	delete lcd;
	delete sim;
	return 0;
}



