#include <iostream>
#include "Client.h"
#include "AllegroLCD.h"
#include "Simulation.h"

bool parseInput(int argNum, char *username, char* tweetNumber);

int main(int argc, char **argv)
{
	bool result=parseInput(argc, argv[1], argv[2]);

	if (result)
	{
		int tweet_count = 10, i = 1;
		Simulation* sim = new Simulation();
		sim->initialize();
		BasicLCD* lcd = new AllegroLCD();
		bool searchingfortweets = true;

		Client* ClientPtr = new Client("NicoTrozzo", tweet_count);
		ClientPtr->getBearerToken();

		while (searchingfortweets)
		{

			loading(lcd, 10);
			searchingfortweets = ClientPtr->getTweets();

		}
		sim->displayTweets(ClientPtr, lcd);
		//EDA_Client.displayTweets();
		delete lcd;
		delete sim;
	}
	return 0;
}

bool parseInput(int argNum, char *username, char* tweetNumber)
{
	/*if (argNum != 3) {
		bool = false;
		cout << "Invalid ammount of arguments." << endl;
	}*/
	return true;
}