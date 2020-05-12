#include "Simulation.h"
#include <string>

Simulation::Simulation(
	ALLEGRO_DISPLAY* display,
	ALLEGRO_TIMER* timer,
	ALLEGRO_EVENT_QUEUE* queue
): display(display), timer(timer), queue(queue) {
}

Simulation::~Simulation() {
	// DESTROY EVERYTHING
	if (queue) {
		al_destroy_event_queue(queue);
	}
	if (timer)
		al_destroy_timer(timer);
	if (display)
		al_destroy_display(display);
}

bool Simulation::initialize() {
	bool res = true;

	if (!al_init()) {        //inicializacion general del allegro
		fprintf(stderr, "error al inicializar el allegro\n");
		res = false;
	}

	else if (!al_init_primitives_addon()) {       //se controla si fallo la inicializacion de las primitivas
		fprintf(stderr, "error al inicializar las primitivas\n");
		return false;
	}

	else if (!al_init_image_addon()) { // necesario para manejo de imagenes 
		fprintf(stderr, "failed to initialize image addon !\n");
		return false;
	}

	else if (!al_init_font_addon()) { // necesario para manejo de fuentes de letras
		fprintf(stderr, "failed to initialize font addon !\n");
		return false;
	}

	else if (!al_init_ttf_addon()) { // necesario para manejo de fuentes de letras
		fprintf(stderr, "failed to initialize font addon !\n");
		return false;
	}

	queue = al_create_event_queue();       //se inicializa los eventos

	if (!queue) {                         //se controla si fallo la init de los eventos
		fprintf(stderr, "failed to create event_queue!\n");
		res = false;
	}

	display = al_create_display(676, 281);

	//se crea el display

	al_register_event_source(queue, al_get_display_event_source(display)); //se registra la fuente de los eventos de cierre de display

	if (!display) {//creo display
		al_shutdown_primitives_addon();      //se destruye la imagen porque ocupa espacio en heap y el programa fallo por otro motivo
		fprintf(stderr, "failed to create display");
		res = false;
	}

	// creo timer
	timer = al_create_timer(1 / FPS);
	if (!timer) {
		res = false;
	}

	// registro timer
	al_register_event_source(queue, al_get_timer_event_source(timer));
	// start timer
	al_start_timer(timer);

	if (!al_install_mouse()) {
		res = false;
	}

	else if (!al_install_keyboard()) {
		res = false;
	}
	al_register_event_source(queue, al_get_keyboard_event_source());

	return res;
}

ALLEGRO_DISPLAY* Simulation::getDisplay() {
	return display;
}

ALLEGRO_TIMER* Simulation::getTimer() {
	return timer;
}

int Simulation::getNextEventType() {
	if (al_get_next_event(queue, &Event))
		return Event.type;
	else
		return NULL;
}

ALLEGRO_EVENT Simulation::getEvent() {
	return Event;
}

string parse_date(std::string usr_date) {

	string day, month, year, hs;
	month.assign(usr_date, 4, 3);
	day.assign(usr_date, 8, 2);
	hs.assign(usr_date, 11, 5);
	year.assign(usr_date, 28, 2);
	usr_date = day + "/" + month + "/" + year + " - " + hs;

	return usr_date;
}


void Simulation::displayTweets(vector<Tweet> tweetList, BasicLCD* lcd) {

	int tweetSelect = 0;
	int speed = 30;
	cursorP p;
	p.x = 1;
	p.y = 1;
	string user;
	string date;
	string text;
	bool streamig = true;
	int timer = 0;
	int trimer = 0;

	lcd->lcdSetCursorPosition(p);
	lcd->lcdClear();
	update_board(lcd);
	while (streamig && getNextEventType() != ALLEGRO_EVENT_DISPLAY_CLOSE) {
		if (getNextEventType()) {
			string message = "";
			if (tweetSelect < tweetList.size()) {
				user = (tweetList.at(tweetSelect)).getUser();
				date = parse_date((tweetList.at(tweetSelect)).getDate());
				message = user + ": - " + (tweetList.at(tweetSelect)).getText() + " -";
			}

			if (Event.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (Event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
					if (tweetSelect < tweetList.size()) {
						tweetSelect++;
					}
					trimer = 0;
				}
				else if (Event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
					if (tweetSelect != 0) {
						tweetSelect--;
						trimer = 0;
					}
					else {
						tweetSelect = 0;
						trimer = 0;
					}
				}
				else if (Event.keyboard.keycode == ALLEGRO_KEY_UP) {
					if (speed > 6) {
						speed-=5;
					}
				}
				else if (Event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
					if (speed < 100) {
						speed+=5;
					}
				}
			}

			if (Event.type == ALLEGRO_EVENT_TIMER) {

				lcd->lcdClear();
				update_board(lcd);

				p.x = 1;
				p.y = 1;

				lcd->lcdSetCursorPosition(p);
				*lcd << (unsigned char*)date.c_str();

				p.x = 1;
				p.y = 2;
				lcd->lcdSetCursorPosition(p);

				// escribo autor y texto
				if (!(timer % speed) && timer != 0) {
					trimer++;
					if (trimer > message.length() - 16) {
						trimer = 0;
						if (tweetSelect < tweetList.size()) {
							tweetSelect++;
						}
					}
					timer = 0;
				}
				string message_to_16;
				if (tweetSelect < tweetList.size()) {
					message_to_16 = message.substr(trimer);
				}
				else {
					p.x = 1;
					p.y = 1;
					lcd->lcdSetCursorPosition(p);
					*lcd << (unsigned char*)"";
					p.x = 2;
					p.y = 2;
					lcd->lcdSetCursorPosition(p);
					message_to_16 = "No more tweets";
				}
				*lcd << (unsigned char*)message_to_16.c_str();

				timer++;
				update_board(lcd);
			}
		}
	}
}