#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "interfaces.h"
#include "load.h"
#include "configuracion.h"


///Funcion para introducir el nombre de los jugadores y el tipo de disparo de cada uno
void introducir_jugadores()
{
    int i;
    char nombre[20];
    char tipo_disparo[20];

    system( "cls" );

    for( i = 0; i < 2; i++ )
    {
        printf( "Introduce el nombre del jugador %d: ", i+1 );                      ///Solicita nombre del jugador
        scanf( "%s", nombre );
        nombre[strcspn(nombre, "\n")] = '\0';
        do{
            printf( "Introduce el tipo de disparo del jugador %d(A/M): ", i+1 );    ///Solicita tipo de disparo(A-M)
            scanf( "%s", tipo_disparo );
            tipo_disparo[strcspn(tipo_disparo, "\n")] = '\0';

            if( strcmp(tipo_disparo, "A") != 0 && strcmp(tipo_disparo, "M") != 0 && strcmp(tipo_disparo, "a") != 0 && strcmp(tipo_disparo, "m") != 0)
                printf( "Error. El tipo de disparo debe ser 'A' o 'M'.\n" );


        }while( strcmp(tipo_disparo, "A") != 0 && strcmp(tipo_disparo, "M") != 0 && strcmp(tipo_disparo, "a") != 0 && strcmp(tipo_disparo, "m") != 0 );     ///Se ejecuta mientras no sea A o M o a o m

        if( tipo_disparo[0] >= 'a' && tipo_disparo[0] <= 'z' )
        {
            tipo_disparo[0] = toupper(tipo_disparo[0]); 
        }

        ///Copia los datos introducidos en las estructuras Jugadores jugador
        jugador[i].Id_jugador = i + 1;
        strcpy( jugador[i].Nomb_jugador, nombre );
        jugador[i].Num_disparo = 0;
        strcpy( jugador[i].Tipo_disparo, tipo_disparo );
        jugador[i].Indicador = 0;

    }

    ///Imprime los datos introducidos
    printf( "\nEleccion:\n" );
    for( i = 0; i < 2; i++ )
    {
        printf( "Nombre Jugador %d: %s.\n", i+1, jugador[i].Nomb_jugador );
        printf( "Tipo de Disparo Jugador %d: %s.\n", i+1, jugador[i].Tipo_disparo );
        printf( "\n" );
    }

    printf( "\n" );

    system( "pause" );
}

