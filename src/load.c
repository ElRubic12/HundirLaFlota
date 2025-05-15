#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "load.h"

Barcos *barco;
Partidas partida;
Tableros *tablero;
Jugadores *jugador;


///Funcion que inicializa el numero de barcos de cada tipo a 0
void inicializarValores()
{
    partida.Portaaviones = 0;
    partida.Acorazado = 0;
    partida.Crucero = 0;
    partida.Destructor = 0;
    partida.Fragata = 0;
    partida.Submarino = 0;

}

///Funcion que almacena en las estructuras Barcos barco los valores que hay en el fichero Barcos.txt
void cargarBarcos()
{
    int TAM;
    int i = 0;
    char c;
    int numTiposBarcos;

    FILE *fich;
    fich = fopen( "TXT/Barcos.txt", "r" );

    if( fich == NULL )
    {
        printf( "No se ha podido abrir el fichero.\n" );
        exit( 1 );
    }

    rewind( fich );
    fseek( fich, 0, SEEK_END );
    TAM = ftell( fich );       ///TAM almacena todos los caracteres que hay en el fichero
    rewind( fich );

    if( TAM <= 2 )
    {
        numTiposBarcos = 0;      ///TAM toma un valor arbitrario para contar el numero de tipos de barcos
    }else{
        if( TAM >= 3 )
            numTiposBarcos = 1;

        while( (c = fgetc(fich)) != EOF ){

            if( c == '\n' )      ///Cada salto de linea aumenta el numero de tipos de barcos
                numTiposBarcos++;
        }
    }


    barco = (Barcos*)malloc( numTiposBarcos * sizeof(Barcos) );

    rewind(fich);

    while( !feof(fich) && numTiposBarcos > 0 ) ///Mientras no llegue al final del fichero y el numero de tipos de barcos sea mayor que uno
    {
        
        fscanf(fich, "%19[^-]-%c-%d\n", barco[i].Nomb_barco, &barco[i].Id_barco, &barco[i].Tam_barco);


        i++;
    }


    fclose( fich );
}

