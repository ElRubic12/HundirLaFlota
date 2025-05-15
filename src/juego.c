#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "load.h"
#include "juego.h"

Disparos *disparo;
BarcosPartida *barcopartida;

int visitado[50][50] = {0};         ///variable para almacenar las posiciones de los barcos de los 2 jugadores en la estructura BarcopsPartida

int generarNumaleatorio( int op )
{
    int num_aleatorio;

    if( op == 1 )
    {
        num_aleatorio = rand() % partida.Tam_tablero;  // Genera un número entre 0 y el tamaño del tablero-1
    }else{
        num_aleatorio = rand() % 2;  // Genera un número entre 0 y el tamaño del tablero-1
    }

    return num_aleatorio;
}

///Funcion que llama a generacion de tableros y al bucle del juego
void jugarPartida()
{
    int op, i, j, k;

    srand(time(NULL));

    system( "cls" );

    if( jugador[0].Id_jugador == 0 && partida.Tam_tablero == 0 && partida.Num_tipos_barcos == 0 )  ///Si no hay configuracion
    {
        printf( "\n\n\n=================Antes de jugar introduce la configuracion de la partida=================\n\n\n\n" );

        system( "pause" );
    }else{
        disparo = (Disparos *)malloc(200 * sizeof(Disparos));                   ///Inicializa la estructura disparo
        barcopartida = (BarcosPartida *)malloc(2 * sizeof(BarcosPartida));      ///Inicializa la estructura barcopartida


        if( jugador[0].Indicador == 1 || jugador[1].Indicador == 1 )
        {

            AlmacenarPosicionesBarcos();
            inicializarTiposBarcos();

            jugador[0].Indicador = 0;
            jugador[1].Indicador = 0;
            jugador[0].Num_disparo = 0;
            jugador[1].Num_disparo = 0;

            op = generarNumaleatorio( 2 );

            for( i = 0; i < partida.Tam_tablero; i++ )
            {
                for( j = 0; j < partida.Tam_tablero; j++ )
                {
                    tablero[1].Matriz_tablero[i][j] = '-';
                }
            }

            for( i = 0; i < partida.Tam_tablero; i++ )
            {
                for( j = 0; j < partida.Tam_tablero; j++ )
                {
                    tablero[3].Matriz_tablero[i][j] = '-';
                }
            }

            printf( "\n\n\nSe ha recuperado la configuracion de la partida guardada.\n\n\n\n\n\n" );

            system( "pause" );

        }else if( jugador[0].Indicador == 0 && jugador[1].Indicador == 0 )
        {
            printf( "\n\n=============Seleccion de Flota=============\n\n\n" );
            generacionFlota( 0, 1 );

            system( "cls" );

            printf( "\n\n=============Seleccion de Flota=============\n\n\n" );
            generacionFlota( 2, 2 );

            system( "cls" );

            printf( "\n\n\nSe han generado los tableros de los jugadores correctamente.\n\n\n" );

            system( "pause" );
        }

        loop();

    }
}

///Funcion que controla el bucle del juego
void loop()
{
    int ganador = 0;
    int contador_disparos = 0;
    int jug;
    int nuevo_tiro;

    do{
        if( partida.Jugador_inicial_continuador == 1 && ganador == 0 )                                ///Turno del jugador 0-Jugador 1
        {
            system( "cls" );

            do{

                printf( "                                           |====================================================================|\n" );
                printf( "                                           |                                                                    |\n" );
                printf( "                                           |                              JUGADOR 1                             |\n" );
                printf( "                                           |--------------------------------------------------------------------|\n" );
                printf( "                                           |                               TURNO %d                              |\n", contador_disparos+1 );
                printf( "                                           |                                                                    |\n" );
                printf( "                                           |====================================================================|\n\n\n\n\n\n\n\n" );


                jug = 2;                                        ///Posicion de la matriz donde debe comprobar el disparo

                mostrarTablero( 0 );                            ///Muestra los 2 tableros del jugador 1
                mostrarTablero( 1 );

                jugar_turno( 0, contador_disparos );            ///Permite al jugador seleccionar la casilla para disparar
                nuevo_tiro =  comprobarDisparo( jug, contador_disparos++ );

                ganador = comprobarGanador( 1 );                ///Comprueba si ha ganado el jugador 1

                if( ganador == 1 )
                {
                    jugador[0].Indicador = 1;                   ///Cambia el valor de la variable de indicador de jugador a 1
                }

            }while( nuevo_tiro == 1 && ganador == 0);


            system( "pause" );
        }

        if( partida.Jugador_inicial_continuador == 2 && ganador == 0 )          ///Turno del jugador 2
        {

            do{

                printf( "                     \n\n\n                                           |====================================================================|\n" );
                printf( "                                           |                                                                    |\n" );
                printf( "                                           |                              JUGADOR 2                             |\n" );
                printf( "                                           |--------------------------------------------------------------------|\n" );
                printf( "                                           |                               TURNO %d                              |\n", contador_disparos+1 );
                printf( "                                           |                                                                    |\n" );
                printf( "                                           |====================================================================|\n\n\n\n\n\n\n\n" );


                jug = 0;

                mostrarTablero( 2 );                        ///Muestra los 2 tableros del jugador 2
                mostrarTablero( 3 );

                jugar_turno( 1, contador_disparos );        ///Permite al jugador seleccionar la casilla para disparar
                nuevo_tiro = comprobarDisparo( jug, contador_disparos++ );          ///Comprueba si el tiro es correcto, actualiza la casilla y si ha hundido el barco cambia el valor de las casillas por 'H'

                ganador = comprobarGanador( 3 );            ///Comprueba si el jugador 2 ha ganado

                if( ganador == 1 )
                {
                    jugador[1].Indicador = 1;
                }

            }while(nuevo_tiro == 1 && ganador == 0 );

            system( "pause" );
        }

        if( partida.Jugador_inicial_continuador == 1 )              ///Cambia el turno del jugador cambiando el valor de la variable de la estructura partida
        {
            partida.Jugador_inicial_continuador = 2;
        }else{
            partida.Jugador_inicial_continuador = 1;
        }

    }while( ganador == 0 );                                 ///El bucle se va a repetir mientras no haya un ganador



    ///Imprime el ganador de la partida
    if( jugador[0].Indicador == 1 )
    {
        system( "cls" );

        printf( "                     \n\n\n                                           |====================================================================|\n" );
        printf( "                                           |                                                                    |\n" );
        printf( "                                           |                           GANADOR: %s                           |\n", jugador[0].Nomb_jugador );
        printf( "                                           |                                                                    |\n" );
        printf( "                                           |====================================================================|\n\n\n\n" );

        mostrarTablero( 0 );
        mostrarTablero( 1 );
    }

    if( jugador[1].Indicador == 1 )
    {
        system( "cls" );

        printf( "                     \n\n\n                                           |====================================================================|\n" );
        printf( "                                           |                                                                    |\n" );
        printf( "                                           |                           GANADOR: %s                           |\n", jugador[1].Nomb_jugador );
        printf( "                                           |                                                                    |\n" );
        printf( "                                           |====================================================================|\n\n\n\n" );

        mostrarTablero( 2 );
        mostrarTablero( 3 );
    }


    system( "pause" );
}

///Función para jugar un turno
void jugar_turno( int turno, int cont_disparos ) {
    int x, y;
    char c;
    int casilla_ocupada = 0;
    int jug;

    if( turno == 0 )            ///jug apunta al tablero oponente
    {
        jug = 1;
    }else{
        jug = 3;
    }

    ///Imprime los datos del jugador que dispara
    printf( "%d-%s-%d-%s-%d\n", jugador[turno].Id_jugador, jugador[turno].Nomb_jugador, jugador[turno].Num_disparo, jugador[turno].Tipo_disparo, jugador[turno].Indicador );

    ///Si el tiro del jugador es Manual
    if( strcmp(jugador[turno].Tipo_disparo, "M") == 0 )
    {
        do{
            casilla_ocupada = 0;
            printf( "Introduce las coordenadas del disparo(x): " );
            if( scanf("%d", &x) != 1 ) {  
                ///Si scanf no lee un numero, limpia el bufer y reinicia x
                while( (c = getchar()) != '\n' && c != EOF ); 
                x = 0;  
                printf( "Entrada invalida.\n" );
            }

            printf( "Introduce las coordenadas del disparo(y): " );
            if( scanf("%d", &y) != 1 ) {  
                ///Si scanf no lee un numero, limpia el bufer y reinicia y
                while( (c = getchar()) != '\n' && c != EOF ); 
                y = 0;  
                printf( "Entrada invalida.\n" );
            }

            if( x >= partida.Tam_tablero || y >= partida.Tam_tablero )
            {
                printf( "Introduce las coordenadas dentro del tablero.\n" );
            }

            ///Comprueba que no se haya disparado anteriormente a la casilla seleccionada
            if( tablero[jug].Matriz_tablero[x][y] == '*' || tablero[jug].Matriz_tablero[x][y] == 'T' || tablero[jug].Matriz_tablero[x][y] == 'H' )
            {
                printf( "Casilla ya ocupada.\n" );
                casilla_ocupada = 1;
            }

        }while( x >= partida.Tam_tablero || y >= partida.Tam_tablero || casilla_ocupada == 1);  ///Se repite el disparo mientras las coordenadas no esten dentro del tablero y se haya disparado en una casilla ocupada

    ///Si el tiro del jugador es Automatico
    }else{

        do{
            casilla_ocupada = 0;

            x = generarNumaleatorio( 1 );
            y = generarNumaleatorio( 1 );

            ///Comprueba que no se haya disparado anteriormente a la casilla seleccionada
            if( tablero[jug].Matriz_tablero[x][y] == '*' || tablero[jug].Matriz_tablero[x][y] == 'T' || tablero[jug].Matriz_tablero[x][y] == 'H' )
            {
                casilla_ocupada = 1;
            }

        }while( x >= partida.Tam_tablero || y >= partida.Tam_tablero || casilla_ocupada == 1);  ///Se repite el disparo mientras las coordenadas no esten dentro del tablero y se haya disparado en una casilla ocupada
    }

    disparo[cont_disparos].x = x;               ///Almacena en la estructura Disparos las coordenadas del disparo
    disparo[cont_disparos].y = y;

    jugador[turno].Num_disparo++;               ///Aumenta el numero de disparos del jugador

}

