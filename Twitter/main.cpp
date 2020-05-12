#include <iostream>
#include <stdlib.h>
#include <ctype.h>
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

			loading(lcd, 32);
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
	bool ret = true;
	int i;

	if (argNum != 3) {
		ret = false;
		cout << "Invalid ammount of arguments." << endl;
	}

	for (i = 0; tweetNumber[i]; i++) {
		if (!isdigit(tweetNumber[i])) {
			ret = false;
			cout << "Invalid number of tweets" << endl;
		}
	}

	if (ret) {
		if (atoi(tweetNumber) > MAXTWEETNUMBER) {
			ret = false;
			cout << "Tweet number exceeds max value." << endl;
		}
	}

	return ret;
}