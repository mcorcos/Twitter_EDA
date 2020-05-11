#include "AllegroLCD.h"


AllegroLCD::AllegroLCD()
{
	lcdInitOK();
}


AllegroLCD::~AllegroLCD()
{
	if (display)
		al_destroy_display(display);

	if (lcd_simul)
		al_destroy_bitmap(lcd_simul);

	if (event_queue) {
		al_destroy_event_queue(event_queue);
	}
	al_shutdown_primitives_addon();

	if (Timer)
		al_destroy_timer(Timer);

}

bool AllegroLCD::lcdInitOK()
{



	if (!al_init()) {        //inicializacion general del allegro
		fprintf(stderr, "error al inicializar el allegro\n");
		return false;
	}


	event_queue = al_create_event_queue();       //se inicializa los eventos

	if (!event_queue) {                         //se controla si fallo la init de los eventos
		fprintf(stderr, "failed to create event_queue!\n");
		return false;
	}


	if (!al_init_primitives_addon()) {       //se controla si fallo la inicializacion de las primitivas
		fprintf(stderr, "error al inicializar las primitivas\n");
		return false;
	}

	if (!al_init_image_addon()) { // necesario para manejo de imagenes 
		fprintf(stderr, "failed to initialize image addon !\n");
		return false;
	}

	if (!al_init_font_addon()) { // necesario para manejo de fuentes de letras
		fprintf(stderr, "failed to initialize font addon !\n");
		return false;
	}


	if (!al_init_ttf_addon()) { // necesario para manejo de fuentes de letras
		fprintf(stderr, "failed to initialize font addon !\n");
		return false;
	}



	al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);
	display = al_create_display(676, 281);

	//se crea el display

	al_register_event_source(event_queue, al_get_display_event_source(display)); //se registra la fuente de los eventos de cierre de display

	if (!display) {//creo display
		al_shutdown_primitives_addon();      //se destruye la imagen porque ocupa espacio en heap y el programa fallo por otro motivo
		fprintf(stderr, "failed to create display");

		return false;
	}

	// creo timer
	Timer = al_create_timer(1 / FPS);
	if (!Timer) {
		return false;
	}

	// registro timer
	al_register_event_source(event_queue, al_get_timer_event_source(Timer));
	// start timer
	al_start_timer(Timer);

	lcd_simul = al_load_bitmap("lcd.bmp");


	if (!lcd_simul) {
		fprintf(stderr, "failed to load image lcd !\n");
		return false;
	}

	font = al_load_font("font.ttf", 24, 0);

	if (!font) {
		fprintf(stderr, "failed to load font !\n");
		return false;
	}

	al_draw_bitmap(lcd_simul, 0, 0, 0);          //se pinta las dos caras del display con lcd 
	al_flip_display();
	al_draw_bitmap(lcd_simul, 0, 0, 0);


	return true;
}

bool AllegroLCD::lcdGetError()
{
	if (result) {
		return FT_ok;
	}
	else {
		return FT_err;
	}
}

bool AllegroLCD::lcdMoveCursorUp()
{
	if (cadd > 16) {
		cadd -= 16;
		return true;
	}
	else {
		return false;
	}
}

bool AllegroLCD::lcdMoveCursorDown()
{
	if (cadd < 16) {
		cadd += 16;
		return true;
	}
	else {
		return false;
	}
}

BasicLCD& AllegroLCD::operator<<(const unsigned char c)
{
	display_char(c);
	return *this;
}

BasicLCD& AllegroLCD::operator<<(const unsigned char * c)
{
	display_chars((char*)c);
	return *this;
}

void AllegroLCD::update_board()
{
	int i, j;

	for (i = 0; i < 2; i++) {

		for (j = 0; j < 16; j++) {

			check_lcd(i, j);

		}

	}
	al_flip_display();
}

void AllegroLCD::check_lcd(int x, int y)
{
	const char c = lcd_chars[x][y];

	if (isAlpha(c) || isNum(c)) {

		(*this) << c;
	}
}

void AllegroLCD::display_char(char c)
{
	al_draw_text(font, al_color_name("black"), 50, 40, 0, &c);
}

void AllegroLCD::display_chars(char * c)
{
	al_draw_text(font, al_color_name("black"), 50, 40, 0, c);
}

bool AllegroLCD::lcdMoveCursorRight() {
	return true;
}
bool AllegroLCD::lcdMoveCursorLeft() {
	return true;
}
bool AllegroLCD::lcdClearToEOL() { 
	return true;
}
bool AllegroLCD::lcdClear() {
	return true;
}
bool AllegroLCD::lcdSetCursorPosition(const cursorP po) {
	return true;
}
int AllegroLCD::lcdGetCusorPosition() {

	return 6;
}