///Comprueba el valor que tiene la casilla segun las coordenadas disparadas
int comprobarDisparo( int jugador, int cont_disparos )
{
    int i, j;
    int x, y;
    char casilla;
    int jug;
    int numero_casilla;

    if( jugador == 2 )      //Apunta al tablero Flota, donde se comprueba si el disparo es correcto
    {
        jug = 1;            ///Apunta al tablero Oponente, donde se actualizan los tableros
    }else{
        jug = 3;
    }

    x = disparo[cont_disparos].x;
    y = disparo[cont_disparos].y;

    casilla = tablero[jugador].Matriz_tablero[x][y];

    actualizarTableroOponente( jug, casilla, cont_disparos, jugador );       ///Llamada a funcion para actualizar el tablero flota. jug es el tablero oponente. jugador es el tablero flota

    if( casilla == 'X' )
    {
        printf( "Casilla: BARCO\n" );
    }else{
        printf( "Casilla: AGUA\n" );
    }

    if( casilla == '-' )
    {
        numero_casilla = 0;     ///No ha dado
    }

    if( casilla == 'X' )
    {
        numero_casilla = 1;     ///Si ha dado
    }


    return numero_casilla;

}

///Funcion que actualiza en el tablero flota segun el disparo realizado 
void actualizarTableroOponente( int oponente, char casilla, int cont_disparos, int flota )
{
    int x, y;
    char nueva_casilla;
    int hundido;

    x = disparo[cont_disparos].x;
    y = disparo[cont_disparos].y;


    ///Si el valor de la casilla es '-' ha tocado en agua
    if( casilla == '-' )
    {
        nueva_casilla = '*';
        tablero[oponente].Matriz_tablero[x][y] = nueva_casilla;
    }

    ///Si el valor de la casilla es 'X' entonces hay un barco
    if( casilla == 'X' )
    {
        ///Se actualiza la casilla pulsada y se llama a la funcion actualizartablerosihundido para comprobar si se han pulsado todas las posiciones del barco
        nueva_casilla = 'T';
        tablero[oponente].Matriz_tablero[x][y] = nueva_casilla;
        actualizarTableroSiHundido( oponente );
    }
}

///Funcion que actualiza el barco de tocado a hundido si se han pulsado todas las casillas del barco 
void actualizarTableroSiHundido( int oponente ){

    int i, j;
    int jugador, barco;
    int x, y;
    int x1, x2, y1, y2;
    int dx, dy;
    int tamano, tocado;


    ///La variable jugador controla los barcos del jugador que tiene el turno
    if( oponente == 1 )
    {
        jugador = 1;
    }else{
        jugador = 0;
    }


    ///Recorre todos los barcos del enemigo del jugador que tiene el turno
    for( i = 0; i < partida.Num_barcos; i++ )
    {
        ///Encuentra el indice del barco que aun no se ha hundido
        if( barcopartida[jugador].Hundido[i] == 'T' )
        {
            barco = i;
        }

        x1 = barcopartida[jugador].Posicion_inicial_X[barco];
        y1 = barcopartida[jugador].Posicion_inicial_Y[barco];
        x2 = barcopartida[jugador].Posicion_final_x[barco];
        y2 = barcopartida[jugador].Posicion_final_Y[barco];

        dx = (x2 - x1) == 0 ? 0 : (x2 - x1) / abs(x2 - x1);         ///Dirección en x
        dy = (y2 - y1) == 0 ? 0 : (y2 - y1) / abs(y2 - y1);         ///Dirección en y

        tamano = barcopartida[jugador].Tamano_barco[barco];
        x = x1, y = y1;
        tocado = 1;

        ///Recorre el barco para saber si faltan casilla 'T'
        for( j = 0; j < tamano; j++ ){

            if( tablero[oponente].Matriz_tablero[x][y] != 'T' ){

                tocado = 0;
                break;
            }

            x += dx;
            y += dy;
        }

        ///Si todas las casillas del barco son 'T'
        if( tocado ){

            ///Volvemos a recorrer para actualizar las 'T' a 'H'
            x = x1;
            y = y1;
            for( j = 0; j < tamano; j++ ){

                tablero[oponente].Matriz_tablero[x][y] = 'H';
                x += dx;
                y += dy;
            }
            barcopartida[jugador].Hundido[barco] = 'H';          ///Marcamos como hundido
        }
    }
}


///Funcion que comprueba si el jugador que tiene el turno ha ganado la partida 
int comprobarGanador( int turno )
{
    int i, j;
    int contador_hundidos = 0;
    int resultado = 0;
    int contador_casillas = 0;

    ///Recorre el tablero oponente del jugador que tiene el turno y cuenta las casillas que tienen 'H'
    for( i = 0; i < partida.Tam_tablero; i++ )
    {
        for( j = 0; j < partida.Tam_tablero; j++ )
        {
            if( tablero[turno].Matriz_tablero[i][j] == 'H' )
            {
                contador_hundidos++;
            }
        }
    }

    ///Calcula cuantas 'H' deberia haber en el tablero oponente si se hundieran todos los barcos
    contador_casillas += partida.Portaaviones * 6;
    contador_casillas += partida.Acorazado * 5;
    contador_casillas += partida.Crucero * 4;
    contador_casillas += partida.Destructor * 3;
    contador_casillas += partida.Fragata * 2;
    contador_casillas += partida.Submarino * 1;

    ///Si el numero total de 'H' si se hundieran todos los barcos es igual al numero de 'H' que hay en el tablero oponente del jugador que tiene el turno, resultado = 1 y el jugador ha ganado
    if( contador_hundidos == contador_casillas )
    {
        resultado = 1;
    }

    return resultado;       ///Devuelve 1 si ha ganado
}

///Funcion para generar la flota de cada jugador solicitando si manual o aleatorio
void generacionFlota( int jugador, int indice )
{
    char key;

    printf( "\nGeneracion de Flota Jugador %d\n", indice );
    do{
        printf( "Quieres generar el tablero automaticamente?(S/N): " );
        scanf( "%s", &key );
    }while( key != 'S' && key != 's' && key != 'N' && key != 'n' );

    if( key == 'S' || key == 's' )
    {
        generarTableroAleatorio( jugador );
    }else{
        generarTableroManual( jugador );

        int jug;

        if( jugador == 0 )
        {
            jug = 0;
        }
        if( jugador == 2 )
        {
            jug = 1;
        }
    }
}