///Funcion para introducir el tamaño del tablero de los 2 jugadores
void introducir_tamano_tablero()
{
    int tamano;
    char c;

    system( "cls" );

    do{
        printf( "Introduce el tamano del tablero(Solo 1 numero y entre 8 y 20): " );

        if( scanf("%d", &tamano) != 1 ) {  
            ///Si scanf no lee un numero, limpia el bufer y reinicia op
            while( (c = getchar()) != '\n' && c != EOF ); 
            tamano = 0;  
            printf( "Entrada invalida. Introduce un numero entre 8 y 20.\n" );
        }

    }while( tamano < 8 || tamano > 20 );                                            ///Solicita tamaño del tablero mientras no este entre 8 y 20

    partida.Tam_tablero = tamano;                                                   ///Introduce en la estructura Partidas partida el valor del tamaño del tablero en la variable Tam_tablero

    printf( "\nEleccion:\n" );
    printf( "Tamano de Tablero: %dx%d casillas.\n\n", partida.Tam_tablero, partida.Tam_tablero );

    system( "pause" );
}
///Funcion para introducir los tipos de barcos que va a haber en cada flota
void introducir_tipos_barcos()
{
    int i = 0, j;
    int numero_barcos;              ///Variable que controla el numero de tipos de barcos
    int cont = 0;                   ///Contador del bucle para introducir los tipos de barcos
    char barcos[6];                 ///Array donde estan los identificadores de los tipos de barcos
    char c;                         ///Caracter que se lee por pantalla del identificador del tipo de barco
    int repetido;                   ///Variable para controlar si en el array barcos hay un identificador de tipo de barco repetido

    system( "cls" );

    printf( "=================Tipos de barcos disponibles=================\n\n" );
    printf( "||Nombre del Barco-Identificador del Barco-Tamano del Barco||\n\n" );
    for( i = 0; i < 6; i++ )                                                                    ///Imprime los tipos de barcos disponibles
    {
        printf( "%s-%c-%d\n", barco[i].Nomb_barco, barco[i].Id_barco, barco[i].Tam_barco );
    }

    do{
        printf( "Introduce cuantos tipos de barcos va a haber en cada flota(1-6): " );              ///Solicita el numero de tipos de barcos de cada flota

        if( scanf("%d", &numero_barcos) != 1 ) {  
            ///Si scanf no lee un numero, limpia el bufer y reinicia op
            while( (c = getchar()) != '\n' && c != EOF ); 
            numero_barcos = 0;  
            printf( "Entrada invalida. Introduce un numero entre 1 y 6.\n" );
        }

        if( numero_barcos < 1 || numero_barcos > 6 )
            printf( "Error. Introduce un numero entre 1 y 6.\n" );

    }while( numero_barcos < 1 || numero_barcos > 6 );


    ///Si se quieren añadir todos los tipos de barcos
    if( numero_barcos == 6 )
    {
        barcos[0] = 'P';
        barcos[1] = 'A';
        barcos[2] = 'C';
        barcos[3] = 'D';
        barcos[4] = 'F';
        barcos[5] = 'S';

    }else{

        ///Si el numero de tipos de barcos no es el maximo de tipos de barcos disponibles

        ///Se introduce un primer barco para que se pueda comparar si ya se ha introducido un mismo barco
        do{
            printf( "Introduce el identificador de los barcos UNO A UNO(P/A/C/D/F/S): " );
            scanf( " %c", &c );

            if( c != 'P' && c != 'A' && c != 'C' && c != 'D' && c != 'F' && c != 'S' && c != 'p' && c != 'a' && c != 'c' && c != 'd' && c != 'f' && c != 's' )
                printf( "Error. Introduce (P/A/C/D/F/S)\n" );


        }while( c != 'P' && c != 'A' && c != 'C' && c != 'D' && c != 'F' && c != 'S' && c != 'p' && c != 'a' && c != 'c' && c != 'd' && c != 'f' && c != 's' );

        ///Pone en mayusculas el caracter
        if( c >= 'a' && c <= 'z' )
        {
            c = toupper(c);
        }

        barcos[cont++] = c;                     ///Se introduce el primer barco en el array barcos
        
        while( cont < numero_barcos )           ///Se ejecuta el bucle mientras no se haya completado el numero de tipos de barcos
        {
            do{
                printf( "Introduce el identificador de los barcos UNO A UNO(P/A/C/D/F/S): " );
                scanf( " %c", &c );
        
                if( c != 'P' && c != 'A' && c != 'C' && c != 'D' && c != 'F' && c != 'S' && c != 'p' && c != 'a' && c != 'c' && c != 'd' && c != 'f' && c != 's' )
                    printf( "Error. Introduce (P/A/C/D/F/S)\n" );
        
        
            }while( c != 'P' && c != 'A' && c != 'C' && c != 'D' && c != 'F' && c != 'S' && c != 'p' && c != 'a' && c != 'c' && c != 'd' && c != 'f' && c != 's' );
        
            ///Pone en mayusculas el caracter
            if( c >= 'a' && c <= 'z' )
            {
                c = toupper(c);
            }

            ///Verifica si el caracter ya ha sido añadido
            repetido = 0;
            for( int i = 0; i < cont; i++ )
            {
                if( barcos[i] == c ) {
                    repetido = 1;
                    break;
                }
            }
        
            if( repetido == 1 ) {
                printf( "El barco '%c' ya ha sido ingresado. Introduce otro.\n", c );
            }else{
                barcos[cont] = c;           ///Si no esta repetido el caracter se añade a barcos
                cont++;                     ///Cont aumenta solo si no esta el caracter repetido
            }
        }
    }

    ///Añadir los datos de numero de tipos de barcos a la variable num_tipos_barcos de y los tipos de barcos a la variable Tipos_barcos en Partidas partida
    partida.Num_tipos_barcos = numero_barcos;
    for( i = 0; i < numero_barcos; i++ )
    {
        partida.Tipos_barcos[i] = barcos[i];
    }



    printf( "\nEleccion:\n" );
    printf( "Cantidad de Tipos de Barcos: %d.\n", partida.Num_tipos_barcos );
    printf( "========Tipos de Barcos========\n" );
    for( i = 0; i < numero_barcos; i++ )
    {
        for( j = 0; j < 6; j++ )
        {
            if( partida.Tipos_barcos[i] == barco[j].Id_barco )
            {
                printf( "-%s\n", barco[j].Nomb_barco );
            }
        }
    }

    printf( "\n" );

    system( "pause" );

}

