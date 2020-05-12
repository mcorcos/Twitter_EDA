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

void update_board(BasicLCD* lcd);
void check_lcd(BasicLCD* lcd,int x, int y);
void loading(BasicLCD* lcd, int dowloadedTwts);

class AllegroLCD : public BasicLCD {
public:
	AllegroLCD(void);
	~AllegroLCD(void);
	virtual bool lcdInitOK();
	virtual bool lcdGetError();
	virtual bool lcdMoveCursorUp();
	virtual bool lcdMoveCursorDown();
	virtual bool lcdMoveCursorRight();
	virtual bool lcdMoveCursorLeft();
	virtual bool lcdClearToEOL();
	virtual bool lcdClear();
	virtual bool lcdSetCursorPosition(const cursorP po);
	int lcdGetCusorPosition();
	BasicLCD& operator<< (const unsigned char c);
	BasicLCD& operator<< (const unsigned char* c);
	void display_char(char c,int x , int y);
	void display_chars(char* c, int x, int y);

private:

	ALLEGRO_BITMAP* espacio = nullptr;
	ALLEGRO_BITMAP* lcd_simul = nullptr;
	ALLEGRO_FONT* font = nullptr;

	int close_display = 0;
	bool result;
	int cadd;
};