//Funcion para generar el tablero de manera manual
void generarTableroManual( int jugador )
{
    int i, j;
    int x, y;
    int cont;
    int port, acor, cruc, dest, frag, subm;
    int resultado;
    char c;
    char orientacion;
    char sentido;
    char sentido_diagonal = ' ';
    int contador_numero_barcos = 0;

    printf( "\n=========BARCOS ELEGIDOS=========\n\n" );            ///Imprime los barcos elegidos en configuracion
    for( i = 0; i < partida.Num_tipos_barcos; i++ )
    {
        for( j = 0; j < 6; j++ )
        {
            if( partida.Tipos_barcos[i] == barco[j].Id_barco )
            {
                if( partida.Tipos_barcos[i] == 'P' )
                {
                    printf( "%s-%d\n", barco[j].Nomb_barco, partida.Portaaviones );
                }

                if( partida.Tipos_barcos[i] == 'A' )
                {
                    printf( "%s-%d\n", barco[j].Nomb_barco, partida.Acorazado );
                }

                if( partida.Tipos_barcos[i] == 'C' )
                {
                    printf( "%s-%d\n", barco[j].Nomb_barco, partida.Crucero );
                }

                if( partida.Tipos_barcos[i] == 'D' )
                {
                    printf( "%s-%d\n", barco[j].Nomb_barco, partida.Destructor );
                }

                if( partida.Tipos_barcos[i] == 'F' )
                {
                    printf( "%s-%d\n", barco[j].Nomb_barco, partida.Fragata );
                }

                if( partida.Tipos_barcos[i] == 'S' )
                {
                    printf( "%s-%d\n", barco[j].Nomb_barco, partida.Submarino );
                }
            }
        }
    }

    port = partida.Portaaviones;
    acor = partida.Acorazado;
    cruc = partida.Crucero;
    dest = partida.Destructor;
    frag = partida.Fragata;
    subm = partida.Submarino;


    cont = 0;
    ///Para los barcos Portaaviones
    while( port > 0 )
    {
        printf( "\n========Eleccion de Posiciones========\n\n" );
        mostrarTablero( jugador );
        printf( "----->Eleccion posicion de Portaaviones(Tam 6). Quedan %d.\n", partida.Portaaviones - cont );
        ///Do-while que se ejecuta mientras la posicion elegida para el barco sea incorrecta
        do{
            ///Do-while para introducir la posicion (x-y) del tablero a colocar el barco
            do{
                printf( "Introduce la posicion base(x): " );
                if( scanf("%d", &x) != 1 ) {  
                    ///Si scanf no lee un numero, limpia el bufer y reinicia x
                    while( (c = getchar()) != '\n' && c != EOF ); 
                    x = 0;  
                }

                printf( "Introduce la posicion base(y): " );
                if( scanf("%d", &y) != 1 ) {  
                    ///Si scanf no lee un numero, limpia el bufer y reinicia y
                    while( (c = getchar()) != '\n' && c != EOF ); 
                    y = 0;  
                }
            }while( x > partida.Tam_tablero && y > partida.Tam_tablero );

            ///Introduce la orientacion y sentido a partir de la posicion base
            do{
                printf( "Intoduce la orientacion Horizontal, Vertical, Diagonal(H/V/D): " );
                scanf( " %c", &orientacion );
            }while( orientacion != 'H' && orientacion != 'h' && orientacion != 'V' && orientacion != 'v' && orientacion != 'D' && orientacion != 'd' );

            if( orientacion == 'H' || orientacion == 'h' )
            {
                do{
                printf( "Introduce si lo quieres para la Derecha o para la Izquierda(D/I): " );
                scanf( " %c", &sentido );
                }while( sentido != 'D' && sentido != 'd' && sentido != 'I' && sentido != 'i' );
            }

            if( orientacion == 'V' || orientacion == 'v' )
            {
                do{
                    printf( "Introduce si lo quieres para Arriba o para Debajo(A/D): " );
                    scanf( " %c", &sentido );
                }while( sentido != 'A' && sentido != 'a' && sentido != 'D' && sentido != 'd' );
            }

            if( orientacion == 'D' || orientacion == 'd' )
            {
                do{
                    printf( "Introduce si lo quieres para Arriba o para Debajo(A/D): " );
                    scanf( " %c", &sentido );
                }while( sentido != 'A' && sentido != 'a' && sentido != 'D' && sentido != 'd' );

                do{
                    printf( "Introduce si lo quieres para la Derecha o para la Izquierda(D/I): " );
                    scanf( " %c", &sentido_diagonal );
                }while( sentido_diagonal != 'D' && sentido_diagonal != 'd' && sentido_diagonal != 'I' && sentido_diagonal != 'i' );
            }


            ///Si la orientacion del barco introducido es horizontal o vertical sentido_diagonal = ' ', en caso de que la orientacion sea diagonal, sentido_diagonal='D' o 'I'
            if( orientacion == 'H' || orientacion == 'h' || orientacion == 'V' || orientacion == 'v' )
            {

                resultado = comprobarPosicion( x, y, orientacion, sentido, sentido_diagonal, jugador, barco[0].Tam_barco );

            }else{

                resultado = comprobarPosicion( x, y, orientacion, sentido, sentido_diagonal, jugador, barco[0].Tam_barco );

            }

            if( resultado == 1 )
            {
                printf( "La posicion es incorrecta.\n" );
                printf( "----->Eleccion posicion de Portaaviones(Tam 6). Quedan %d.\n", partida.Portaaviones - cont );
            }

        }while( resultado == 1 );

        anadirBarcoFlota( jugador, x, y, orientacion, sentido, sentido_diagonal, barco[0].Tam_barco, contador_numero_barcos++ );
        mostrarTablero( jugador );

        cont++;
        port--;
    }


    cont = 0;
    ///Para los barcos Acorazados
    while( acor > 0 )
    {
        printf( "\n========Eleccion de Posiciones========\n\n" );
        mostrarTablero( jugador );
        printf( "----->Eleccion posicion de Acorazados(Tam 5). Quedan %d.\n", partida.Acorazado - cont );
        ///Do-while que se ejecuta mientras la posicion elegida para el barco sea incorrecta
        do{
            ///Do-while para introducir la posicion (x-y) del tablero a colocar el barco
            do{
                printf( "Introduce la posicion base(x): " );
                if( scanf("%d", &x) != 1 ) {  
                    ///Si scanf no lee un numero, limpia el bufer y reinicia x
                    while( (c = getchar()) != '\n' && c != EOF ); 
                    x = 0;  
                }

                printf( "Introduce la posicion base(y): " );
                if( scanf("%d", &y) != 1 ) {  
                    ///Si scanf no lee un numero, limpia el bufer y reinicia y
                    while( (c = getchar()) != '\n' && c != EOF ); 
                    y = 0;  
                }
            }while( x > partida.Tam_tablero && y > partida.Tam_tablero );

            ///Introduce la orientacion y sentido a partir de la posicion base
            do{
                printf( "Intoduce la orientacion Horizontal, Vertical, Diagonal(H/V/D): " );
                scanf( " %c", &orientacion );
            }while( orientacion != 'H' && orientacion != 'h' && orientacion != 'V' && orientacion != 'v' && orientacion != 'D' && orientacion != 'd' );

            if( orientacion == 'H' || orientacion == 'h' )
            {
                do{
                printf( "Introduce si lo quieres para la Derecha o para la Izquierda(D/I): " );
                scanf( " %c", &sentido );
                }while( sentido != 'D' && sentido != 'd' && sentido != 'I' && sentido != 'i' );
            }

            if( orientacion == 'V' || orientacion == 'v' )
            {
                do{
                    printf( "Introduce si lo quieres para Arriba o para Debajo(A/D): " );
                    scanf( " %c", &sentido );
                }while( sentido != 'A' && sentido != 'a' && sentido != 'D' && sentido != 'd' );
            }

            if( orientacion == 'D' || orientacion == 'd' )
            {
                do{
                    printf( "Introduce si lo quieres para Arriba o para Debajo(A/D): " );
                    scanf( " %c", &sentido );
                }while( sentido != 'A' && sentido != 'a' && sentido != 'D' && sentido != 'd' );

                do{
                    printf( "Introduce si lo quieres para la Derecha o para la Izquierda(D/I): " );
                    scanf( " %c", &sentido_diagonal );
                }while( sentido_diagonal != 'D' && sentido_diagonal != 'd' && sentido_diagonal != 'I' && sentido_diagonal != 'i' );
            }


            if( orientacion == 'H' || orientacion == 'h' || orientacion == 'V' || orientacion == 'v' )
            {

                resultado = comprobarPosicion( x, y, orientacion, sentido, sentido_diagonal, jugador, barco[1].Tam_barco );

            }else{

                resultado = comprobarPosicion( x, y, orientacion, sentido, sentido_diagonal, jugador, barco[1].Tam_barco );

            }

            if( resultado == 1 )
            {
                printf( "La posicion es incorrecta.\n" );
                printf( "----->Eleccion posicion de Acorazados(Tam 5). Quedan %d.\n", partida.Acorazado - cont );
            }

        }while( resultado == 1 );

        ///Una vez se ha introducido las posiciones del barco y la orientacion y sentido, se ha comprobado que se puede situar en esas posiciones, se añade el barco a la flota
        anadirBarcoFlota( jugador, x, y, orientacion, sentido, sentido_diagonal, barco[1].Tam_barco, contador_numero_barcos++ );
        mostrarTablero( jugador );

        cont++;
        acor--;
    }



    cont = 0;
    ///Para los barcos Cruceros
    while( cruc > 0 )
    {
        printf( "\n========Eleccion de Posiciones========\n\n" );
        mostrarTablero( jugador );
        printf( "----->Eleccion posicion de Cruceros(Tam 4). Quedan %d.\n", partida.Crucero - cont );
        ///Do-while que se ejecuta mientras la posicion elegida para el barco sea incorrecta
        do{
            ///Do-while para introducir la posicion (x-y) del tablero a colocar el barco
            do{
                printf( "Introduce la posicion base(x): " );
                if( scanf("%d", &x) != 1 ) {  
                    ///Si scanf no lee un numero, limpia el bufer y reinicia x
                    while( (c = getchar()) != '\n' && c != EOF ); 
                    x = 0;  
                }

                printf( "Introduce la posicion base(y): " );
                if( scanf("%d", &y) != 1 ) {  
                    ///Si scanf no lee un numero, limpia el bufer y reinicia y
                    while( (c = getchar()) != '\n' && c != EOF ); 
                    y = 0;  
                }
            }while( x > partida.Tam_tablero && y > partida.Tam_tablero );

            ///Introduce la orientacion y sentido a partir de la posicion base
            do{
                printf( "Intoduce la orientacion Horizontal, Vertical, Diagonal(H/V/D): " );
                scanf( " %c", &orientacion );
            }while( orientacion != 'H' && orientacion != 'h' && orientacion != 'V' && orientacion != 'v' && orientacion != 'D' && orientacion != 'd' );

            if( orientacion == 'H' || orientacion == 'h' )
            {
                do{
                printf( "Introduce si lo quieres para la Derecha o para la Izquierda(D/I): " );
                scanf( " %c", &sentido );
                }while( sentido != 'D' && sentido != 'd' && sentido != 'I' && sentido != 'i' );
            }

            if( orientacion == 'V' || orientacion == 'v' )
            {
                do{
                    printf( "Introduce si lo quieres para Arriba o para Debajo(A/D): " );
                    scanf( " %c", &sentido );
                }while( sentido != 'A' && sentido != 'a' && sentido != 'D' && sentido != 'd' );
            }

            if( orientacion == 'D' || orientacion == 'd' )
            {
                do{
                    printf( "Introduce si lo quieres para Arriba o para Debajo(A/D): " );
                    scanf( " %c", &sentido );
                }while( sentido != 'A' && sentido != 'a' && sentido != 'D' && sentido != 'd' );

                do{
                    printf( "Introduce si lo quieres para la Derecha o para la Izquierda(D/I): " );
                    scanf( " %c", &sentido_diagonal );
                }while( sentido_diagonal != 'D' && sentido_diagonal != 'd' && sentido_diagonal != 'I' && sentido_diagonal != 'i' );
            }


            if( orientacion == 'H' || orientacion == 'h' || orientacion == 'V' || orientacion == 'v' )
            {

                resultado = comprobarPosicion( x, y, orientacion, sentido, sentido_diagonal, jugador, barco[2].Tam_barco );

            }else{

                resultado = comprobarPosicion( x, y, orientacion, sentido, sentido_diagonal, jugador, barco[2].Tam_barco );

            }

            if( resultado == 1 )
            {
                printf( "La posicion es incorrecta.\n" );
                printf( "----->Eleccion posicion de Cruceros(Tam 4). Quedan %d.\n", partida.Crucero - cont );
            }

        }while( resultado == 1 );

        anadirBarcoFlota( jugador, x, y, orientacion, sentido, sentido_diagonal, barco[2].Tam_barco, contador_numero_barcos++ );
        mostrarTablero( jugador );

        cont++;
        cruc--;
    }


    cont = 0;
    ///Para los barcos Destructores
    while( dest > 0 )
    {
        printf( "\n========Eleccion de Posiciones========\n\n" );
        mostrarTablero( jugador );
        printf( "----->Eleccion posicion de Destructores(Tam 3). Quedan %d.\n", partida.Destructor - cont );
        ///Do-while que se ejecuta mientras la posicion elegida para el barco sea incorrecta
        do{
            ///Do-while para introducir la posicion (x-y) del tablero a colocar el barco
            do{
                printf( "Introduce la posicion base(x): " );
                if( scanf("%d", &x) != 1 ) {  
                    ///Si scanf no lee un numero, limpia el bufer y reinicia x
                    while( (c = getchar()) != '\n' && c != EOF ); 
                    x = 0;  
                }

                printf( "Introduce la posicion base(y): " );
                if( scanf("%d", &y) != 1 ) {  
                    ///Si scanf no lee un numero, limpia el bufer y reinicia y
                    while( (c = getchar()) != '\n' && c != EOF ); 
                    y = 0;  
                }
            }while( x > partida.Tam_tablero && y > partida.Tam_tablero );

            ///Introduce la orientacion y sentido a partir de la posicion base
            do{
                printf( "Intoduce la orientacion Horizontal, Vertical, Diagonal(H/V/D): " );
                scanf( " %c", &orientacion );
            }while( orientacion != 'H' && orientacion != 'h' && orientacion != 'V' && orientacion != 'v' && orientacion != 'D' && orientacion != 'd' );

            if( orientacion == 'H' || orientacion == 'h' )
            {
                do{
                printf( "Introduce si lo quieres para la Derecha o para la Izquierda(D/I): " );
                scanf( " %c", &sentido );
                }while( sentido != 'D' && sentido != 'd' && sentido != 'I' && sentido != 'i' );
            }

            if( orientacion == 'V' || orientacion == 'v' )
            {
                do{
                    printf( "Introduce si lo quieres para Arriba o para Debajo(A/D): " );
                    scanf( " %c", &sentido );
                }while( sentido != 'A' && sentido != 'a' && sentido != 'D' && sentido != 'd' );
            }

            if( orientacion == 'D' || orientacion == 'd' )
            {
                do{
                    printf( "Introduce si lo quieres para Arriba o para Debajo(A/D): " );
                    scanf( " %c", &sentido );
                }while( sentido != 'A' && sentido != 'a' && sentido != 'D' && sentido != 'd' );

                do{
                    printf( "Introduce si lo quieres para la Derecha o para la Izquierda(D/I): " );
                    scanf( " %c", &sentido_diagonal );
                }while( sentido_diagonal != 'D' && sentido_diagonal != 'd' && sentido_diagonal != 'I' && sentido_diagonal != 'i' );
            }


            if( orientacion == 'H' || orientacion == 'h' || orientacion == 'V' || orientacion == 'v' )
            {

                resultado = comprobarPosicion( x, y, orientacion, sentido, sentido_diagonal, jugador, barco[3].Tam_barco );

            }else{

                resultado = comprobarPosicion( x, y, orientacion, sentido, sentido_diagonal, jugador, barco[3].Tam_barco );
            }

            if( resultado == 1 )
            {
                printf( "La posicion es incorrecta.\n" );
                printf( "----->Eleccion posicion de Destructores(Tam 3). Quedan %d.\n", partida.Destructor - cont );
            }

        }while( resultado == 1 );

        anadirBarcoFlota( jugador, x, y, orientacion, sentido, sentido_diagonal, barco[3].Tam_barco, contador_numero_barcos++ );
        mostrarTablero( jugador );

        cont++;
        dest--;
    }


    cont = 0;
    ///Para los barcos Fragatas
    while( frag > 0 )
    {
        printf( "\n========Eleccion de Posiciones========\n\n" );
        mostrarTablero( jugador );
        printf( "----->Eleccion posicion de Fragatas(Tam 2). Quedan %d.\n", partida.Fragata - cont );
        ///Do-while que se ejecuta mientras la posicion elegida para el barco sea incorrecta
        do{
            ///Do-while para introducir la posicion (x-y) del tablero a colocar el barco
            do{
                printf( "Introduce la posicion base(x): " );
                if( scanf("%d", &x) != 1 ) {  
                    ///Si scanf no lee un numero, limpia el bufer y reinicia x
                    while( (c = getchar()) != '\n' && c != EOF ); 
                    x = 0;  
                }

                printf( "Introduce la posicion base(y): " );
                if( scanf("%d", &y) != 1 ) {  
                    ///Si scanf no lee un numero, limpia el bufer y reinicia y
                    while( (c = getchar()) != '\n' && c != EOF ); 
                    y = 0;  
                }
            }while( x > partida.Tam_tablero && y > partida.Tam_tablero );

            ///Introduce la orientacion y sentido a partir de la posicion base
            do{
                printf( "Intoduce la orientacion Horizontal, Vertical, Diagonal(H/V/D): " );
                scanf( " %c", &orientacion );
            }while( orientacion != 'H' && orientacion != 'h' && orientacion != 'V' && orientacion != 'v' && orientacion != 'D' && orientacion != 'd' );

            if( orientacion == 'H' || orientacion == 'h' )
            {
                do{
                printf( "Introduce si lo quieres para la Derecha o para la Izquierda(D/I): " );
                scanf( " %c", &sentido );
                }while( sentido != 'D' && sentido != 'd' && sentido != 'I' && sentido != 'i' );
            }

            if( orientacion == 'V' || orientacion == 'v' )
            {
                do{
                    printf( "Introduce si lo quieres para Arriba o para Debajo(A/D): " );
                    scanf( " %c", &sentido );
                }while( sentido != 'A' && sentido != 'a' && sentido != 'D' && sentido != 'd' );
            }

            if( orientacion == 'D' || orientacion == 'd' )
            {
                do{
                    printf( "Introduce si lo quieres para Arriba o para Debajo(A/D): " );
                    scanf( " %c", &sentido );
                }while( sentido != 'A' && sentido != 'a' && sentido != 'D' && sentido != 'd' );

                do{
                    printf( "Introduce si lo quieres para la Derecha o para la Izquierda(D/I): " );
                    scanf( " %c", &sentido_diagonal );
                }while( sentido_diagonal != 'D' && sentido_diagonal != 'd' && sentido_diagonal != 'I' && sentido_diagonal != 'i' );
            }


            if( orientacion == 'H' || orientacion == 'h' || orientacion == 'V' || orientacion == 'v' )
            {

                resultado = comprobarPosicion( x, y, orientacion, sentido, sentido_diagonal, jugador, barco[4].Tam_barco );

            }else{

                resultado = comprobarPosicion( x, y, orientacion, sentido, sentido_diagonal, jugador, barco[4].Tam_barco );

            }

            if( resultado == 1 )
            {
                printf( "La posicion es incorrecta.\n" );
                printf( "----->Eleccion posicion de Fragatas(Tam 2). Quedan %d.\n", partida.Fragata - cont );
            }

        }while( resultado == 1 );

        anadirBarcoFlota( jugador, x, y, orientacion, sentido, sentido_diagonal, barco[4].Tam_barco, contador_numero_barcos++ );
        mostrarTablero( jugador );

        cont++;
        frag--;
    }



    cont = 0;
    ///Para los barcos Submarinos
    while( subm > 0 )
    {
        printf( "\n========Eleccion de Posiciones========\n\n" );
        mostrarTablero( jugador );
        printf( "----->Eleccion posicion de Submarinos(Tam 1). Quedan %d.\n", partida.Submarino - cont );
        ///Do-while que se ejecuta mientras la posicion elegida para el barco sea incorrecta
        do{
            ///Do-while para introducir la posicion (x-y) del tablero a colocar el barco
            do{
                printf( "Introduce la posicion base(x): " );
                if( scanf("%d", &x) != 1 ) {  
                    ///Si scanf no lee un numero, limpia el bufer y reinicia x
                    while( (c = getchar()) != '\n' && c != EOF ); 
                    x = 0;  
                }

                printf( "Introduce la posicion base(y): " );
                if( scanf("%d", &y) != 1 ) {  
                    ///Si scanf no lee un numero, limpia el bufer y reinicia y
                    while( (c = getchar()) != '\n' && c != EOF ); 
                    y = 0;  
                }
            }while( x > partida.Tam_tablero && y > partida.Tam_tablero );

            ///Introduce la orientacion y sentido a partir de la posicion base
            do{
                printf( "Intoduce la orientacion Horizontal, Vertical, Diagonal(H/V/D): " );
                scanf( " %c", &orientacion );
            }while( orientacion != 'H' && orientacion != 'h' && orientacion != 'V' && orientacion != 'v' && orientacion != 'D' && orientacion != 'd' );

            if( orientacion == 'H' || orientacion == 'h' )
            {
                do{
                printf( "Introduce si lo quieres para la Derecha o para la Izquierda(D/I): " );
                scanf( " %c", &sentido );
                }while( sentido != 'D' && sentido != 'd' && sentido != 'I' && sentido != 'i' );
            }

            if( orientacion == 'V' || orientacion == 'v' )
            {
                do{
                    printf( "Introduce si lo quieres para Arriba o para Debajo(A/D): " );
                    scanf( " %c", &sentido );
                }while( sentido != 'A' && sentido != 'a' && sentido != 'D' && sentido != 'd' );
            }

            if( orientacion == 'D' || orientacion == 'd' )
            {
                do{
                    printf( "Introduce si lo quieres para Arriba o para Debajo(A/D): " );
                    scanf( " %c", &sentido );
                }while( sentido != 'A' && sentido != 'a' && sentido != 'D' && sentido != 'd' );

                do{
                    printf( "Introduce si lo quieres para la Derecha o para la Izquierda(D/I): " );
                    scanf( " %c", &sentido_diagonal );
                }while( sentido_diagonal != 'D' && sentido_diagonal != 'd' && sentido_diagonal != 'I' && sentido_diagonal != 'i' );
            }


            if( orientacion == 'H' || orientacion == 'h' || orientacion == 'V' || orientacion == 'v' )
            {

                resultado = comprobarPosicion( x, y, orientacion, sentido, sentido_diagonal, jugador, barco[5].Tam_barco );

            }else{

                resultado = comprobarPosicion( x, y, orientacion, sentido, sentido_diagonal, jugador, barco[5].Tam_barco );

            }

            if( resultado == 1 )
            {
                printf( "La posicion es incorrecta.\n" );
                printf( "----->Eleccion posicion de Submarinos(Tam 1). Quedan %d.\n", partida.Submarino - cont );
            }

        }while( resultado == 1 );

        anadirBarcoFlota( jugador, x, y, orientacion, sentido, sentido_diagonal, barco[5].Tam_barco, contador_numero_barcos++ );
        mostrarTablero( jugador );

        cont++;
        subm--;
    }

    AlmacenarPosicionesBarcos();

    system( "pause" );
}

