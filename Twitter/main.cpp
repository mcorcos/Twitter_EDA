#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include "Client.h"
#include "AllegroLCD.h"
#include "Simulation.h"

bool parseInput(int argNum, char *username, char* tweetNumber);

int main(int argc, char **argv)
{
	bool result = true;
	bool use_default = false;

	if(argc!=2)
		result=parseInput(argc, argv[1], argv[2]);
	else use_default = true;

	if (result)
	{
		int tweet_count;

		if(!use_default)
			tweet_count = stoi(argv[2]);
		else 
			tweet_count = DEFAULT_TWEET_NUMBER;

		string username = argv[1];
		Simulation* sim = new Simulation();
		sim->initialize();
		BasicLCD* lcd = new AllegroLCD();
		bool searchingfortweets = true;

		Client* ClientPtr = new Client(username, tweet_count);
		ClientPtr->getBearerToken();

		if (ClientPtr->getErrorCode() == ERROR_FREE)
		{
			while (searchingfortweets)
			{

				loading(lcd, 32);
				searchingfortweets = ClientPtr->getTweets();

			}
		}
		else
		{
			loading(lcd, 32);
			ClientPtr->setErrorMessage();
		}

		sim->displayTweets(ClientPtr, lcd);


		delete ClientPtr;
		delete lcd;
		delete sim;
	}
	return 0;
}

bool parseInput(int argNum, char *username, char* tweetNumber)
{
	bool ret = true;
	int i;

	if (argNum == 3) {
		for (i = 0; tweetNumber[i]; i++) {
			if (!isdigit(tweetNumber[i])) {
				ret = false;
			}
		}
		if (!ret)
			cout << "Invalid number of tweets" << endl;
	}

	else {
		ret = false;
		cout << "Invalid ammount of arguments - Argumentos should be: name+tweetammount or name" << endl;
	}

	return ret;
}