///Funcion que permite seleccionar el numero de barcos de cada tipo
void introducirBarcos()
{
    int i, j;
    int op;
    int resultado;
    int barcos_totales = 0;

    system( "cls" );

    int len = strlen(partida.Tipos_barcos );

    ///Controla que se haya introducido la configuracion anterior(Tipos de Barcos)
    if ( len == 0 )
    {
        printf( "No se ha introducido la configuracion de los Tipos de Barcos.\n" );

    }else{
        
        ///Controla que se haya introducido la configuracion anterior(Tamaño de tablero)
        if( partida.Tam_tablero == 0 )
        {

            printf( "\n=========BARCOS ELEGIDOS=========\n\n" );            ///Imprime los tipos de barcos con el numero de barcos de cada tipo
            for( i = 0; i < partida.Num_tipos_barcos; i++ )
            {
                for( j = 0; j < 6; j++ )
                {
                    if( partida.Tipos_barcos[i] == barco[j].Id_barco )
                    {
                        printf( "-%s\n", barco[j].Nomb_barco );
                    }
                }
            }

            printf( "\n" );

            printf( "No se ha introducido la configuracion del Tamano del Tablero.\n\n" );

        }else{

            do{
                printf( "\n=========BARCOS ELEGIDOS=========\n\n" );            ///Imprime los tipos de barcos con el numero de barcos de cada tipo
                for( i = 0; i < partida.Num_tipos_barcos; i++ )
                {
                    for( j = 0; j < 6; j++ )
                    {
                        if( partida.Tipos_barcos[i] == barco[j].Id_barco )
                        {
                            printf( "-%s\n", barco[j].Nomb_barco );
                        }
                    }
                }


                printf( "\nIntroduce el numero de barcos de cada tipo que desees\n" );      ///Selecciona todos los tipos de barcos y se introduce el numero de barcos
                for( i = 0; i < partida.Num_tipos_barcos; i++ )
                {
                    for( j = 0; j < 6; j++ )
                    {
                        if( partida.Tipos_barcos[i] == barco[j].Id_barco )
                        {
                            if( partida.Tipos_barcos[i] == 'P' )                            ///Si son portaaviones
                            {
                                printf( "Introduce la cantidad de %s: ", barco[j].Nomb_barco );
                                scanf( "%d", &op );
                                partida.Portaaviones = op;
                            }

                            if( partida.Tipos_barcos[i] == 'A' )                            ///Si son acorazados
                            {
                                printf( "Introduce la cantidad de %ss: ", barco[j].Nomb_barco );
                                scanf( "%d", &op );
                                partida.Acorazado = op;
                            }

                            if( partida.Tipos_barcos[i] == 'C' )                            ///Si son cruceros
                            {
                                printf( "Introduce la cantidad de %ss: ", barco[j].Nomb_barco );
                                scanf( "%d", &op );
                                partida.Crucero = op;
                            }

                            if( partida.Tipos_barcos[i] == 'D' )                            ///Si son destructores
                            {
                                printf( "Introduce la cantidad de %ses: ", barco[j].Nomb_barco );
                                scanf( "%d", &op );
                                partida.Destructor = op;
                            }

                            if( partida.Tipos_barcos[i] == 'F' )                            ///Si son fragatas
                            {
                                printf( "Introduce la cantidad de %ss: ", barco[j].Nomb_barco );
                                scanf( "%d", &op );
                                partida.Fragata = op;
                            }

                            if( partida.Tipos_barcos[i] == 'S' )                            ///Si son submarinos
                            {
                                printf( "Introduce la cantidad de %ss: ", barco[j].Nomb_barco );
                                scanf( "%d", &op );
                                partida.Submarino = op;
                            }
                        }
                    }
                }

                resultado = comprobarBarcos();                  ///Guarda en resultado el valor de si es posible el numero de barcos

                if( resultado == 1 )
                {
                    printf( "\n------>La configuracion introducida no es posible. Introduce otra.\n" );
                }

            }while( resultado != 0 );               ///Pide la configuracion de barcos mientras resultado no devuelva 1


            ///Actualiza el numero total de barcos en cada flota
            barcos_totales += partida.Portaaviones;
            barcos_totales += partida.Acorazado;
            barcos_totales += partida.Crucero;
            barcos_totales += partida.Destructor;
            barcos_totales += partida.Fragata;
            barcos_totales += partida.Submarino;

            partida.Num_barcos = barcos_totales;

            printf( "La cantidad total de barcos es: %d.\n", barcos_totales );


            printf( "\nCantidad introducida:\n" );
            if( partida.Portaaviones != 0 ){
                printf( "Portaaviones: %d\n", partida.Portaaviones );
            }

            if( partida.Acorazado != 0 ){
                printf( "Acorazados: %d\n", partida.Acorazado );
            }

            if( partida.Crucero != 0 ){
                printf( "Cruceros: %d\n", partida.Crucero );
            }

            if( partida.Destructor != 0 ){
                printf( "Destructores: %d\n", partida.Destructor );
            }

            if( partida.Fragata != 0 ){
                printf( "Fragatas: %d\n", partida.Fragata );
            }
            if ( partida.Submarino != 0 ) {
                printf( "Submarinos: %d\n", partida.Submarino );
            }
            printf( "\n" );

            printf( "\nConfiguracion de barcos registrada con exito.\n\n" );
        }
    }

    system( "pause" );

}

