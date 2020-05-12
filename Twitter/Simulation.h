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
#include "AllegroLCD.h"

#define FPS    60.0


class Simulation {
public:
	Simulation(
		ALLEGRO_DISPLAY* display=nullptr,
		ALLEGRO_TIMER*timer=nullptr,
		ALLEGRO_EVENT_QUEUE* queue=nullptr
	);
	~Simulation();
	bool initialize(void);
	ALLEGRO_DISPLAY* getDisplay();
	ALLEGRO_TIMER* getTimer();
	ALLEGRO_EVENT getEvent();
	int getNextEventType();
	void displayTweets(vector<Tweet> tweetList, BasicLCD* lcd);

private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_EVENT Event;
};