///Funcion para generar el tablero de los jugadores de manera aleatoria 
void generarTableroAleatorio( int jugador )
{
    int x, y;
    int port, acor, cruc, dest, frag, subm;
    int resultado;
    int contador_numero_barcos = 0;
    char orientacion[] = { 'H', 'V', 'D' };
    char sentido_derecha_izquierda[] = { 'D', 'I' };
    char sentido_arriba_abajo[] = { 'A', 'D' };
    char letraori, letrasen_horizontal, letrasen_vertical, letrasen_diagonal;

    port = partida.Portaaviones;
    acor = partida.Acorazado;
    cruc = partida.Crucero;
    dest = partida.Destructor;
    frag = partida.Fragata;
    subm = partida.Submarino;


    ///Para los barcos Portaaviones
    while( port > 0 )
    {
        ///Do-while que se ejecuta mientras la posicion elegida para el barco sea incorrecta
        do{

            x = rand() % partida.Tam_tablero;           ///Genera las coordendas x e y aleatorias
            y = rand() % partida.Tam_tablero;


            ///Vacia las variables para las siguientes entradas al bucle
            letraori = ' ';
            letrasen_horizontal = ' ';
            letrasen_vertical = ' ';
            letrasen_diagonal = ' ';

            letraori = orientacion[rand() % 3];

            ///Si la orientacion es horizontal genera aleatoriamente una letra de sentido 'D' o 'I'
            if( letraori == 'H' )
            {
                letrasen_horizontal = sentido_derecha_izquierda[rand() % 2];
                letrasen_diagonal = ' ';
            }

            ///Si la orientacion es vertical genera aleatoriamente una letra de sentido 'A' o 'D'
            if( letraori == 'V' )
            {
                letrasen_vertical = sentido_arriba_abajo[rand() % 2];
                letrasen_diagonal = ' ';
            }

            ///Si la orientacion es diagonal genera aleatoriamente 2 letras de sentido 'A' o 'D' y 'D' o 'I'
            if( letraori == 'D' )
            {
                letrasen_vertical = sentido_arriba_abajo[rand() % 2];
                letrasen_diagonal = sentido_derecha_izquierda[rand() % 2];
            }


            resultado = 0;
            if( letraori == 'H' )
            {
                resultado = comprobarPosicion( x, y, letraori, letrasen_horizontal, letrasen_diagonal, jugador, barco[0].Tam_barco );

            }
            if( letraori == 'V' ){

                resultado = comprobarPosicion( x, y, letraori, letrasen_vertical, letrasen_diagonal, jugador, barco[0].Tam_barco );

            }
            if( letraori == 'D' ){

                resultado = comprobarPosicion( x, y, letraori, letrasen_vertical, letrasen_diagonal, jugador, barco[0].Tam_barco );
            }

        }while( resultado == 1 );           ///Ejecuta el bucle mientras no se pueda colocar el barco en las posiciones generadas aleatoriamente


        ///Dependiendo de la orientacion llama a la funcion con los valores generados
        if( letraori == 'H' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_horizontal, letrasen_diagonal, barco[0].Tam_barco, contador_numero_barcos++ );
        }

        if( letraori == 'V' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_vertical, letrasen_diagonal, barco[0].Tam_barco, contador_numero_barcos++ );
        }

        if( letraori == 'D' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_vertical, letrasen_diagonal, barco[0].Tam_barco, contador_numero_barcos++ );
        }

        port--;
    }


    ///Para los barcos Acorazados
    while( acor > 0 )
    {
        ///Do-while que se ejecuta mientras la posicion elegida para el barco sea incorrecta
        do{

            x = rand() % partida.Tam_tablero;           ///Genera las coordendas x e y aleatorias
            y = rand() % partida.Tam_tablero;


            ///Vacia las variables para las siguientes entradas al bucle
            letraori = ' ';
            letrasen_horizontal = ' ';
            letrasen_vertical = ' ';
            letrasen_diagonal = ' ';

            letraori = orientacion[rand() % 3];

            ///Si la orientacion es horizontal genera aleatoriamente una letra de sentido 'D' o 'I'
            if( letraori == 'H' )
            {
                letrasen_horizontal = sentido_derecha_izquierda[rand() % 2];
                letrasen_diagonal = ' ';
            }

            ///Si la orientacion es vertical genera aleatoriamente una letra de sentido 'A' o 'D'
            if( letraori == 'V' )
            {
                letrasen_vertical = sentido_arriba_abajo[rand() % 2];
                letrasen_diagonal = ' ';
            }

            ///Si la orientacion es diagonal genera aleatoriamente 2 letras de sentido 'A' o 'D' y 'D' o 'I'
            if( letraori == 'D' )
            {
                letrasen_vertical = sentido_arriba_abajo[rand() % 2];
                letrasen_diagonal = sentido_derecha_izquierda[rand() % 2];
            }


            resultado = 0;
            if( letraori == 'H' )
            {
                resultado = comprobarPosicion( x, y, letraori, letrasen_horizontal, letrasen_diagonal, jugador, barco[1].Tam_barco );

            }
            if( letraori == 'V' ){

                resultado = comprobarPosicion( x, y, letraori, letrasen_vertical, letrasen_diagonal, jugador, barco[1].Tam_barco );

            }
            if( letraori == 'D' ){

                resultado = comprobarPosicion( x, y, letraori, letrasen_vertical, letrasen_diagonal, jugador, barco[1].Tam_barco );
            }

        }while( resultado == 1 );           ///Ejecuta el bucle mientras no se pueda colocar el barco en las posiciones generadas aleatoriamente


        ///Dependiendo de la orientacion llama a la funcion con los valores generados
        if( letraori == 'H' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_horizontal, letrasen_diagonal, barco[1].Tam_barco, contador_numero_barcos++ );
        }

        if( letraori == 'V' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_vertical, letrasen_diagonal, barco[1].Tam_barco, contador_numero_barcos++ );
        }

        if( letraori == 'D' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_vertical, letrasen_diagonal, barco[1].Tam_barco, contador_numero_barcos++ );
        }

        acor--;
    }

    ///Para los barcos Cruceros
    while( cruc > 0 )
    {
        ///Do-while que se ejecuta mientras la posicion elegida para el barco sea incorrecta
        do{

            x = rand() % partida.Tam_tablero;           ///Genera las coordendas x e y aleatorias
            y = rand() % partida.Tam_tablero;


            ///Vacia las variables para las siguientes entradas al bucle
            letraori = ' ';
            letrasen_horizontal = ' ';
            letrasen_vertical = ' ';
            letrasen_diagonal = ' ';

            letraori = orientacion[rand() % 3];

            ///Si la orientacion es horizontal genera aleatoriamente una letra de sentido 'D' o 'I'
            if( letraori == 'H' )
            {
                letrasen_horizontal = sentido_derecha_izquierda[rand() % 2];
                letrasen_diagonal = ' ';
            }

            ///Si la orientacion es vertical genera aleatoriamente una letra de sentido 'A' o 'D'
            if( letraori == 'V' )
            {
                letrasen_vertical = sentido_arriba_abajo[rand() % 2];
                letrasen_diagonal = ' ';
            }

            ///Si la orientacion es diagonal genera aleatoriamente 2 letras de sentido 'A' o 'D' y 'D' o 'I'
            if( letraori == 'D' )
            {
                letrasen_vertical = sentido_arriba_abajo[rand() % 2];
                letrasen_diagonal = sentido_derecha_izquierda[rand() % 2];
            }


            resultado = 0;
            if( letraori == 'H' )
            {
                resultado = comprobarPosicion( x, y, letraori, letrasen_horizontal, letrasen_diagonal, jugador, barco[2].Tam_barco );

            }
            if( letraori == 'V' ){

                resultado = comprobarPosicion( x, y, letraori, letrasen_vertical, letrasen_diagonal, jugador, barco[2].Tam_barco );

            }
            if( letraori == 'D' ){

                resultado = comprobarPosicion( x, y, letraori, letrasen_vertical, letrasen_diagonal, jugador, barco[2].Tam_barco );
            }

        }while( resultado == 1 );           ///Ejecuta el bucle mientras no se pueda colocar el barco en las posiciones generadas aleatoriamente


        ///Dependiendo de la orientacion llama a la funcion con los valores generados
        if( letraori == 'H' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_horizontal, letrasen_diagonal, barco[2].Tam_barco, contador_numero_barcos++ );
        }

        if( letraori == 'V' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_vertical, letrasen_diagonal, barco[2].Tam_barco, contador_numero_barcos++ );
        }

        if( letraori == 'D' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_vertical, letrasen_diagonal, barco[2].Tam_barco, contador_numero_barcos++ );
        }

        cruc--;
    }


    ///Para los barcos Destructores
    while( dest > 0 )
    {
        ///Do-while que se ejecuta mientras la posicion elegida para el barco sea incorrecta
        do{

            x = rand() % partida.Tam_tablero;           ///Genera las coordendas x e y aleatorias
            y = rand() % partida.Tam_tablero;


            ///Vacia las variables para las siguientes entradas al bucle
            letraori = ' ';
            letrasen_horizontal = ' ';
            letrasen_vertical = ' ';
            letrasen_diagonal = ' ';

            letraori = orientacion[rand() % 3];

            ///Si la orientacion es horizontal genera aleatoriamente una letra de sentido 'D' o 'I'
            if( letraori == 'H' )
            {
                letrasen_horizontal = sentido_derecha_izquierda[rand() % 2];
                letrasen_diagonal = ' ';
            }

            ///Si la orientacion es vertical genera aleatoriamente una letra de sentido 'A' o 'D'
            if( letraori == 'V' )
            {
                letrasen_vertical = sentido_arriba_abajo[rand() % 2];
                letrasen_diagonal = ' ';
            }

            ///Si la orientacion es diagonal genera aleatoriamente 2 letras de sentido 'A' o 'D' y 'D' o 'I'
            if( letraori == 'D' )
            {
                letrasen_vertical = sentido_arriba_abajo[rand() % 2];
                letrasen_diagonal = sentido_derecha_izquierda[rand() % 2];
            }


            resultado = 0;
            if( letraori == 'H' )
            {
                resultado = comprobarPosicion( x, y, letraori, letrasen_horizontal, letrasen_diagonal, jugador, barco[3].Tam_barco );

            }
            if( letraori == 'V' ){

                resultado = comprobarPosicion( x, y, letraori, letrasen_vertical, letrasen_diagonal, jugador, barco[3].Tam_barco );

            }
            if( letraori == 'D' ){

                resultado = comprobarPosicion( x, y, letraori, letrasen_vertical, letrasen_diagonal, jugador, barco[3].Tam_barco );
            }

        }while( resultado == 1 );           ///Ejecuta el bucle mientras no se pueda colocar el barco en las posiciones generadas aleatoriamente


        ///Dependiendo de la orientacion llama a la funcion con los valores generados
        if( letraori == 'H' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_horizontal, letrasen_diagonal, barco[3].Tam_barco, contador_numero_barcos++ );
        }

        if( letraori == 'V' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_vertical, letrasen_diagonal, barco[3].Tam_barco, contador_numero_barcos++ );
        }

        if( letraori == 'D' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_vertical, letrasen_diagonal, barco[3].Tam_barco, contador_numero_barcos++ );
        }

        dest--;
    }

    ///Para los barcos Fragatas
    while( frag > 0 )
    {
        ///Do-while que se ejecuta mientras la posicion elegida para el barco sea incorrecta
        do{

            x = rand() % partida.Tam_tablero;           ///Genera las coordendas x e y aleatorias
            y = rand() % partida.Tam_tablero;


            ///Vacia las variables para las siguientes entradas al bucle
            letraori = ' ';
            letrasen_horizontal = ' ';
            letrasen_vertical = ' ';
            letrasen_diagonal = ' ';

            letraori = orientacion[rand() % 3];

            ///Si la orientacion es horizontal genera aleatoriamente una letra de sentido 'D' o 'I'
            if( letraori == 'H' )
            {
                letrasen_horizontal = sentido_derecha_izquierda[rand() % 2];
                letrasen_diagonal = ' ';
            }

            ///Si la orientacion es vertical genera aleatoriamente una letra de sentido 'A' o 'D'
            if( letraori == 'V' )
            {
                letrasen_vertical = sentido_arriba_abajo[rand() % 2];
                letrasen_diagonal = ' ';
            }

            ///Si la orientacion es diagonal genera aleatoriamente 2 letras de sentido 'A' o 'D' y 'D' o 'I'
            if( letraori == 'D' )
            {
                letrasen_vertical = sentido_arriba_abajo[rand() % 2];
                letrasen_diagonal = sentido_derecha_izquierda[rand() % 2];
            }


            resultado = 0;
            if( letraori == 'H' )
            {
                resultado = comprobarPosicion( x, y, letraori, letrasen_horizontal, letrasen_diagonal, jugador, barco[4].Tam_barco );

            }
            if( letraori == 'V' ){

                resultado = comprobarPosicion( x, y, letraori, letrasen_vertical, letrasen_diagonal, jugador, barco[4].Tam_barco );

            }
            if( letraori == 'D' ){

                resultado = comprobarPosicion( x, y, letraori, letrasen_vertical, letrasen_diagonal, jugador, barco[4].Tam_barco );
            }

        }while( resultado == 1 );           ///Ejecuta el bucle mientras no se pueda colocar el barco en las posiciones generadas aleatoriamente


        ///Dependiendo de la orientacion llama a la funcion con los valores generados
        if( letraori == 'H' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_horizontal, letrasen_diagonal, barco[4].Tam_barco, contador_numero_barcos++ );
        }

        if( letraori == 'V' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_vertical, letrasen_diagonal, barco[4].Tam_barco, contador_numero_barcos++ );
        }

        if( letraori == 'D' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_vertical, letrasen_diagonal, barco[4].Tam_barco, contador_numero_barcos++ );
        }

        frag--;
    }

    ///Para los barcos Submarinos
    while( subm > 0 )
    {
        ///Do-while que se ejecuta mientras la posicion elegida para el barco sea incorrecta
        do{

            x = rand() % partida.Tam_tablero;           ///Genera las coordendas x e y aleatorias
            y = rand() % partida.Tam_tablero;


            ///Vacia las variables para las siguientes entradas al bucle
            letraori = ' ';
            letrasen_horizontal = ' ';
            letrasen_vertical = ' ';
            letrasen_diagonal = ' ';

            letraori = orientacion[rand() % 3];

            ///Si la orientacion es horizontal genera aleatoriamente una letra de sentido 'D' o 'I'
            if( letraori == 'H' )
            {
                letrasen_horizontal = sentido_derecha_izquierda[rand() % 2];
                letrasen_diagonal = ' ';
            }

            ///Si la orientacion es vertical genera aleatoriamente una letra de sentido 'A' o 'D'
            if( letraori == 'V' )
            {
                letrasen_vertical = sentido_arriba_abajo[rand() % 2];
                letrasen_diagonal = ' ';
            }

            ///Si la orientacion es diagonal genera aleatoriamente 2 letras de sentido 'A' o 'D' y 'D' o 'I'
            if( letraori == 'D' )
            {
                letrasen_vertical = sentido_arriba_abajo[rand() % 2];
                letrasen_diagonal = sentido_derecha_izquierda[rand() % 2];
            }


            resultado = 0;
            if( letraori == 'H' )
            {
                resultado = comprobarPosicion( x, y, letraori, letrasen_horizontal, letrasen_diagonal, jugador, barco[5].Tam_barco );

            }
            if( letraori == 'V' ){

                resultado = comprobarPosicion( x, y, letraori, letrasen_vertical, letrasen_diagonal, jugador, barco[5].Tam_barco );

            }
            if( letraori == 'D' ){

                resultado = comprobarPosicion( x, y, letraori, letrasen_vertical, letrasen_diagonal, jugador, barco[5].Tam_barco );
            }

        }while( resultado == 1 );           ///Ejecuta el bucle mientras no se pueda colocar el barco en las posiciones generadas aleatoriamente


        ///Dependiendo de la orientacion llama a la funcion con los valores generados
        if( letraori == 'H' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_horizontal, letrasen_diagonal, barco[5].Tam_barco, contador_numero_barcos++ );
        }

        if( letraori == 'V' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_vertical, letrasen_diagonal, barco[5].Tam_barco, contador_numero_barcos++ );
        }

        if( letraori == 'D' )
        {
            anadirBarcoFlota( jugador, x, y, letraori, letrasen_vertical, letrasen_diagonal, barco[5].Tam_barco, contador_numero_barcos++ );
        }

        subm--;
    }

    AlmacenarPosicionesBarcos();

}