///Funcion que comprueba si es posible crear un tablero con la configuracion dada 
int comprobarBarcos()
{
    ///Variables que controlan lo que vale cada barco si se colocan en el centro, lado y esquina del tablero
    int valor_portaavion_Centro = 24, valor_acorazado_Centro = 21, valor_crucero_Centro = 18, valor_destructor_Centro = 15, valor_fragata_Centro = 12, valor_submarino_Centro = 9;
    int valor_portaavion_Lado = 16, valor_acorazado_Lado = 14, valor_crucero_Lado = 12, valor_destructor_Lado = 10, valor_fragata_Lado = 8, valor_submarino_Lado = 6;
    int valor_portaaviones_Esquina = 14, valor_acorazado_Esquina = 12, valor_crucero_Esquina = 10, valor_destructor_Esquina = 8, valor_fragata_Esquina = 6, valor_submarino_Esquina = 4;
    int suma_casillas = 0;              ///Variable que suma las casillas que ocupan todos los barcos
    int op;                             ///Producto del numero de barcos de cada tipo por el espacio que ocupa en el tablero
    int capacidad_tablero;              ///Capacidad total del tablero: nxn
    int resultado;                      ///variable que controla si es posible esta configuracion o no

    capacidad_tablero = partida.Tam_tablero * partida.Tam_tablero;

    if( partida.Portaaviones != 0 )
    {
        op = partida.Portaaviones * 18;
        suma_casillas += op;
    }

    if( partida.Acorazado != 0 )
    {
        op = partida.Acorazado * 16;
        suma_casillas += op;
    }

    if( partida.Crucero != 0 )
    {
        op = partida.Crucero * 13;
        suma_casillas += op;
    }

    if( partida.Destructor != 0 )
    {
        op = partida.Destructor * 11;
        suma_casillas += op;
    }

    if( partida.Fragata != 0 )
    {
        op = partida.Fragata * 9;
        suma_casillas += op;
    }

    if( partida.Submarino != 0 )
    {
        op = partida.Submarino * 6;
        suma_casillas += op;
    }

    if( suma_casillas < capacidad_tablero )
    {
        resultado = 0;                      ///Devuelve 0 si la configuracion registrada es correcta
    }else{
        resultado = 1;                      ///Devuelve 1 si la configuracion registrada es incorrecta
    }


    return resultado;
}

