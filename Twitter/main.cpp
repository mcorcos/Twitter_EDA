#include <iostream>
#include "Client.h"
#include "Allegro.h"
int main(void)
{
	Graphic graphic;
	graphic.inicializacion();
	bool searchingfortweets = true;
	Client EDA_Client("NicoTrozzo", 10);
	EDA_Client.getBearerToken();
	while (searchingfortweets)
	{
		searchingfortweets = EDA_Client.getTweets();
	}
	while (1) {
		graphic.update_board();
	}
	
	return 0;
}