///Imprime el tablero Flota 
void mostrarTablero( int jugador )
{
    int i, j;


    printf("  ");               ///Espacio para alinear con los índices de fila
    for (j = 0; j < partida.Tam_tablero; j++) {
        printf("  %d ", j);
    }
    printf("\n");

    ///Imprimir la matriz con los indices de las filas
    for (i = 0; i < partida.Tam_tablero; i++) {
        printf("%d | ", i);     ///Indice de fila con separador
        for (j = 0; j < partida.Tam_tablero; j++) {
            printf("%c   ", tablero[jugador].Matriz_tablero[i][j] );    ///Espaciado uniforme
        }
        printf("\n");
    }

    printf( "\n" );

}

///Funcion que comprueba si las posiciones dadas son validas
int comprobarPosicion( int x, int y, char orientacion, char sentido, char sentido_diagonal, int jugador, int tam_barco )
{
    int cont;
    int correcto = 0;


    ///Contempla todos los casos posibles de colocacion de un barco(derecha, izquierda, arriba, abajo y las 4 diagonales)
    cont = 0;
    do{
        if( (orientacion == 'H' || orientacion == 'h') && (sentido == 'D' || sentido == 'd') )
        {
            correcto = comprobarPosicionBase(x, y++, jugador);
        }

        if( (orientacion == 'H' || orientacion == 'h') && (sentido == 'I' || sentido == 'i') )
        {
            correcto = comprobarPosicionBase(x, y--, jugador);
        }

        if( (orientacion == 'V' || orientacion == 'v') && (sentido == 'A' || sentido == 'a') )
        {
            correcto = comprobarPosicionBase(x--, y, jugador);
        }

        if( (orientacion == 'V' || orientacion == 'v') && (sentido == 'D' || sentido == 'd') )
        {
            correcto = comprobarPosicionBase(x++, y, jugador);
        }

        if( (orientacion == 'D' || orientacion == 'd') && (sentido == 'A' || sentido == 'a') && (sentido_diagonal == 'D' || sentido_diagonal == 'd') )
        {
            correcto = comprobarPosicionBase(x--, y++, jugador);
        }

        if( (orientacion == 'D' || orientacion == 'd') && (sentido == 'A' || sentido == 'a') && (sentido_diagonal == 'I' || sentido_diagonal == 'i') )
        {
            correcto = comprobarPosicionBase(x--, y--, jugador);
        }

        if( (orientacion == 'D' || orientacion == 'd') && (sentido == 'D' || sentido == 'd') && (sentido_diagonal == 'I' || sentido_diagonal == 'i') )
        {
            correcto = comprobarPosicionBase(x++, y--, jugador);
        }

        if( (orientacion == 'D' || orientacion == 'd') && (sentido == 'D' || sentido == 'd') && (sentido_diagonal == 'D' || sentido_diagonal == 'd') )
        {
            correcto = comprobarPosicionBase(x++, y++, jugador);
        }


        cont++;
    }while( correcto == 0 && cont < tam_barco );


    return correcto;
}