///Funcion que almacena en las estructuras correspondientes todos los datos que hay en el fichero Juego.txt
void cargarJuego()
{
    int TAM;
    int i = 0, j = 0;
    char c;
    char buffer_numeros[20];       ///Vector que va almacenando todos los caracteres del fichero antes de introducirlos en el vector numeros
    int numeros[20];               ///Vector que almacena todos los numeros del fichero juego.txt
    int bufIndex = 0;              ///Indice para cada caracter en vector buffer_numeros
    int numIndex = 0;              ///Indice para cada numero en vector numeros
    int tiposBarcos;               ///Variable que controla el numero de tipos de barcos que hay en el fichero
    int tamanoTablero;             ///Variable que controla el tamaño del tablero(primera posicion del fichero)
    int lineasFichero = 1;         ///Variable que controla el numero de lineas del fichero

    FILE *fich;
    fich = fopen( "TXT/Juego.txt", "r" );

    if( fich == NULL )
    {
        printf( "No se ha podido abrir el fichero.\n" );
        exit( 1 );
    }

    printf( "\nEl fichero juego.txt se ha abierto.\n\n" );         ///==================DEBUG=====================

    rewind( fich );

    ///Lee caracter a caracter y los numeros enteros los almacena en el vector numeros
    while( (c = fgetc(fich)) != EOF ){
        if( c == '\n' )      ///Cada salto de linea aumenta el numero de lineas que hay en el fichero
                lineasFichero++;

        if( isdigit(c) ){
            buffer_numeros[bufIndex++] = c;     /// Acumular dígitos en el buffer

        }else if( c == '-' || c == '\n' ){
            if( bufIndex > 0 ){
                buffer_numeros[bufIndex] = '\0';                 ///Termina el string borrando el ultimo caracter
                numeros[numIndex++] = atoi(buffer_numeros);      ///Convierte el caracter en numero y lo almacena en numeros
                bufIndex = 0;                                    ///Reiniciar buffer para el siguiente número
            }
        }
    }

    ///Si el ultimo caracter del fichero es un numero entero
    if( bufIndex > 0 ){
        buffer_numeros[bufIndex] = '\0';
        numeros[numIndex++] = atoi(buffer_numeros);    ///Guardar el último caracter si es un numero, como entero en el vector numeros
    }


    rewind( fich );



    char *lineas[100];             ///Vector de punteros para leer los caracteres del fichero
    char buffer_lineas[100];       ///Vector que almacena todas las lineas del fichero
    int lineaCont = 0;             ///Contador para recorrer todas las lineas del fichero


    ///Almacena todas las lineas del fichero en el vector linea
    while( fgets(buffer_lineas, lineasFichero, fich) && lineaCont < lineasFichero ){
        buffer_lineas[strcspn(buffer_lineas, "\n")] = 0;             ///Elimina el salto de línea

        lineas[lineaCont] = malloc(strlen(buffer_lineas) + 1);       ///Reserva memoria para el vector lineas

        strcpy(lineas[lineaCont], buffer_lineas);                    ///Copiar la línea en el vector
        lineaCont++;
    }



    tiposBarcos = numeros[2];


    ///Almacena el numero de tipos de barcos y las cantidades de los mismos

    char *tokens[20];           ///Vector para almacenar los elementos de la línea
    int tokenCont = 0;
    char B[5];                  ///Variable que almacena el identificador del tipo de barco
    int C;                      ///Variable que almacena la cantidad de barcos de cada tipo


    for( i = 1; i <= tiposBarcos; i++ ){
        tokenCont = 0;

        char temp[256];
        strcpy(temp, lineas[i]);

        char *token = strtok(temp, "-");       ///Separar por '-'
        while( token != NULL && tokenCont < 20 ){
            tokens[tokenCont] = malloc(strlen(token) + 1);

            strcpy( tokens[tokenCont], token );
            tokenCont++;
            token = strtok(NULL, "-");
        }

        for( j = 0; j < tokenCont; j++ ){
            strcpy( B, tokens[0] );                ///En la variable B se almacena el identificador del tipo de barco
            C = atoi(tokens[1]);                   ///En la variable C se almacena la cantidad de barcos del tipo de B

            ///Introduce la cantidad de cada tipo de barco en la estructura tablero
            if( strcmp(B, "P") == 0 )
            {
                partida.Portaaviones = C;
            }else if( strcmp(B, "A") == 0 )
            {
                partida.Acorazado = C;
            }else if( strcmp(B, "C") == 0 )
            {
                partida.Crucero = C;
            }else if( strcmp(B, "D") == 0 )
            {
                partida.Destructor = C;
            }else if( strcmp(B, "F") == 0 )
            {
                partida.Fragata = C;
            }else if( strcmp(B, "S") == 0 ){
                partida.Submarino = C;
            }

            free( tokens[j] );         /// /Liberar memoria de los elementos

        }

    }

    ///Almacenar los elementos de tamaño tablero, numero de barcos y numero de tipos de barcos en la estructura
    int tamano_tablero = numeros[0];
    partida.Tam_tablero = tamano_tablero;
    partida.Num_barcos = numeros[1];
    partida.Num_tipos_barcos = tiposBarcos;

    ///===================================DEBUG===================================

    printf( "El tamano del tablero es: %d.\n", partida.Tam_tablero );
    printf( "El numero de barcos es: %d.\n", partida.Num_barcos );
    printf( "El numero de tipos de barcos es: %d.\n", partida.Num_tipos_barcos );
    printf( "El valor de P es: %d.\n", partida.Portaaviones );
    printf( "El valor de A es: %d.\n", partida.Acorazado );
    printf( "El valor de C es: %d.\n", partida.Crucero );
    printf( "El valor de D es: %d.\n", partida.Destructor );
    printf( "El valor de F es: %d.\n", partida.Fragata );
    printf( "El valor de S es: %d.\n", partida.Submarino );
    printf( "\n\n" );




    char linea_jugador1[20];
    char linea_jugador2[20];
    int index_jugador1, index_jugador2;

    index_jugador1 = tiposBarcos + 1;
    index_jugador2 = tamano_tablero * 2 + tiposBarcos + 2;

    strcpy( linea_jugador1, lineas[index_jugador1] );
    strcpy( linea_jugador2, lineas[index_jugador2] );




    int id1, id2;
    char nombre1[20], nombre2[20];
    int num_disparos1, num_disparos2;
    char disparo1[20], disparo2[20];
    int ganador1, ganador2;

    ///Jugador 1
    char *token = strtok(linea_jugador1, "-");     ///Separar por '-'
    if( token ) id1 = atoi(token);                 ///Convertir el primer token a entero

    token = strtok(NULL, "-");
    if( token ) strcpy(nombre1, token);            ///Copiar el nombre

    token = strtok(NULL, "-");
    if (token) num_disparos1 = atoi(token);        ///Convertir el numero de disparos a entero

    token = strtok(NULL, "-");
    if( token ) strcpy(disparo1, token);                  ///Copiar el tipo de disparo

    token = strtok(NULL, "-");
    if (token) ganador1 = atoi(token);              ///Convertir a entero la variable ganador


    ///Jugador 2
    char *token2 = strtok(linea_jugador2, "-");           ///Separar por '-'
    if( token2 ) id2 = atoi(token2);                  ///Convertir el primer token a entero

    token2 = strtok(NULL, "-");
    if( token2 ) strcpy(nombre2, token2);             ///Copiar el nombre

    token2 = strtok(NULL, "-");
    if (token2) num_disparos2 = atoi(token2);        ///Convertir el numero de disparos a entero

    token2 = strtok(NULL, "-");
    if( token2 ) strcpy(disparo2, token2);                   ///Copiar el tipo de disparo

    token2 = strtok(NULL, "-");
    if (token2) ganador2 = atoi(token2);             ///Convertir a entero la variable ganador


    ///Almacenar las variables de los jugadores en la estructura


    jugador[0].Id_jugador = id1;
    strcpy( jugador[0].Nomb_jugador, nombre1 );
    jugador[0].Num_disparo = num_disparos1;
    strcpy( jugador[0].Tipo_disparo, disparo1);
    jugador[0].Indicador = ganador1;

    jugador[1].Id_jugador = id2;
    strcpy( jugador[1].Nomb_jugador, nombre2 );
    jugador[1].Num_disparo = num_disparos2;
    strcpy( jugador[1].Tipo_disparo, disparo2);
    jugador[1].Indicador = ganador2;


    ///===============DEBUG=================
    for( i = 0; i < 2; i++ )
    {
        printf( "Jugador %d\n", i+1 );
        printf( "ID: %d\n", jugador[i].Id_jugador );
        printf( "Nombre: %s\n", jugador[i].Nomb_jugador );
        printf( "Disparos: %d\n", jugador[i].Num_disparo );
        printf( "Tipo Disparo: %s\n", jugador[i].Tipo_disparo );
        printf( "Ganador: %d\n", jugador[i].Indicador );
        printf( "\n" );
    }
    printf( "\n" );

    ///Almacenar los tableros de los jugadores en su estructura

    char token3[10];              ///Variable auxiliar para almacenar cada linea del vector lineas
    char caracteres[20];          ///Variable auxiliar para almacenar cada caracter de la linea del vector token3
    int l = tiposBarcos + 2;      ///Indices para acceder a la posicion exacta del tablero en el fichero
    int k = tiposBarcos + 2 + tamano_tablero;  ///Indices para acceder a la posicion exacta del tablero en el fichero


    ///Tablero Jugador 1 - Flota
    int q = 0;
    int w = 0;
    for( i = l; i < k; i++ )
    {
        strcpy(token3, lineas[i] );
        w = 0;
        for( j = 0; j < tamano_tablero; j++ )
        {
            caracteres[j] = token3[j];
            tablero[0].Matriz_tablero[q][w] = caracteres[j];       ///Almacena en la matriz el caracter '-' o 'X'
            w++;
        }
        q++;
    }

    ///Tablero Jugador 1 - Oponente
    l = tiposBarcos + 2 + tamano_tablero;
    k = tiposBarcos + tamano_tablero * 2 + 2;

    q = 0;
    w = 0;
    for( i = l; i < k; i++ )
    {
        strcpy(token3, lineas[i] );
        w = 0;
        for( j = 0; j < tamano_tablero; j++ )
        {
            caracteres[j] = token3[j];
            tablero[1].Matriz_tablero[q][w] = caracteres[j];       ///Almacena en la matriz el caracter '-' o 'X'
            w++;
        }
        q++;
    }



    ///Tablero Jugador 2 - Flota
    l = tiposBarcos + tamano_tablero * 2 + 3;
    k = tiposBarcos + tamano_tablero * 3 + 3;

    q = 0;
    w = 0;
    for( i = l; i < k; i++ )
    {
        strcpy(token3, lineas[i] );
        w = 0;
        for( j = 0; j < tamano_tablero; j++ )
        {
            caracteres[j] = token3[j];
            tablero[2].Matriz_tablero[q][w] = caracteres[j];       ///Almacena en la matriz el caracter '-' o 'X'
            w++;
        }
        q++;
    }


    ///Tablero Jugador 2 - Oponente
    l = tiposBarcos + tamano_tablero * 3 + 3;
    k = tiposBarcos + tamano_tablero * 4 + 3;

    q = 0;
    w = 0;
    for( i = l; i < k; i++ )
    {
        strcpy(token3, lineas[i] );
        w = 0;
        for( j = 0; j < tamano_tablero; j++ )
        {
            caracteres[j] = token3[j];
            tablero[3].Matriz_tablero[q][w] = caracteres[j];       ///Almacena en la matriz el caracter '-' o 'X'
            w++;
        }
        q++;
    }


    ///===============DEBUG=================

    for( i = 0; i < tamano_tablero; i++ )
    {
        for( j = 0; j < tamano_tablero; j++ )
        {
            printf( "%c ", tablero[0].Matriz_tablero[i][j] );
        }
        printf( "\n" );
    }
    printf( "\n" );

    for( i = 0; i < tamano_tablero; i++ )
    {
        for( j = 0; j < tamano_tablero; j++ )
        {
            printf( "%c ", tablero[1].Matriz_tablero[i][j] );
        }
        printf( "\n" );
    }
    printf( "\n" );

    for( i = 0; i < tamano_tablero; i++ )
    {
        for( j = 0; j < tamano_tablero; j++ )
        {
            printf( "%c ", tablero[2].Matriz_tablero[i][j] );
        }
        printf( "\n" );
    }
    printf( "\n" );

    for( i = 0; i < tamano_tablero; i++ )
    {
        for( j = 0; j < tamano_tablero; j++ )
        {
            printf( "%c ", tablero[3].Matriz_tablero[i][j] );
        }
        printf( "\n" );
    }
    printf( "\n" );


    ///Inicializa la variable jugador_inicial_continuador de la estructura Partidas partida con el jugador 1
    partida.Jugador_inicial_continuador = 1;


    fclose( fich );
}