///Funcion para introducir quien comienza la partida
void introducir_quien_comienza()
{
    char key;
    int op;
    char c;

    do{
        printf( "Quieres elegir quien comienza la partida(S/N): " );
        scanf( " %c", &key );

        if( key != 'S' && key != 's' && key != 'N' && key != 'n' )
            printf( "Error. Introduce('S', 'N', 's', 'n').\n" );

    }while( key != 'S' && key != 's' && key != 'N' && key != 'n' );


    if( key == 'S' || key == 's' )
    {
        do{
            printf( "Quien comienza la partida, Jugador 1 o Jugador 2?(1/2): " );

            if( scanf("%d", &op) != 1 ) {  
                ///Si scanf no lee un numero, limpia el bufer y reinicia op
                while( (c = getchar()) != '\n' && c != EOF ); 
                op = 0;  
                printf( "Entrada invalida. Introduce un numero entre 1 y 2.\n" );
            }

            if( op != 1 && op != 2 )
                printf( "Error. Introduce un numero entre 1 y 2.\n" );

        }while( op != 1 && op != 2 );
    }else{
        op = generarJugadorComienzo();

        if( op == 0 )           ///La funcion generarJugadorComienzo devuelve 0 o 1, y los intercambio por 1 y 2
        {
            op = 1;
        }else{
            op = 2;
        }
    }


    ///Almacena el jugador que comienza la partida en la estructura Partidas partidas;
    partida.Jugador_inicial_continuador = op;

    printf( "\nEleccion:\n" );
    printf( "Comienza la partida: Jugador %d.\n\n", partida.Jugador_inicial_continuador );


    system( "pause" );

}

///Funcion que genera un numero aleatorio entre 0 y 1 para el jugador que comienza la partida
int generarJugadorComienzo()
{
    srand(time(NULL));

    return rand() % 2;              ///Genera un número entre 0 y 1
}

