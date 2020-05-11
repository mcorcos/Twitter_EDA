//#include <iostream>
//#include "graphiclcd.h"
//
//#include <string>
//
//
//#define FPS    60.0
//
//#define WIDTH 676   
//#define HEIGHT 281
//#define x_cuadrado 32
//#define y_cuadrado 47
//#define X 82
//#define Y 94
//#define LETRAS_ALPH 27
//#define NUMS 9
//#define isAlpha(a)  ( ( ('a'<= (a)) && ('z' >= (a)) ) || ( ('A'<= (a)) && ('Z' >= (a)) ) )
//#define isNum(a)     ( ('0'<= (a)) && ('9' >= (a)) )
//
//
//extern allegroLCD lcd;
//
//
//allegroLCD::~allegroLCD()
//{
//
//
//
//
//
//    if (display)
//        al_destroy_display(display);
//
//    if (lcd_simul)
//        al_destroy_bitmap(lcd_simul);
//
//    if (event_queue) {
//        al_destroy_event_queue(event_queue);
//    }
//    al_shutdown_primitives_addon();
//
//
//
//}
//
//allegroLCD::allegroLCD() {
//    result=lcdInitOK();
//}
//
//
//bool allegroLCD::lcdGetError() {
//    if (result) {
//        return FT_ok;
//    }
//    else {
//        return FT_err;
//    }
//}
//
//
//
//bool allegroLCD::lcdMoveCursorUp() {
//    if (cadd > 16) {
//        cadd -= 16;
//        return true;
//    }
//    else {
//        return false;
//    }
//}
//
//bool allegroLCD::lcdMoveCursorDown() {
//    if (cadd < 16) {
//        cadd += 16;
//        return true;
//    }
//    else {
//        return false;
//    }
//}
//
//
//
//
//bool allegroLCD::lcdInitOK() {
//
//
//
//    if (!al_init()) {        //inicializacion general del allegro
//        fprintf(stderr, "error al inicializar el allegro\n");
//        return false;
//    }
//
//
//    event_queue = al_create_event_queue();       //se inicializa los eventos
//
//    if (!event_queue) {                         //se controla si fallo la init de los eventos
//        fprintf(stderr, "failed to create event_queue!\n");
//        return false;
//    }
//
//
//    if (!al_init_primitives_addon()) {       //se controla si fallo la inicializacion de las primitivas
//        fprintf(stderr, "error al inicializar las primitivas\n");
//        return false;
//    }
//
//    if (!al_init_image_addon()) { // necesario para manejo de imagenes 
//        fprintf(stderr, "failed to initialize image addon !\n");
//        return false;
//    }
//
//    if (!al_init_font_addon()) { // necesario para manejo de fuentes de letras
//        fprintf(stderr, "failed to initialize font addon !\n");
//        return false;
//    }
//
//
//    if (!al_init_ttf_addon()) { // necesario para manejo de fuentes de letras
//        fprintf(stderr, "failed to initialize font addon !\n");
//        return false;
//    }
//
//
//
//    al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);
//    display = al_create_display(676, 281);
//
//    //se crea el display
//
//    al_register_event_source(event_queue, al_get_display_event_source(display)); //se registra la fuente de los eventos de cierre de display
//
//    if (!display) {//creo display
//        al_shutdown_primitives_addon();      //se destruye la imagen porque ocupa espacio en heap y el programa fallo por otro motivo
//        fprintf(stderr, "failed to create display");
//
//        return false;
//    }
//
//    lcd_simul = al_load_bitmap("lcd.bmp");
//
//
//    if (!lcd_simul) {
//        fprintf(stderr, "failed to load image lcd !\n");
//        return false;
//    }
//
//    font = al_load_font("font.ttf",24,0);
//
//    if (!font) {
//        fprintf(stderr, "failed to load font !\n");
//        return false;
//    }
//
//    al_draw_bitmap(lcd_simul, 0, 0, 0);          //se pinta las dos caras del display con lcd 
//    al_flip_display();
//    al_draw_bitmap(lcd_simul, 0, 0, 0);
//
//
//    return true;
//}
//
//
//
//void allegroLCD::update_board() { // funcion principal en el juego
//                                                                                                         // esta funcion actualiza el floor y lo imprime en pantalla
//
//    int i, j;
//
//    for (i = 0;i < 2;i++) {
//
//        for (j = 0;j < 16;j++) {
//
//            check_lcd(i, j);
//
//        }
//
//    }
//    al_flip_display();
//
//}
//
//
//void allegroLCD::check_lcd(int x, int y) {
//
//    const char c = lcd_chars[x][y];
//
//    if (isAlpha(c) || isNum(c)) {
//
//        lcd << c;
//    }
//
//}
//
//
//allegroLCD& allegroLCD::operator<< (const unsigned char c) {
//
//    display_char(c);
//    return *this;
//
//}
//
//allegroLCD& allegroLCD::operator<< (const unsigned char* c) {
//
//    display_chars((char*)c);
//    return *this;
//}
//
//
//void allegroLCD::display_char(char c) {
//
//
//    al_draw_text(font, al_color_name("black"), 50, 40, 0, &c);
//
//}
//
//void allegroLCD::display_chars(char* c) {
//
//    al_draw_text(font, al_color_name("black"), 50, 40, 0, c);
//
//}
//
