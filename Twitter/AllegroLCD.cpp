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
	if (lcd_simul)
		al_destroy_bitmap(lcd_simul);

	al_shutdown_primitives_addon();
}

bool AllegroLCD::lcdInitOK()
{

	al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);

	lcd_simul = al_load_bitmap("lcd.bmp");


	if (!lcd_simul) {
		fprintf(stderr, "failed to load image lcd !\n");
		return false;
	}

	espacio = al_load_bitmap("espacio.png");


	if (!espacio) {
		fprintf(stderr, "failed to load image espacio !\n");
		return false;
	}

	font = al_load_font("font.ttf", 38, 0);

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
		y = 1;
	}
	else {
		y = 0;
	}
	if (c == ' ') {

		al_draw_bitmap(espacio, X + x * x_cuadrado, Y + y * y_cuadrado, 0);

	}
	else if (c == '*') {
		display_char(c, x, y);
	}
	else if (c == '-') {
		display_char(c, x, y);
	}
	else if (c == ':') {
		display_char(c, x, y);
	}
	else if (c == '.' || c == '/') {
		display_char(c, x, y);
	}
	else if (isAlpha(c) || isNum(c)) {
		display_char(c, x, y);
	}

	if (lcdMoveCursorRight()) {

	}
	else {
		cadd = 1;
	}
	return *this;
}

BasicLCD& AllegroLCD::operator<<(const unsigned char* c)
{
	//int x, y, pos;
	//display_chars((char*)c,x,y);

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


	if ((16 - x) >= string.size()) {

		cadd = cadd += string.size();
		for (int i = 0; i < string.size(); i++) {

			lcd_chars[y][i] = c[i];

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


		for (int i = 0; i < string1.size(); i++) {

			lcd_chars[y][i] = c[i];
		}

		if (y == 0) {
			for (int i = 0; i < string2.size(); i++) {

				lcd_chars[y + 1][i] = c[i + string1.size()];

			}
		}
		cadd = cadd += string.size();

		if (cadd > 32) { cadd = 1; }

	};

	return *this;






}

void AllegroLCD::display_char(char c, int x, int y)
{
	al_draw_text(font, al_color_name("black"), X + x * x_cuadrado, Y + y * y_cuadrado, 0, &c);
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
	if (cadd != 0) {
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


	po.x = 1;
	po.y = 1;
	lcd->lcdSetCursorPosition(po);
	*lcd << (unsigned char*)"downloading";

	for (int j = 0; j < downloadedTwts / 2; j++) {

		lcd_chars[1][j] = '0';
		if (j > 0) {
			lcd_chars[1][j - 1] = ' ';
		}

		al_rest(0.05);
		update_board(lcd);

	}
	for (int j = 0; j < downloadedTwts / 2; j++) {

		lcd_chars[1][j] = ' ';

	}
	update_board(lcd);

}


void update_board(BasicLCD* lcd)
{
	int i, j;

	for (i = 0; i <= 2; i++) {

		for (j = 0; j <= 16; j++) {
			po.x = j + 1;
			po.y = i + 1;
			lcd->lcdSetCursorPosition(po);
			check_lcd(lcd, i, j);
		}

	}
	al_flip_display();
}

void check_lcd(BasicLCD* lcd, int x, int y)
{
	const char c = lcd_chars[x][y];
	(*lcd) << c;
}
