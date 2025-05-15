#ifndef _LOAD_H_
#define _LOAD_H_


typedef struct{       ///Estructura para almacenar los tipos de barcos que existen
    char Nomb_barco[20];
	char Id_barco;
	int Tam_barco;
}Barcos;

extern Barcos *barco;

typedef struct{       ///Estructura para almecenar los datos de los jugadores
	int Id_jugador;
	char Nomb_jugador[20];
	int Num_disparo;
	char Tipo_disparo[20];
	int Indicador;
}Jugadores;

extern Jugadores *jugador;

typedef struct{                        ///Estructura para almacenar los datos de los tableros
    int Tam_tablero;                   ///Tamaño del tablero(nxn)
    int Num_barcos;                    ///Numero de barcos que hay en cada flota 
    int Num_tipos_barcos;              ///Numero de tipos de barcos que hay en cada flota(Portaaviones, Destructor y Fragata. Num_tipos_barcos=3)
                                       ///Variables de barcos para indicar el numero de estos barcos que hay en cada tablero
    ///Numero de barcos de cada tipo
    int Portaaviones;
    int Acorazado;
    int Crucero;
    int Destructor;
    int Fragata;
    int Submarino;

    char Tipos_barcos[6];               ///Variable que almacena en cada posicion los tipos de barcos dependiendo de Num_tipos_barcos(Tipo_barco[0]='P', Tipo_barco=[1]='D')
    int Jugador_inicial_continuador;    ///Variable que almacena un numero(1 o 2) que identifica al jugador que comienza o continua la partida despues de cargarla
}Partidas;

extern Partidas partida;

typedef struct{
    char Matriz_tablero[50][50];
}Tableros;

extern Tableros *tablero;


void inicializarValores();
void cargarBarcos();
void cargarJuego();
void inicializarTiposBarcos();
void inicializarValoresaCero();
void almacenarJuego();

#endif