///Funcion que comprueba las 8 posiciones de alrededor de cada casilla y lo va a hacer tantas veces como tamaño de barco sea
int comprobarPosicionBase( int x, int y, int jugador )
{
    int resultado = 0;

    if( tablero[jugador].Matriz_tablero[x][y] == 'X' )
    {
        resultado = 1;
    }

    if( tablero[jugador].Matriz_tablero[x][y+1] == 'X' || y >= partida.Tam_tablero )
    {
        resultado = 1;
    }

    if( tablero[jugador].Matriz_tablero[x][y-1] == 'X' || y < 0 )
    {
        resultado = 1;
    }

    if( tablero[jugador].Matriz_tablero[x-1][y] == 'X' || x < 0 )
    {
        resultado = 1;
    }

    if( tablero[jugador].Matriz_tablero[x+1][y] == 'X' || x >= partida.Tam_tablero )
    {
        resultado = 1;
    }

    if( tablero[jugador].Matriz_tablero[x-1][y-1] == 'X' || y < 0 || x < 0 )
    {
        resultado = 1;
    }

    if( tablero[jugador].Matriz_tablero[x-1][y+1] == 'X' || y >= partida.Tam_tablero || x < 0 )
    {
        resultado = 1;
    }

    if( tablero[jugador].Matriz_tablero[x+1][y-1] == 'X' || y < 0 || x >= partida.Tam_tablero )
    {
        resultado = 1;
    }

    if( tablero[jugador].Matriz_tablero[x+1][y+1] == 'X' || y >= partida.Tam_tablero || x >= partida.Tam_tablero )
    {
        resultado = 1;
    }

    return resultado;

}

