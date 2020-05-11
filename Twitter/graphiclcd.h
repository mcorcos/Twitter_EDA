//
//#include <allegro5/allegro.h>
//#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_primitives.h> 
//#include <allegro5/allegro_color.h>
//#include <allegro5/allegro5.h>
//#include <allegro5/allegro_acodec.h>
//#include <allegro5/allegro_audio.h>
//#include <allegro5/allegro_native_dialog.h>
//#include <allegro5/allegro_font.h>
//#include <allegro5/allegro_ttf.h>
//
//
//
//
//struct cursorP {
//
//    int x;
//    int y;
//
//};
//
//#define FT_ok true
//#define FT_err false
//
//
//using namespace std;
//
//
//
//
//
//
//class basicLCD {
//public:
//    virtual ~basicLCD() {};
//    virtual bool lcdInitOK() = 0;
//    virtual bool lcdMoveCursorUp() = 0;
//    virtual bool lcdMoveCursorDown() = 0;
//    virtual bool lcdMoveCursorRight() = 0;
//    virtual bool lcdMoveCursorLeft() = 0;
//    virtual bool lcdClearToEOL() = 0;
//    virtual bool lcdGetError() = 0;
//    virtual bool lcdClear() = 0;
//    virtual basicLCD& operator<< (const unsigned char c) = 0;
//    virtual basicLCD& operator<<(const unsigned char* c) = 0;
//    virtual bool lcdSetCursorPosition(const cursorP)=0;
//private:
//    unsigned int cadd;
//
//};
//
//
//
//class allegroLCD : public basicLCD {
//public:
//    allegroLCD();
//    ~allegroLCD();
//    bool lcdInitOK();
//    bool lcdGetError();
//    bool lcdMoveCursorUp();
//    bool lcdMoveCursorDown();
//    bool lcdMoveCursorRight();
//    bool lcdMoveCursorLeft();
//    bool lcdClearToEOL();
//    bool lcdClear();
//    bool lcdSetCursorPosition(const cursorP po);
//    cursorP lcdGetCusorPosition();
//    allegroLCD& operator<< (const unsigned char c);
//    allegroLCD& operator<< (const unsigned char* c);
//    void update_board();
//    void check_lcd(int x, int y);
//    void display_char(char c);
//    void display_chars(char* c);
//
//private:
//
//    ALLEGRO_DISPLAY* display = nullptr;  //punteros que apuntan a un estructuras de allegro, se los apuntan a NULL para controlar errores
//    ALLEGRO_EVENT_QUEUE* event_queue;
//    ALLEGRO_EVENT ev;
//
//    ALLEGRO_BITMAP* loading_bitmaps[4];
//    ALLEGRO_BITMAP* al_bitmaps[27];
//    ALLEGRO_BITMAP* Num_bitmaps[9];
//    ALLEGRO_BITMAP* lcd_simul = nullptr;
//    ALLEGRO_FONT* font = nullptr;
//
//    int close_display = 0;
//    bool result;
//    char lcd_chars[2][16];
//    int cadd;
//};
//