///Funcion que inicializa la variable Tipos_barcos de Partidas partida con los valores de los tipos de barcos que hay en el tablero del fichero Juego.txt
void inicializarTiposBarcos()
{
    int i = 0;

    if( partida.Portaaviones != 0 ){
        partida.Tipos_barcos[i++] = 'P';
    }

    if( partida.Acorazado != 0 ){
        partida.Tipos_barcos[i++] = 'A';
    }

    if( partida.Crucero != 0 ){
        partida.Tipos_barcos[i++] = 'C';
    }

    if( partida.Destructor != 0 ){
        partida.Tipos_barcos[i++] = 'D';
    }

    if( partida.Fragata != 0 ){
        partida.Tipos_barcos[i++] = 'S';
    }

    if( partida.Submarino != 0 ){
        partida.Tipos_barcos[i++] = 'S';
    }


}

///Funcion para incializar todas las estructuras
void inicializarValoresaCero()
{
    int i, j, k;


    jugador = (Jugadores *)malloc( 2 * sizeof(Jugadores) );

    ///Inicializa todas las variables de Jugadores *jugador
    for( i = 0; i < 2; i++ )
    {
        jugador[i].Id_jugador = 0;
        memset( jugador[i].Nomb_jugador, 0, sizeof(jugador[i].Nomb_jugador) );
        jugador[i].Num_disparo = 0;
        memset( jugador[i].Tipo_disparo, 0, sizeof(jugador[i].Tipo_disparo) );
        jugador[i].Indicador = 0;
    }


    ///Inicializa todas las variables de Partidas partida
    partida.Tam_tablero = 0;
    partida.Num_barcos = 0;
    partida.Num_tipos_barcos = 0;

    partida.Portaaviones = 0;
    partida.Acorazado = 0;
    partida.Crucero = 0;
    partida.Destructor = 0;
    partida.Fragata = 0;
    partida.Submarino = 0;

    memset( partida.Tipos_barcos, 0, sizeof(partida.Tipos_barcos) );
    partida.Jugador_inicial_continuador = 0;


    ///Inicializa la variable de la estructuda Tableros tablero de los 4 tableros
    tablero = (Tableros*)malloc(4 * sizeof(Tableros));
    if (tablero == NULL) {
        printf("Error al asignar memoria.\n");
    }


    for( k = 0; k < 4; k++ )
    {
        for( i = 0; i < 50; i++ ) 
        {
            for( j = 0; j < 50; j++ )
            {
                tablero[k].Matriz_tablero[i][j] = '-';  // Inicializar con espacio
            }
        }
    }

}

