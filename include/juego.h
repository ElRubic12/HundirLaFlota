#ifndef JUEGO_H
#define JUEGO_H

typedef struct
{
  int x;
  int y;
}Disparos;

extern Disparos *disparo;

typedef struct{
  int Posicion_inicial_X[50];
  int Posicion_final_x[50];
  int Posicion_inicial_Y[50];
  int Posicion_final_Y[50];
  int Tamano_barco[50];
  char Hundido[50];
}BarcosPartida;

extern BarcosPartida *barcopartida;


void jugarPartida();
void loop();
int generarNumaleatorio( int op );
int comprobarDisparo( int jugador, int cont_disparos );
void actualizarTableroOponente( int oponente, char casilla, int cont_disparos, int flota );
void actualizarTableroSiHundido( int oponente );
int comprobarGanador( int turno );
void jugar_turno( int turno, int cont_disparos );
void generacionFlota( int jugador, int indice );
void mostrarTablero( int jugador );
void generarTableroManual( int jugador );
void generarTableroAleatorio( int jugador );
int comprobarPosicion( int x, int y, char orientacion, char sentido, char sentido_diagonal, int jugador, int tam_barco );
int comprobarPosicionBase( int x, int y, int jugador );
void anadirBarcoFlota( int jugador, int x, int y, char orientacion, char sentido, char sentido_diagonal, int tam_barco, int contador_numero_barcos );
void mostrarResumen();
void reiniciarPartida();
void inicializarTiposBarcos();
void AlmacenarPosicionesBarcos();
void detectarBarco( char matriz[50][50], int x, int y, int *tamano, int *firstX, int *firstY, int *lastX, int *lastY );

#endif
