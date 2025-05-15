#include <stdio.h>
#include <stdlib.h>

#include "juego.h"
#include "configuracion.h"
#include "load.h"
#include "interfaces.h"


void MenuInicio()
{
    int op;
    char c;

    system( "cls" );
    printf( "\n\n\n" );
    do{
        printf( "                                                                |======HUNDIR LA FLOTA=======|\n" );
        printf( "                                                                |                            |\n" );
        printf( "                                                                |       1-Configuracion      |\n" );
        printf( "                                                                |          2-Jugar           |\n" );
        printf( "                                                                |          3-Salir           |\n" );
        printf( "                                                                |                            |\n" );
        printf( "                                                                |============================|\n" );

        if( scanf("%d", &op) != 1 ) {  
            ///Si scanf no lee un numero, limpia el bufer y reinicia op
            while( (c = getchar()) != '\n' && c != EOF ); 
            op = 0;  
            printf( "Entrada invalida. Introduce un numero entre 1 y 3.\n" );
        }
    }while( op < 1 || op > 3 );

    switch( op )
    {
    case 1:
        MenuConfiguracion();                ///En interfaces.c
        break;
    case 2:
        MenuJuego();                        ///En juego.c
        break;
    case 3:
        printf( "\n\n==============================SALIENDO...================================\n\n\n" );
        break;
    }

    if( op != 3 )
    {
        MenuInicio();
    }

}
void MenuConfiguracion()
{
    int op;
    char c;

    system( "cls" );
    printf( "\n\n\n" );
    do{
        printf( "                                                                |======HUNDIR LA FLOTA=======|\n" );
        printf( "                                                                |                            |\n" );
        printf( "                                                                |     1-Introducir Datos     |\n" );
        printf( "                                                                |          2-Mostrar         |\n" );
        printf( "                                                                |          3-Borrar          |\n" );
        printf( "                                                                |          4-Guardar         |\n" );
        printf( "                                                                |          5-Cargar          |\n" );
        printf( "                                                                |          6-Volver          |\n" );
        printf( "                                                                |                            |\n" );
        printf( "                                                                |============================|\n" );

        if( scanf("%d", &op) != 1 ) {  
            ///Si scanf no lee un numero, limpia el bufer y reinicia op
            while( (c = getchar()) != '\n' && c != EOF ); 
            op = 0;  
            printf( "Entrada invalida. Introduce un numero entre 1 y 6.\n" );
        }
    }while( op < 1 || op > 6 );

    switch( op )
    {
    case 1:
        Menu_Conf_Introducir_Datos();           ///En configuracion.c
        break;
    case 2:
        mostrarConfiguracion();                 ///En configuracion.c
        break;
    case 3:
        borrarConfiguracion();                  ///En configuracion.c
        break;
    case 4:
        almacenarJuego();                       ///En load.c
        printf( "\n\nSe ha guardado correctamente el fichero.\n\n" );
        system( "pause" );
        break;
    case 5:
        cargarJuego();                          ///En load.c
        inicializarTiposBarcos();               ///En load.c
        system( "pause" );
        break;
    case 6:
        MenuInicio();                           ///En interfaces.c
        break;
    }

    MenuConfiguracion();                        ///En interfaces.c

}

void MenuJuego()
{
    int op;
    char c;

    system( "cls" );
    printf ( "\n\n" );
    do{
        printf( "                                                                |======JUGAR LA PARTIDA=======|\n" );
        printf( "                                                                |                             |\n" );
        printf( "                                                                |      1- Jugar partida       |\n" );
        printf( "                                                                |    2- Reiniciar partida     |\n" );
        printf( "                                                                |        3- Resumen           |\n" );
        printf( "                                                                |        4- Volver            |\n" );
        printf( "                                                                |                             |\n" );
        printf( "                                                                |=============================|\n" );

        if( scanf("%d", &op) != 1 ) {  
            ///Si scanf no lee un numero, limpia el bufer y reinicia op
            while( (c = getchar()) != '\n' && c != EOF ); 
            op = 0;  
            printf( "Entrada invalida. Introduce un numero entre 1 y 4.\n" );
        }
    }while( op < 1 || op > 4 );

    switch( op )
    {
    case 1:
        jugarPartida();                 ///En juego.c
        break;
    case 2:
        reiniciarPartida();             ///En juego.c
        break;
    case 3:
        mostrarResumen();               ///En juego.c
        break;
    case 4:
        MenuInicio();                   ///En interfaces.c
        break;
    }

    MenuJuego();                        ///En interfaces.c
}

void Menu_Conf_Introducir_Datos()
{

    int op;
    char c;

    system( "cls" );
    printf ( "\n\n" );
    do{
        printf( "                                                                |=======INTRODUCIR DATOS=======|\n" );
        printf( "                                                                |                              |\n" );
        printf( "                                                                |         1-Jugadores          |\n" );
        printf( "                                                                |      2-Tamano Tablero        |\n" );
        printf( "                                                                |          3-Barcos            |\n" );
        printf( "                                                                |      4-Numero de barcos      |\n" );
        printf( "                                                                |      5-Quien Comienza?       |\n" );
        printf( "                                                                |          6-Volver            |\n" );
        printf( "                                                                |                              |\n" );
        printf( "                                                                |==============================|\n" );

        if( scanf("%d", &op) != 1 ) {  
            ///Si scanf no lee un numero, limpia el bufer y reinicia op
            while( (c = getchar()) != '\n' && c != EOF ); 
            op = 0;  
            printf( "Entrada invalida. Introduce un numero entre 1 y 3.\n" );
        }
    }while( op < 1 || op > 6 );

    switch( op )
    {
    case 1:
        introducir_jugadores();                     ///En configuracion.c
        break;
    case 2:
        introducir_tamano_tablero();                ///En configuracion.c
        break;
    case 3:
        introducir_tipos_barcos();                  ///En configuracion.c
        break;
    case 4:
        introducirBarcos();                         ///En configuracion.c
        break;
    case 5:
        introducir_quien_comienza();                ///En configuracion.c
        break;
    case 6:
        MenuConfiguracion();                        ///En interfaces.c
        break;
    }

    Menu_Conf_Introducir_Datos();                   ///En interfaces.c
}