///Funcion para guardar en el fichero los valores de todas las estructuras
void almacenarJuego()
{
    int i, j, k;

    FILE *fich;
    fich = fopen( "TXT/Juego.txt", "w" );
    if( fich == NULL )
    {
        printf( "No se ha podido abrir el fichero.\n" );
    }else{

        ///Almacena la primera linea(tamaño de tablero, numero de barcos, numero de tipos de barcos)
        fprintf( fich, "%d", partida.Tam_tablero );
        fprintf( fich, "-%d", partida.Num_barcos );
        fprintf( fich, "-%d", partida.Num_tipos_barcos );

        fprintf( fich, "\n" );


        ///Almacena los tipos de barcos y el numero de barcos de cada uno de ellos
        i = 0;
        while( i < partida.Num_tipos_barcos )
        {
            if( partida.Tipos_barcos[i] == 'P' )
            {
                fprintf( fich, "%c-%d", partida.Tipos_barcos[i], partida.Portaaviones );
            }

            if( partida.Tipos_barcos[i] == 'A' )
            {
                fprintf( fich, "%c-%d", partida.Tipos_barcos[i], partida.Acorazado );
            }

            if( partida.Tipos_barcos[i] == 'C' )
            {
                fprintf( fich, "%c-%d", partida.Tipos_barcos[i], partida.Crucero );
            }

            if( partida.Tipos_barcos[i] == 'D' )
            {
                fprintf( fich, "%c-%d", partida.Tipos_barcos[i], partida.Destructor );
            }

            if( partida.Tipos_barcos[i] == 'F' )
            {
                fprintf( fich, "%c-%d", partida.Tipos_barcos[i], partida.Fragata );
            }

            if( partida.Tipos_barcos[i] == 'S' )
            {
                fprintf( fich, "%c-%d", partida.Tipos_barcos[i], partida.Submarino );
            }

            fprintf( fich, "\n" );

            i++;
        }


        ///Almacena los datos del primer jugador
        fprintf( fich, "%d", jugador[0].Id_jugador );
        fprintf( fich, "-%s", jugador[0].Nomb_jugador );
        fprintf( fich, "-%d", jugador[0].Num_disparo );
        fprintf( fich, "-%s", jugador[0].Tipo_disparo );
        fprintf( fich, "-%d", jugador[0].Indicador );

        fprintf( fich, "\n" );


        ///Almacena los tableros del jugador 1(flota y oponente)
        for( k = 0; k < 2; k++ )
        {
            for( i = 0; i < partida.Tam_tablero; i++ )
            {
                for( j = 0; j < partida.Tam_tablero; j++ )
                {
                    fprintf( fich, "%c", tablero[k].Matriz_tablero[i][j] );
                }
                fprintf( fich, "\n" );
            }
        }

        ///Almacena los datos del jugador 2
        fprintf( fich, "%d", jugador[1].Id_jugador );
        fprintf( fich, "-%s", jugador[1].Nomb_jugador );
        fprintf( fich, "-%d", jugador[1].Num_disparo );
        fprintf( fich, "-%s", jugador[1].Tipo_disparo );
        fprintf( fich, "-%d", jugador[1].Indicador );

        fprintf( fich, "\n" );


        ///Almacena los tableros del jugador 2(flota y oponente)
        for( k = 2; k < 4; k++ )
        {
            for( i = 0; i < partida.Tam_tablero; i++ )
            {
                for( j = 0; j < partida.Tam_tablero; j++ )
                {
                    fprintf( fich, "%c", tablero[k].Matriz_tablero[i][j] );
                }

                if (!(k == 3 && i == partida.Tam_tablero - 1)) {
                    fprintf(fich, "\n");
                }
            }
        }


    }

    fclose( fich );
}