#include <stdio.h>
#include <stdlib.h>
#include "load.h"
#include "juego.h"
#include "interfaces.h"


int main() {
    printf( "                     \n\n\n                                           |====================================================================|\n" );
    printf( "                                           |                                                                    |\n" );
    printf( "                                           |                    Bienvenido a Hundir la Flota                    |\n" );
    printf( "                                           |                                                                    |\n" );
    printf( "                                           |====================================================================|\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );

    cargarBarcos();
    inicializarValoresaCero();

    system( "pause" );
    
    
    MenuInicio();


    free(jugador);
    free(barco);
    free(tablero);
    free(disparo);
    free(barcopartida);

    return 0;
}
