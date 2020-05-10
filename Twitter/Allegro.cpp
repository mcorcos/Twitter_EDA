#include <iostream>
#include "Allegro.h"


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


Graphic::~Graphic()
{
}


int Graphic::inicializacion() {



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



    al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);
    display = al_create_display(676,281);

    //se crea el display

    al_register_event_source(event_queue, al_get_display_event_source(display)); //se registra la fuente de los eventos de cierre de display

    if (!display) {//creo display
        al_shutdown_primitives_addon();      //se destruye la imagen porque ocupa espacio en heap y el programa fallo por otro motivo
        fprintf(stderr, "failed to create display");

        return -1;
    }

    lcd = al_load_bitmap("lcd.bmp");

    if (!lcd) {
        fprintf(stderr, "failed to load image lcd !\n");
        return -1;
    }


    init_bitmaps();

    al_draw_bitmap(lcd,0,0,0);          //se pinta las dos caras del display con lcd 
    al_flip_display();
    al_draw_bitmap(lcd, 0, 0, 0);


    return 0;
}












void Graphic::erase_events(void) {
    al_flush_event_queue(event_queue);
}

void Graphic::init_bitmaps(void) {

    using std::string;

    string name = "fonts/letra_";
    string tempstr;
    char tempchar[30];


    for (int i = 0; i < LETRAS_ALPH ; i++) {


        char c = i + 'a';

        tempstr = name + c + ".png";

        char* filename = strcpy(tempchar, tempstr.c_str());
        al_bitmaps[i] = al_load_bitmap(filename);
        cout << filename << endl;
        if (!al_bitmaps[i]) {
            fprintf(stderr, "failed to load image al_bitmaps[%d] !\n",i);
        }

    }

    name = "fonts/numero";

    for (int i = 0; i < NUMS; i++) {

        tempstr = name + std::to_string(i) + ".png";

        char * filename = strcpy(tempchar, tempstr.c_str());
        Num_bitmaps[i] = al_load_bitmap(filename);

    }
}



void Graphic::close_window(void) { // funcion que desinstala los plugins de alegro



    al_destroy_bitmap(lcd);       //se libera la memoria dinamica , destruyendo los elemntos usados
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_shutdown_primitives_addon();
    printf("bye\n");


}

void Graphic::update_board() { // funcion principal en el juego
                                                                                                         // esta funcion actualiza el floor y lo imprime en pantalla

    int i, j;

    for (i = 0;i < 2;i++) {

        for (j = 0;j < 16;j++) {

            check_lcd(i,j);

        }

    }
    al_flip_display();

}



void Graphic::check_lcd(int x, int y) {
    
    char c = lcd_chars[x][y];

    if(isAlpha(c)){

            drawalpha(x, y);
    }
    if (isNum(c)) {
        
        drawNum(x, y);

    }
}


void Graphic::drawalpha(int x, int y) {
    char alpha = lcd_chars[x][y];
    int a = alpha - 'A';
    al_draw_bitmap(al_bitmaps[a], X + y * x_cuadrado, Y + x * y_cuadrado, 0);

}



void Graphic::drawNum(int x, int y) {

    char Num = lcd_chars[x][y];
    Num -= '0';

    al_draw_bitmap(Num_bitmaps[Num], X + x * x_cuadrado, Y + y * y_cuadrado, 0);

}











