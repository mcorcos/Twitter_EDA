#pragma once
#include "BasicLCD.h"
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
#include <string>

#define FPS    60.0

#define WIDTH 676   
#define HEIGHT 281
#define x_cuadrado 32
#define y_cuadrado 47
#define X 82
#define Y 94
#define LETRAS_ALPH 27
#define NUMS 9
#define isAlpha(a)  ( ( ('a'<= (a)) && ('z' >= (a)) ) || ( ('A'<= (a)) && ('Z' >= (a)) ) )
#define isNum(a)     ( ('0'<= (a)) && ('9' >= (a)) )

#define FT_ok true
#define FT_err false


using namespace std;

class AllegroLCD : public BasicLCD {
public:
	AllegroLCD();
	~AllegroLCD();
	bool lcdInitOK();
	bool lcdGetError();
	bool lcdMoveCursorUp();
	bool lcdMoveCursorDown();
	bool lcdMoveCursorRight();
	bool lcdMoveCursorLeft();
	bool lcdClearToEOL();
	bool lcdClear();
	bool lcdSetCursorPosition(const cursorP po);
	cursorP lcdGetCusorPosition();
	AllegroLCD& operator<< (const unsigned char c);
	AllegroLCD& operator<< (const unsigned char* c);
	void update_board();
	void check_lcd(int x, int y);
	void display_char(char c);
	void display_chars(char* c);

private:

	ALLEGRO_DISPLAY* display = nullptr;  //punteros que apuntan a un estructuras de allegro, se los apuntan a NULL para controlar errores
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_EVENT ev;

	ALLEGRO_BITMAP* loading_bitmaps[4];
	ALLEGRO_BITMAP* al_bitmaps[27];
	ALLEGRO_BITMAP* Num_bitmaps[9];
	ALLEGRO_BITMAP* lcd_simul = nullptr;
	ALLEGRO_FONT* font = nullptr;

	int close_display = 0;
	bool result;
	char lcd_chars[2][16];
	int cadd;
};