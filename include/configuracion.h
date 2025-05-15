#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfaces.h"
#include "load.h"


void introducir_jugadores();
void introducir_tamano_tablero();
void introducir_tipos_barcos();
void introducirBarcos();
int comprobarBarcos();
void introducir_quien_comienza();
int generarJugadorComienzo();
void mostrarConfiguracion();
void borrarConfiguracion();



#endif
