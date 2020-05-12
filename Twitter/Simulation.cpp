#include "Simulation.h"
#include <string>

const char* endofmessage = "................";

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

void Simulation::setLCD(BasicLCD* lcd, int x, int y) {
	
	cursorP p;
	p.x = x;
	p.y = y;

	lcd->lcdSetCursorPosition(p);
}


void Simulation::dispatch(int type) {

	switch (type) {
	case ALLEGRO_KEY_SPACE:
		trimer = 0;
		break;
	case ALLEGRO_KEY_RIGHT:
		if (tweetSelect < tweet_select_upper_bound) {
			tweetSelect++;
		}
		trimer = 0;
		break;
	case ALLEGRO_KEY_LEFT:
		if (tweetSelect != 0) {
			tweetSelect--;
			trimer = 0;
		}
		else {
			tweetSelect = 0;
			trimer = 0;
		}
		break;
	case ALLEGRO_KEY_UP:
		if (speed > SPEED_LOWER_LIMIT) {
			speed -= 5;
		}
		break;
	case ALLEGRO_KEY_DOWN:
		if (speed < SPEED_HIGHER_LIMIT) {
			speed += 5;
		}
		break;
	case ALLEGRO_KEY_Q:
		streaming = false;
	default:
		break;
	}
}


void Simulation::displayTweets(Client* ClientPtr, BasicLCD* lcd) {

	tweet_select_upper_bound = ClientPtr->getTweetList().size();
	cursorP p;
	string user;
	string date;
	string text;
	string message = "";
	bool error = false;


	lcd->lcdClear();
	update_board(lcd);
	while (streaming) {
		if (getNextEventType()) {

			if (Event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				streaming = false;
			}

			if (tweetSelect < tweet_select_upper_bound) {
				if (ClientPtr->getErrorCode() == ERROR_FREE)
				{
					user = (ClientPtr->getTweetList().at(tweetSelect)).getUser();
					date = parse_date((ClientPtr->getTweetList().at(tweetSelect)).getDate());
					message = user + ": - " + (ClientPtr->getTweetList().at(tweetSelect)).getText() + "-";
				}
				else
				{
					error = true;
					switch (ClientPtr->getErrorCode())
					{
					case INVALID_USERNAME:
						message = "Could not find requested Twitter username";
						message.append(endofmessage);
						break;
					case JSON_ERROR:
						message = "Unspecified JSON error";
						message.append(endofmessage);
						break;
					case CURL_EASY_ERROR:
						message = "Could not initiate Curl Easy Handle";
						message.append(endofmessage);
						break;
					case CURL_MULTI_ERROR:
						message = "Could not initiate Curl Multi Handle";
						message.append(endofmessage);
						break;
					case CURL_ERROR:
						message = "Cannot start curl";
						message.append(endofmessage);
						break;
					case TWEET_NUMBER_ERROR:
						message = "Invalid number of tweets";
						message.append(endofmessage);
						break;
					default:
						break;
					}
				}
			}


			if (Event.type == ALLEGRO_EVENT_KEY_DOWN) {
				dispatch(Event.keyboard.keycode);
			}

			if (Event.type == ALLEGRO_EVENT_TIMER) {

				lcd->lcdClear();
				update_board(lcd);


				// escribo autor y texto
				if (!(sequence_counter % speed) && sequence_counter != 0) {
					trimer++;
					if (trimer > message.length() - 16) {
						trimer = 0;
						if (tweetSelect < tweet_select_upper_bound) {
							tweetSelect++;
						}
					}
					sequence_counter = 0;
				}

				string message_to_16;
				if (tweetSelect < tweet_select_upper_bound) {
					message_to_16 = message.substr(trimer);
				}
				else {
					if (!error)
					{
						message_to_16 = "No more tweets";
						date = "";
					}
					else {
						message_to_16 = message;
						tweetSelect--;
					}
				}

				setLCD(lcd, 1, 1);
				*lcd << (unsigned char*)date.c_str();

				setLCD(lcd, 1, 2);
				*lcd << (unsigned char*)message_to_16.c_str();

				update_board(lcd);
				sequence_counter++;
			}
		}
	}
}

string parse_date(std::string usr_date) {

	string day, month, year, hs;
	month.assign(usr_date, 4, 3);
	month = month_tonum(month);
	day.assign(usr_date, 8, 2);
	hs.assign(usr_date, 11, 5);
	year.assign(usr_date, 28, 2);
	usr_date = day + "/" + month + "/" + year + " - " + hs;

	return usr_date;
}
