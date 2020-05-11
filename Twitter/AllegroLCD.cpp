#include "AllegroLCD.h"
#include "string.h"

char lcd_chars[2][16];
struct cursorP po;

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

	if (!lcdClear()) {
		fprintf(stderr, "failed to xlear lcd !\n");
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
	int pos, x, y;
	pos = cadd - 1;
	if (pos >= 16) {
		x = pos - 16;
	}
	else {
		x = pos;
	}
	if (pos >= 16) {
		y=1;
	}
	else {
		y=0;
	}
	display_char(c,x,y);
	if (lcdMoveCursorRight()) {

	}
	else {
		cadd = 1;
	}
	return *this;
}

BasicLCD& AllegroLCD::operator<<(const unsigned char * c)
{
	//int x, y, pos;
	//display_chars((char*)c,x,y);
	return *this;

	string string = (char*)c, string1, string2;
	int pos, x, y;
	pos = cadd - 1;
	if (pos >= 16) {
		x = pos - 16;
	}
	else {
		x = pos;
	}
	if (pos >= 16) {
		y = 1;
	}
	else {
		y = 0;
	}


	if (16 - x >= string.size()) {

		cadd = cadd += string.size();
		for (int i = 0;i < string.size();i++) {

			lcd_chars[y][x] = c[i];

		}
	}
	else {

		string1 = string.substr(0, 16 - x);
		if ((string.size() - (16 - x)) >= 16) {
			string2 = string.substr(16 - x, 16);

		}
		else {
			string2 = string.substr(16 - x, string.size() - (16 - x));
		}

		for (int i = 0;i < string1.size();i++) {

			lcd_chars[y][x] = c[i];
		}
		if (y = 0) {
			for (int i = 0;i < string2.size();i++) {

				lcd_chars[y + 1][x + string1.size()] = c[i];

			}
		}
		cadd = cadd += string.size();

	};

	return *this;






}

void AllegroLCD::display_char(char c,int x, int y)
{
	al_draw_text(font, al_color_name("black"), X + x*x_cuadrado, Y + y*y_cuadrado, 0, &c);
}

void AllegroLCD::display_chars(char* c, int x, int y)
{
	al_draw_text(font, al_color_name("black"), X + x * x_cuadrado, Y + y * y_cuadrado, 0, c);
}


bool AllegroLCD::lcdMoveCursorRight() {
	if (cadd != 32) {
		cadd += 1;
		return true;
	}
	else {
		return false;
	}
}
bool AllegroLCD::lcdMoveCursorLeft() {
	if (cadd != 0 ) {
		cadd -= 1;
		return true;
	}
	else {
		return false;
	}
}
bool AllegroLCD::lcdClearToEOL() { 
	return true;
}
bool AllegroLCD::lcdClear() {


	bool result = true;
	int x, y;

	for (int i = 0; i < 32; i++) {

		if (i < 32 && i >= 0) {
			if (i >= 16) {
				x = i - 16;
			}
			else {
				x = i;
			}
			if (i >= 16) {
				y = 1;
			}
			else {
				y = 0;
			}
			lcd_chars[y][x] = ' ';
		}
		else { result = false; };
	}
	cadd = 1;
	return result;

}
bool AllegroLCD::lcdSetCursorPosition(const cursorP po) {

	if (po.y > 0 && po.x > 0 && po.y <= 2 && po.x <= 16) {
		cadd = (po.y - 1) * 16 + po.x;
		return true;
	}
	else return false;
}
int AllegroLCD::lcdGetCusorPosition() {

	return 6;
}


void loading(BasicLCD* lcd, int downloadedTwts) {



	for (int j = 0;j < downloadedTwts; j++ ) {

			lcd_chars[1][j] = '0';

	}
	update_board(lcd);

}


void update_board(BasicLCD* lcd)
{
	int i, j;

	for (i =0; i <= 2; i++) {

		for (j = 0; j <= 16; j++) {
			po.x = j+1;
			po.y = i+1;
			lcd->lcdSetCursorPosition(po);
			check_lcd(lcd,i, j);	
		}

	}
	al_flip_display();
}

void check_lcd(BasicLCD* lcd, int x, int y)
{
	const char c = lcd_chars[x][y];

	if (isAlpha(c) || isNum(c)) {
		(*lcd) << c;
	}
	else
	{
		*lcd << '*';
	}
}