///Funcion que añade el barco introducido en el tablero flota del jugador que llama la funcion 
void anadirBarcoFlota( int jugador, int x, int y, char orientacion, char sentido, char sentido_diagonal, int tam_barco, int contador_numero_barcos )
{
    int i, j;
    int cont;
    int auxX = x;
    int auxY = y;
    int jug;            ///Variable que controla el indice de los barcos que tiene cada jugador

    if( jugador == 0 )
    {
        jug = 0;
    }

    if( jugador == 2 )
    {
        jug = 1;
    }

    ///Coloca la X en caso de que se desplace para la derecha desde la posicion base
    cont = 0;
    if( (orientacion == 'H' || orientacion == 'h') && (sentido == 'D' || sentido == 'd') )
    {
        while( cont < tam_barco )
        {
            tablero[jugador].Matriz_tablero[x][y++] = 'X';

            cont++;
        }
    }

    ///Coloca la X en caso de que se desplace para la izquierda desde la posicion base
    cont = 0;
    if( (orientacion == 'H' || orientacion == 'h') && (sentido == 'I' || sentido == 'i') )
    {
        while( cont < tam_barco )
        {
            tablero[jugador].Matriz_tablero[x][y--] = 'X';

            cont++;
        }
    }

    ///Coloca la X en caso de que se desplace para arriba desde la posicion base
    cont = 0;
    if( (orientacion == 'V' || orientacion == 'v') && (sentido == 'A' || sentido == 'a') )
    {
        while( cont < tam_barco )
        {
            tablero[jugador].Matriz_tablero[x--][y] = 'X';

            cont++;
        }
    }

    ///Coloca la X en caso de que se desplace para abajo desde la posicion base
    cont = 0;
    if( (orientacion == 'V' || orientacion == 'v') && (sentido == 'D' || sentido == 'd') )
    {
        while( cont < tam_barco )
        {
            tablero[jugador].Matriz_tablero[x++][y] = 'X';

            cont++;
        }
    }

    ///Coloca la X en caso de que se desplace en diagonal para arriba a la derecha
    cont = 0;
    if( (orientacion == 'D' || orientacion == 'd') && (sentido == 'A' || sentido == 'a') && (sentido_diagonal == 'D' || sentido_diagonal == 'd') )
    {
        while( cont < tam_barco )
        {
            tablero[jugador].Matriz_tablero[x--][y++] = 'X';

            cont++;
        }
    }

    ///Coloca la X en caso de que se desplace en diagonal para arriba a la izquierda
    cont = 0;
    if( (orientacion == 'D' || orientacion == 'd') && (sentido == 'A' || sentido == 'a') && (sentido_diagonal == 'I' || sentido_diagonal == 'i') )
    {
        while( cont < tam_barco )
        {
            tablero[jugador].Matriz_tablero[x--][y--] = 'X';

            cont++;
        }
    }

    ///Coloca la X en caso de que se desplace en diagonal para abajo a la izquierda
    cont = 0;
    if( (orientacion == 'D' || orientacion == 'd') && (sentido == 'D' || sentido == 'd') && (sentido_diagonal == 'I' || sentido_diagonal == 'i') )
    {
        while( cont < tam_barco )
        {
            tablero[jugador].Matriz_tablero[x++][y--] = 'X';

            cont++;
        }
    }

    ///Coloca la X en caso de que se desplace en diagonal para abajo a la derecha
    cont = 0;
    if( (orientacion == 'D' || orientacion == 'd') && (sentido == 'D' || sentido == 'd') && (sentido_diagonal == 'D' || sentido_diagonal == 'd') )
    {
        while( cont < tam_barco )
        {
            tablero[jugador].Matriz_tablero[x++][y++] = 'X';

            cont++;
        }
    }


}

