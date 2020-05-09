#include <iostream>

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


#define FPS    60.0

#define CUADRADITO_SIZE 20
#define MOVE_RATE  4.0

#define WIDTH 676   
#define HEIGHT 281
#define x_cuadrado 33
#define y_cuadrado 47
#define X 82
#define Y 94

ALLEGRO_DISPLAY* display;  //punteros que apuntan a un estructuras de allegro, se los apuntan a NULL para controlar errores
ALLEGRO_BITMAP* lcd;
ALLEGRO_BITMAP* Al_bitmaps[27];
ALLEGRO_BITMAP* al_bitmaps[27];
ALLEGRO_BITMAP* Num_bitmaps[9];
ALLEGRO_EVENT_QUEUE* event_queue;

ALLEGRO_EVENT ev;

ALLEGRO_BITMAP* lcd = nullptr;

int close_display = 0;

char lcd_chars[16][16];


int inicializacion() {



    if (!al_init()) {        //inicializacion general del allegro
        fprintf(stderr, "error al inicializar el allegro\n");
        return -1;
    }


    event_queue = al_create_event_queue();       //se inicializa los eventos

    if (!event_queue) {                         //se controla si fallo la init de los eventos
        fprintf(stderr, "failed to create event_queue!\n");
        return -1;
    }


    if (!al_init_primitives_addon()) {       //se controla si fallo la inicializacion de las primitivas
        fprintf(stderr, "error al inicializar las primitivas\n");
        return -1;
    }

    if (!al_init_image_addon()) { // necesario para manejo de imagenes 
        fprintf(stderr, "failed to initialize image addon !\n");
        return -1;
    }

    if (!al_init_ttf_addon()) { // necesario para manejo de fuentes de letras
        fprintf(stderr, "failed to initialize font addon !\n");
        return -1;
    }

    display = al_create_display(WIDTH,HEIGHT);

    //se crea el display

    al_register_event_source(event_queue, al_get_display_event_source(display)); //se registra la fuente de los eventos de cierre de display

    if (!display) {//creo display
        al_shutdown_primitives_addon();      //se destruye la imagen porque ocupa espacio en heap y el programa fallo por otro motivo
        fprintf(stderr, "failed to create display");

        return -1;
    }

    lcd = al_load_bitmap("lcd.png");

    if (!lcd) {
        fprintf(stderr, "failed to load image lcd !\n");
        return -1;
    }

    al_draw_bitmap(lcd,0,0,0);          //se pinta las dos caras del display con lcd 
    al_flip_display();
    al_draw_bitmap(lcd, 0, 0, 0);


    return 0;
}

void erase_events(void) {
    al_flush_event_queue(event_queue);
}






void close_window(void) { // funcion que desinstala los plugins de alegro



    al_destroy_bitmap(imagen);       //se libera la memoria dinamica , destruyendo los elemntos usados
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_shutdown_primitives_addon();
    printf("bye\n");


}

void update_board() { // funcion principal en el juego
                                                                                                         // esta funcion actualiza el floor y lo imprime en pantalla

    int i, j;

    for (i = 0;i < 16;i++) {

        for (j = 0;j < 16;j++) {

            check_lcd(i,j);

        }

    }
    al_draw_rectangle(0, 0, board_width * 100, board_height * 100, al_map_rgb(70, 70, 70), 3);
    al_flip_display();

}

void print_robot(double y, double x) {

    int xp = (int)(x * 100);
    int yp = (int)(y * 100);
    al_draw_bitmap(robot_img, xp, yp, 0);
    al_flip_display();
}





void chech_lcd(int x, int y) {
    
    if(isAlpha(lcd[x][y])){

        drawAlpha(x, y);

    }
    else(isNum(lcd[x][y])) {
        
        drawNum(x, y);

    }
}


void drawalpha(int x, int y) {
    
    char alpha = lcd_chars[x][y];
    alpha -= 97;

    al_draw_bitmap(al_bitmaps[alpha], X + x * x_cuadrado, Y + y * y_cuadrado, 0);

}

void drawAlpha(int x, int y) {

    char alpha = lcd_chars[x][y];
    alpha -= 65;

    al_draw_bitmap(Al_bitmaps[alpha], X + x * x_cuadrado, Y + y * y_cuadrado, 0);

}


void drawNum(int x, int y) {

    char Num = lcd_chars[x][y];
    Num -= 48;

    al_draw_bitmap(Num_bitmaps[Num], X + x * x_cuadrado, Y + y * y_cuadrado, 0);

}