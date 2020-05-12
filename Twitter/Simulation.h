#pragma once
#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_color.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Tweet.h"
#include "Client.h"
#include "AllegroLCD.h"

#define FPS    60.0
#define SPEED_LOWER_LIMIT 6
#define SPEED_HIGHER_LIMIT 100
#define DEFAULT_SPEED 30

string parse_date(std::string usr_date);

class Simulation {
public:
	Simulation(
		ALLEGRO_DISPLAY* display = nullptr,
		ALLEGRO_TIMER* timer = nullptr,
		ALLEGRO_EVENT_QUEUE* queue = nullptr
	);
	~Simulation();
	bool initialize(void);
	ALLEGRO_DISPLAY* getDisplay();
	ALLEGRO_TIMER* getTimer();
	ALLEGRO_EVENT getEvent();
	void displayTweets(Client* ClientPtr, BasicLCD* lcd);
	int getNextEventType();
private:

	void dispatch(int type);
	void setLCD(BasicLCD* lcd, int x, int y);
	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_EVENT Event;
	int trimer=0;
	int tweetSelect = 0;
	int tweet_select_upper_bound;
	int speed = DEFAULT_SPEED;
	int sequence_counter;
	bool streaming = true;
};