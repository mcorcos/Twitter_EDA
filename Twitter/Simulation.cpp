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

void Simulation::displayTweets(vector<Tweet> tweetList, BasicLCD* lcd) {

	int tweetSelect = 0;
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
			user = (tweetList.at(tweetSelect)).getUser();
			date = (tweetList.at(tweetSelect)).getDate();
			string joiner = ": - ";
			string message = user + joiner + (tweetList.at(tweetSelect)).getText() + " -";
			/*
			string day = date.substr(date.find(' ',0,2)-1, date.find(' ', 0,3));
			string month = date.substr(date.find(' ', 0), date.find(' ', 1)+1);
			string year = date.substr(date.find(' ', 4), date.length());
			string hh_mm = date.substr(date.find(' ', 2), date.find(':', 1));
			cout << day+'/'+month+'/'+year+' '+'-'+' '+hh_mm;
			*/
			if (Event.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (Event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
					tweetSelect++;
					trimer = 0;
				}
				if (Event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
					if (tweetSelect != 0) {
						tweetSelect--;
						trimer = 0;
					}
					else {
						tweetSelect = 0;
						trimer = 0;
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
				if (!(timer % 40) && timer != 0) {
					trimer++;
					if (trimer > message.length() - 16) {
						trimer = 0;
						tweetSelect++;
					}
					timer = 0;
				}

				string message_to_16 = message.substr(trimer);
				*lcd << (unsigned char*)message_to_16.c_str();

				timer++;
				update_board(lcd);
			}
		}
	}
}