///Funcion que muestra el resumen de la partida que se acaba de jugar
void mostrarResumen()
{
    int i, j;
    int vacias1 = 0, aguas1 = 0, tocadas1 = 0, hundidas1 = 0, barcos_hundidos1 = 0, barcos_restantes1 = 0;
    int vacias2 = 0, aguas2 = 0, tocadas2 = 0, hundidas2 = 0, barcos_hundidos2 = 0, barcos_restantes2 = 0;

    system( "cls" );

    printf( "\n\n==============================================RESUMEN==============================================\n\n" );

    ///Cuenta las casillas vacias del jugador 1
    for( i = 0; i < partida.Tam_tablero; i++ )
    {
        for( j = 0; j < partida.Tam_tablero; j++ )
        {
            if( tablero[1].Matriz_tablero[i][j] == '-' )
            {
                vacias1++;
            }
        }
    }

    ///Cuenta las casillas vacias del jugador 2
    for( i = 0; i < partida.Tam_tablero; i++ )
    {
        for( j = 0; j < partida.Tam_tablero; j++ )
        {
            if( tablero[3].Matriz_tablero[i][j] == '-' )
            {
                vacias2++;
            }
        }
    }

    ///Cuenta las casillas agua del jugador 1
    for( i = 0; i < partida.Tam_tablero; i++ )
    {
        for( j = 0; j < partida.Tam_tablero; j++ )
        {
            if( tablero[1].Matriz_tablero[i][j] == '*' )
            {
                aguas1++;
            }
        }
    }

    ///Cuenta las casillas agua del jugador 2
    for( i = 0; i < partida.Tam_tablero; i++ )
    {
        for( j = 0; j < partida.Tam_tablero; j++ )
        {
            if( tablero[3].Matriz_tablero[i][j] == '*' )
            {
                aguas2++;
            }
        }
    }

    ///Cuenta las casillas tocadas del jugador 1
    for( i = 0; i < partida.Tam_tablero; i++ )
    {
        for( j = 0; j < partida.Tam_tablero; j++ )
        {
            if( tablero[1].Matriz_tablero[i][j] == 'T' )
            {
                tocadas1++;
            }
        }
    }

    ///Cuenta las casillas tocadas del jugador 2
    for( i = 0; i < partida.Tam_tablero; i++ )
    {
        for( j = 0; j < partida.Tam_tablero; j++ )
        {
            if( tablero[3].Matriz_tablero[i][j] == 'T' )
            {
                tocadas2++;
            }
        }
    }

    ///Cuenta las casillas hundidas del jugador 1
    for( i = 0; i < partida.Tam_tablero; i++ )
    {
        for( j = 0; j < partida.Tam_tablero; j++ )
        {
            if( tablero[1].Matriz_tablero[i][j] == 'H' )
            {
                hundidas1++;
            }
        }
    }

    ///Cuenta las casillas hundidas del jugador 2
    for( i = 0; i < partida.Tam_tablero; i++ )
    {
        for( j = 0; j < partida.Tam_tablero; j++ )
        {
            if( tablero[3].Matriz_tablero[i][j] == 'H' )
            {
                hundidas2++;
            }
        }
    }

    ///Barcos que ha hundido el jugador 1
    for( i = 0; i < partida.Num_barcos; i++ )
    {
        if( barcopartida[1].Hundido[i] == 'H' )
        {
            barcos_hundidos1++;
        }
    }

    ///Barcos que ha hundido el jugador 2
    for( i = 0; i < partida.Num_barcos; i++ )
    {
        if( barcopartida[0].Hundido[i] == 'H' )
        {
            barcos_hundidos2++;
        }
    }

    ///Barcos que le faltan por hundir al jugador 1
    for( i = 0; i < partida.Num_barcos; i++ )
    {
        if( barcopartida[1].Hundido[i] == 'T' )
        {
            barcos_restantes1++;
        }
    }

    ///Barcos que le faltan por hundir al jugador 2
    for( i = 0; i < partida.Num_barcos; i++ )
    {
        if( barcopartida[0].Hundido[i] == 'T' )
        {
            barcos_restantes2++;
        }
    }


    printf( "            |              Valor de las Casillas              |              Barcos            |\n" );
    printf( "  Jugador   |  Disparos  | Vacias | Agua | Tocadas | Hundidas | Hundidos | Restantes | Ganador |\n" );
    printf( "------------|------------|--------|------|---------|----------|----------|-----------|---------|\n" );
    printf( " Jugador 1  |     %d     |   %d   |  %d  |    %d    |    %d     |    %d     |     %d     |   %d    |\n", jugador[0].Num_disparo, vacias1, aguas1, tocadas1, hundidas1, barcos_hundidos1, barcos_restantes1, jugador[0].Indicador );
    printf( " Jugador 2  |     %d     |   %d   |  %d  |    %d    |    %d     |    %d     |     %d     |   %d    |\n", jugador[1].Num_disparo, vacias2, aguas2, tocadas2, hundidas2, barcos_hundidos2, barcos_restantes2, jugador[1].Indicador );

    printf( "Tablero Flota Jugador 1:\n" );
    mostrarTablero( 0 );
    printf( "Tablero Oponente Jugador 1:\n" );
    mostrarTablero( 1 );
    printf( "Tablero Flota Jugador 2:\n" );
    mostrarTablero( 2 );
    printf( "Tablero Oponente Jugador 2:\n" );
    mostrarTablero( 3 );



    system( "pause" );
}

///Funcion que reinicia la partida jugada anteriormente, solo si se ha jugado
void reiniciarPartida()
{
    int i, j, k;

    ///Toma el valor del tamaño del tablero para saber si se ha jugado la partida
    if( partida.Tam_tablero != 0 )
    {

        printf( "\n\n\n===================REINICIANDO PARTIDA...===================\n\n\n" );
        system( "pause" );

        almacenarJuego();                           ///Guarda todos los valores de la partida en el fichero
        cargarJuego();                              ///Almacena de nuevo los valores del fichero en las estructuras

        ///Reinicia los tableros oponentes a '-'
        for( i = 0; i < partida.Tam_tablero; i++ ) 
        {
            for( j = 0; j < partida.Tam_tablero; j++ )
            {
                tablero[1].Matriz_tablero[i][j] = '-';  // Inicializar con espacio
            }
        }

        for( i = 0; i < partida.Tam_tablero; i++ ) 
        {
            for( j = 0; j < partida.Tam_tablero; j++ )
            {
                tablero[3].Matriz_tablero[i][j] = '-';  // Inicializar con espacio
            }
        }

        ///Pone la variable hundido de la estructura barcospartida de todos los barcos y de los 2 jugadores a 'T'
        for( i = 0; i < 2; i++ )
        {
            for( j = 0; j < partida.Num_barcos; j++ )
            {
                barcopartida[i].Hundido[j] = 'T';
            }
        }

        almacenarJuego();

        ///Pone a 0 el ganador de la partida anterior
        jugador[0].Indicador = 0;
        jugador[1].Indicador = 0;

        jugador[0].Num_disparo = 0;
        jugador[1].Num_disparo = 1;

        loop();

    }else{

        printf( "\n\n\n=========Para reiniciar una partida primero tienes que jugarla!!=========\n\n\n" );
        system( "pause" );

    }
}

///Funcion para guardar en la estrucura Barcospartida las posiciones de todos los barcos de cada jugador
void AlmacenarPosicionesBarcos()
{
    int i, j;
    int barco = 0;
    int tamano;
    int xInicial, yInicial, xFinal, yFinal;
    int firstX, firstY, lastX, lastY;


    ///Barcos del Jugador 1
    for( i = 0; i < partida.Tam_tablero; i++ ){
        for( j = 0; j < partida.Tam_tablero; j++ ){

            if (tablero[0].Matriz_tablero[i][j] == 'X' && !visitado[i][j] ){
                ///Variables para guardar la info del barco
                tamano = 0;

                firstX = -1, firstY = -1, lastX = -1, lastY = -1;


                detectarBarco( tablero[0].Matriz_tablero, i, j, &tamano, &firstX, &firstY, &lastX, &lastY );

                barcopartida[0].Posicion_inicial_X[barco] = firstX;
                barcopartida[0].Posicion_inicial_Y[barco] = firstY;
                barcopartida[0].Posicion_final_x[barco] = lastX;
                barcopartida[0].Posicion_final_Y[barco] = lastY;
                barcopartida[0].Tamano_barco[barco] = tamano;
                barcopartida[0].Hundido[barco] = 'T';
                barco++;

            }
        }
    }
    


    ///Barcos del Jugador 2
    memset(visitado, 0, sizeof(visitado));
    barco = 0;
    for( i = 0; i < partida.Tam_tablero; i++ ){
        for( j = 0; j < partida.Tam_tablero; j++ ){

            if (tablero[2].Matriz_tablero[i][j] == 'X' && !visitado[i][j] ){
                ///Variables para guardar la info del barco
                tamano = 0;

                firstX = -1, firstY = -1, lastX = -1, lastY = -1;

                detectarBarco( tablero[2].Matriz_tablero, i, j, &tamano, &firstX, &firstY, &lastX, &lastY );

                barcopartida[1].Posicion_inicial_X[barco] = firstX;
                barcopartida[1].Posicion_inicial_Y[barco] = firstY;
                barcopartida[1].Posicion_final_x[barco] = lastX;
                barcopartida[1].Posicion_final_Y[barco] = lastY;
                barcopartida[1].Tamano_barco[barco] = tamano;
                barcopartida[1].Hundido[barco] = 'T';
                barco++;

            }
        }
    }


}

///Funcion para saber si existe un barco alrededor de la posicion base
void detectarBarco( char matriz[50][50], int x, int y, int *tamano, int *firstX, int *firstY, int *lastX, int *lastY ) {

    if( x < 0 || x >= partida.Tam_tablero || y < 0 || y >= partida.Tam_tablero || matriz[x][y] != 'X' || visitado[x][y] )
        return;


    visitado[x][y] = 1;
    if( *tamano == 0 ){
        *firstX = x;
        *firstY = y;
    }

    *lastX = x;
    *lastY = y;
    (*tamano)++;

    int dx[] = {-1, -1, -1,  0, 0, 1, 1, 1};
    int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

    for( int d = 0; d < 8; d++ ){
        detectarBarco(matriz, x + dx[d], y + dy[d], tamano, firstX, firstY, lastX, lastY);
    }


}