///Funcion que muestra toda la informacion que hay en las estructuras de partidas y jugadores(la info que se puede configurar)
void mostrarConfiguracion()
{
    int i, j;

    printf( "\n========MOSTRAR CONFIGURACION========\n\n" );

    printf( "=================Tipos de barcos disponibles=================\n\n" );              ///Muestra los tipos de barcos disponibles
    printf( "||Nombre del Barco-Identificador del Barco-Tamano del Barco||\n\n" );
    for( i = 0; i < 6; i++ )                                                                    ///Imprime los tipos de barcos disponibles
    {
        printf( "%s-%c-%d\n", barco[i].Nomb_barco, barco[i].Id_barco, barco[i].Tam_barco );
    }

    printf( "\n--->Jugadores:\n" );                                                               ///Muestra la configuracion de los jugadores
    for( i = 0; i < 2; i++ )
    {
        printf( "Nombre Jugador %d: %s.\n", i+1, jugador[i].Nomb_jugador );
        printf( "Tipo de Disparo Jugador %d: %s.\n", i+1, jugador[i].Tipo_disparo );
        printf( "\n" );
    }
    printf( "\n" );

    printf( "--->Tamano del Tablero:\n" );                                                      ///Muestra la configuracion del tablero
    printf( "Tamano de Tablero: %dx%d casillas.\n\n", partida.Tam_tablero, partida.Tam_tablero );

    if( partida.Num_barcos == 0 && partida.Num_tipos_barcos == 0 )                      ///Si no existe configuracion
    {
        printf( "--->Tipos de Barcos:\n" );                                                         ///Muestra la configuracion de los tipos de barcos
        printf( "Cantidad de Tipos de Barcos: %d.\n", partida.Num_tipos_barcos );
        printf( "Cantidad de Barcos Totales: %d.\n", partida.Num_barcos );
        printf( "=====Tipos de Barcos y Cantidades=====\n" );
        printf( "-No hay barcos asignados\n" );
    }else{                                                                              ///Si existe configuracion

        printf( "--->Tipos de Barcos:\n" );                                                         ///Muestra la configuracion de los tipos de barcos
        printf( "Cantidad de Tipos de Barcos: %d.\n", partida.Num_tipos_barcos );
        printf( "Cantidad de Barcos Totales: %d.\n", partida.Num_barcos );
        printf( "=====Tipos de Barcos y Cantidades=====\n" );
        for( i = 0; i < partida.Num_tipos_barcos; i++ )
        {
            for( j = 0; j < 6; j++ )
            {
                if( partida.Tipos_barcos[i] == barco[j].Id_barco )
                {
                    if( barco[j].Id_barco == 'P' )
                    {
                        printf( "-%s-%d\n", barco[j].Nomb_barco, partida.Portaaviones );
                    }

                    if( barco[j].Id_barco == 'A' )
                    {
                        printf( "-%s-%d\n", barco[j].Nomb_barco, partida.Acorazado );
                    }

                    if( barco[j].Id_barco == 'C' )
                    {
                        printf( "-%s-%d\n", barco[j].Nomb_barco, partida.Crucero );
                    }

                    if( barco[j].Id_barco == 'D' )
                    {
                        printf( "-%s-%d\n", barco[j].Nomb_barco, partida.Destructor );
                    }

                    if( barco[j].Id_barco == 'F' )
                    {
                        printf( "-%s-%d\n", barco[j].Nomb_barco, partida.Fragata );
                    }

                    if( barco[j].Id_barco == 'S' )
                    {
                        printf( "-%s-%d\n", barco[j].Nomb_barco, partida.Submarino );
                    }


                    //printf( "-%s\n-%d", barco[j].Nomb_barco, partida );
                }
            }
        }
    }
    printf( "\n" );



    printf( "--->Quien Comienza?\n" );                                                         ///Muestra quien comienza la partida o quien la continua
    printf( "Comienza la partida: Jugador %d.\n\n", partida.Jugador_inicial_continuador );

    system( "pause" );
}


