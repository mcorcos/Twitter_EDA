
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

using namespace std;


class Graphic
{
public:

	~Graphic();


	int inicializacion();
	void erase_events(void);
	void close_window(void);
	void update_board();
	void check_lcd(int x, int y);
	void drawalpha(int x, int y);
	void drawNum(int x, int y);
	void init_bitmaps(void);



	ALLEGRO_DISPLAY* display=nullptr;  //punteros que apuntan a un estructuras de allegro, se los apuntan a NULL para controlar errores
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_EVENT ev;


	ALLEGRO_BITMAP* al_bitmaps[27];
	ALLEGRO_BITMAP* Num_bitmaps[9];
	ALLEGRO_BITMAP* lcd = nullptr;

	int close_display = 0;

	char lcd_chars[2][16] = {
	   'H','O','L','A','I','Q','U','E'
	};

};

