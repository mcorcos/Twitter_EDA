#include <iostream>
#include "allegroEngine.h"


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_color.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>


#define FPS    60.0

#define CUADRADITO_SIZE 20
#define MOVE_RATE  4.0



ALLEGRO_DISPLAY* display;  //punteros que apuntan a un estructuras de allegro, se los apuntan a NULL para controlar errores
ALLEGRO_BITMAP* imagen;
ALLEGRO_EVENT_QUEUE* event_queue;

ALLEGRO_EVENT ev;

ALLEGRO_BITMAP* robot_img = NULL;
ALLEGRO_BITMAP* N0 = NULL;
ALLEGRO_BITMAP* N1 = NULL;
ALLEGRO_BITMAP* N2 = NULL;
ALLEGRO_BITMAP* N3 = NULL;
ALLEGRO_BITMAP* N4 = NULL;
ALLEGRO_BITMAP* N5 = NULL;
ALLEGRO_BITMAP* N6 = NULL;
ALLEGRO_BITMAP* N7 = NULL;
ALLEGRO_BITMAP* N8 = NULL;
ALLEGRO_BITMAP* N9 = NULL;




int close_display = 0;

int inicializacion(int width, int height) {



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


    display = al_create_display(width * 100, height * 100);

    //se crea el display

    al_register_event_source(event_queue, al_get_display_event_source(display)); //se registra la fuente de los eventos de cierre de display

    if (!display) {//creo display
        al_shutdown_primitives_addon();      //se destruye la imagen porque ocupa espacio en heap y el programa fallo por otro motivo
        fprintf(stderr, "failed to create display");

        return -1;
    }

    robot_img = al_load_bitmap("robot_img.png");

    if (!robot_img) {
        fprintf(stderr, "failed to load image robot_img !\n");
        return -1;
    }
    N0 = al_load_bitmap("N0.bmp");

    if (!N0) {
        fprintf(stderr, "failed to load image N0 !\n");
        return -1;
    }
    N1 = al_load_bitmap("N1.bmp");

    if (!N1) {
        fprintf(stderr, "failed to load image N1 !\n");
        return -1;
    }
    N2 = al_load_bitmap("N2.bmp");

    if (!N2) {
        fprintf(stderr, "failed to load image N2 !\n");
        return -1;
    }
    N3 = al_load_bitmap("N3.bmp");

    if (!N3) {
        fprintf(stderr, "failed to load image N3 !\n");
        return -1;
    }
    N4 = al_load_bitmap("N4.bmp");

    if (!N4) {
        fprintf(stderr, "failed to load image N4 !\n");
        return -1;
    }
    N5 = al_load_bitmap("N5.bmp");

    if (!N5) {
        fprintf(stderr, "failed to load image N5 !\n");
        return -1;
    }
    N6 = al_load_bitmap("N6.bmp");

    if (!N6) {
        fprintf(stderr, "failed to load image N6 !\n");
        return -1;
    }
    N7 = al_load_bitmap("N7.bmp");

    if (!N7) {
        fprintf(stderr, "failed to load image N7 !\n");
        return -1;
    }
    N8 = al_load_bitmap("N8.bmp");

    if (!N8) {
        fprintf(stderr, "failed to load image N8 !\n");
        return -1;
    }
    N9 = al_load_bitmap("N9.bmp");

    if (!N9) {
        fprintf(stderr, "failed to load image N9 !\n");
        return -1;
    }


    al_clear_to_color(al_color_name("white"));          //se pinta las dos caras del display con blanco
    al_flip_display();
    al_clear_to_color(al_color_name("white"));

    return 0;
}

void erase_events(void) {
    al_flush_event_queue(event_queue);
}


void create_tablero(int width, int height) {           //se crea el grafico 
    int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {

            al_draw_filled_rectangle(100 * j, 100 * i, 100 * (j + 1), (i + 1) * 100, al_map_rgb(220, 220, 220));
            al_draw_rectangle(100 * j, 100 * i, 100 * (j + 1), (i + 1) * 100, al_map_rgb(0, 0, 0), 0);

        }
    }
    al_draw_rectangle(0, 0, width, height, al_map_rgb(70, 70, 70), 3);
    al_flip_display();

}

void create_graph(double* t_medio, int last_n) {
    int i;

    for (i = 0; i < last_n; i++) {
        //draw v_medio
    }
}



void close(void) { // funcion que desinstala los plugins de alegro



    al_destroy_bitmap(imagen);       //se libera la memoria dinamica , destruyendo los elemntos usados
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_shutdown_primitives_addon();
    printf("bye\n");


}

void update_board(int board_height, int board_width, bool* my_floor) { // funcion principal en el juego
                                                                                                         // esta funcion actualiza el floor y lo imprime en pantalla
    int i, j, numero, k;
    static int tick = 0;

    for (i = 0;i < board_height;i++) {

        for (j = 0;j < board_width;j++) {

            if (my_floor[i * board_width + j]) {


                al_draw_filled_rectangle(board_width * 100 * j / 25, board_height * 100 * i / 19, board_width * 100 * (j + 1) / 25, board_height * 100 * (i + 1) / 19, al_color_name("brown"));
                al_draw_rectangle(board_width * 100 * j / 25, board_height * 100 * i / 19, board_width * 100 * (j + 1) / 25, board_height * 100 * (i + 1) / 19, al_map_rgb(70, 70, 70), 0);


            }

        }

    }
    // imprimo la cantidad de ticks
    for (k = ((board_width * 100) - 10), i = 0;i < 5;i++) {

        numero = tick % 10;
        switch (numero) {

        case 0: al_draw_bitmap(N0, k, ((board_height * 100) - 10), 0);
            al_flip_display();
            break;
        case 1: al_draw_bitmap(N1, k, ((board_height * 100) - 10), 0);
            al_flip_display();
            break;
        case 2: al_draw_bitmap(N2, k, ((board_height * 100) - 10), 0);
            al_flip_display();
            break;
        case 3: al_draw_bitmap(N3, k, ((board_height * 100) - 10), 0);
            al_flip_display();
            break;
        case 4: al_draw_bitmap(N4, k, ((board_height * 100) - 10), 0);
            al_flip_display();
            break;
        case 5: al_draw_bitmap(N5, k, ((board_height * 100) - 10), 0);
            al_flip_display();
            break;
        case 6: al_draw_bitmap(N6, k, ((board_height * 100) - 10), 0);
            al_flip_display();
            break;
        case 7: al_draw_bitmap(N7, k, ((board_height * 100) - 10), 0);
            al_flip_display();
            break;
        case 8: al_draw_bitmap(N8, k, ((board_height * 100) - 10), 0);
            al_flip_display();
            break;
        case 9: al_draw_bitmap(N9, k, ((board_height * 100) - 10), 0);
            al_flip_display();
            break;
        }
        tick /= 10;
        k -= 15;
    }

    al_draw_rectangle(0, 0, board_width * 100, board_height * 100, al_map_rgb(70, 70, 70), 3);
    al_flip_display();

}

void print_robot(double x, double y) {

    int xp = (int)(x * 100);
    int yp = (int)(y * 100);
    al_draw_bitmap(robot_img, xp, yp, 0);
    al_flip_display();

}