///Funcion que borra la configuracion existente
void borrarConfiguracion()
{
    char key;
    int i;
    int len;
    int jugador_borrado = 0, tablero_borrado = 0, barcos_borrado = 0, jugador_inicial_borrado = 0;


    printf( "\n========BORRAR CONFIGURACION========\n\n" );

    if( jugador[0].Id_jugador == 0 && jugador[1].Id_jugador == 0 )
    {
        printf( "No se ha introducido la configuracion de los Jugadores.\n" );
        jugador_borrado = 1;
    }

    if( partida.Tam_tablero == 0 )
    {
        printf( "No se ha introducido la configuracion del Tablero.\n" );
        tablero_borrado = 1;
    }

    len = strlen( partida.Tipos_barcos );
    if( len == 0 )
    {
        printf( "No se ha introducido la configuracion de Tipos de Barcos ni el Numero de Barcos de cada Tipo.\n" );
        barcos_borrado = 1;
    }

    if( partida.Jugador_inicial_continuador == 0 )
    {
        printf( "No se ha introducido la configuracion de Jugador que Comienza la Partida.\n" );
        jugador_inicial_borrado = 1;
    }

    if( jugador_borrado == 0 || tablero_borrado == 0 || barcos_borrado == 0 || jugador_inicial_borrado == 0 )
    {
        mostrarConfiguracion();
    }


    if( jugador_borrado == 0 )          ///Si existe configuracion de jugadores entra en la selectiva
    {
        printf( "A continuacion, selecciona la configuracion que precises borrar:\n\n" );
        do{                                                                                                 ///Borrar configuracion de los jugadores(nombre y tipo disparo)
            printf( "-Quieres borrar la configuracion de los jugadores(Nombres y Tipo de Disparo)(S/N): " );
            scanf( " %c", &key );
        }while( key != 'S' && key != 's' && key != 'N' && key != 'n' );

        if( key == 'S' || key == 's' )
        {
            for( i = 0; i < 2; i++ )
            {
                jugador[i].Id_jugador = 0;
                memset( jugador[i].Nomb_jugador, 0, sizeof(jugador[i].Nomb_jugador) );
                jugador[i].Num_disparo;
                memset( jugador[i].Tipo_disparo, 0, sizeof(jugador[i].Tipo_disparo) );
                jugador[i].Indicador = 0;
            }

            printf( "\n\nConfiguracion de los jugadores BORRADA.\n\n" );
        }
    }


    if( tablero_borrado == 0 )          ///Si existe configuracion del tablero entra en la selectiva
    {
        do{                                                                                            ///Borra la configuracion del tablero(tamaño tablero)
            printf( "-Quieres borrar la configuracion del tablero(Tamano del Tablero)(S/N): " );
            scanf( " %c", &key );
        }while( key != 'S' && key != 's' && key != 'N' && key != 'n' );

        if( key == 'S' || key == 's' )
        {
            partida.Tam_tablero = 0;

            printf( "\n\nConfiguracion del tablero BORRADA.\n\n" );
        }
    }


    if( barcos_borrado == 0 )                       ///Si existe configuracion de los tipos de barcos o las cantidades de barcos entra en la selectiva
    {
        do{                                                                                            ///Borra la configuracion de los barcos(Numero de tipos de barcos y tipos de barcos)
            printf( "-Quieres borrar la configuracion de los barcos(Cantidad de tipos de barcos, tipos de barcos) y numero de barcos de cada tipo(S/N): " );
            scanf( " %c", &key );
        }while( key != 'S' && key != 's' && key != 'N' && key != 'n' );

        if( key == 'S' || key == 's' )
        {
            partida.Num_tipos_barcos = 0;
            partida.Num_barcos = 0;
            partida.Portaaviones = 0;
            partida.Acorazado = 0;
            partida.Crucero = 0;
            partida.Destructor = 0;
            partida.Fragata = 0;
            partida.Submarino = 0;
            memset( partida.Tipos_barcos, 0, sizeof(partida.Tipos_barcos) );

            printf( "\n\nConfiguracion de los barcos BORRADA.\n\n" );
        }
    }

    if( jugador_inicial_borrado == 0 )
    {
        do{                                                                                            ///Borra la configuracion del tablero(jugador que comienza o continua)
            printf( "-Quieres borrar la configuracion del jugador que comienza la partida(S/N): " );
            scanf( " %c", &key );
        }while( key != 'S' && key != 's' && key != 'N' && key != 'n' );

        if( key == 'S' || key == 's' )
        {
            partida.Jugador_inicial_continuador = 0;

            printf( "\n\nConfiguracion del jugador que comienza la partida BORRADA.\n\n" );
        }
    }

    printf( "\n" );

    system( "pause" );
}