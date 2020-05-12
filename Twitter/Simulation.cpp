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

void Simulation::displayTweets(vector<Tweet> tweetList) {

	bool streamig = true;
	int counter = 0;

	while (streamig) {

		if (getNextEventType() == ALLEGRO_EVENT_TIMER) {
			cout << "hola";
			streamig = false;
		}
	}

	for (auto tweet_ : tweetList)
	{
		cout << "Tweets retrieved from Twitter account: " << tweet_.getUser() << endl;
		cout << tweet_.getUser() << endl;
		cout << tweet_.getDate() << endl;
		cout << tweet_.getText() << endl;

		std::cout << "-----------------------------------------" << std::endl;
	}
}