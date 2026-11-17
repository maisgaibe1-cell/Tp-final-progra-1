#ifndef CALIFICACIONES_H_INCLUDED
#define CALIFICACIONES_H_INCLUDED
#include "canciones.h"
#include <stdio.h>

#define ARCHIVO_CALIFICACIONES "calificaciones.dat"
#define PUNTUACION_MINIMA 1
#define PUNTUACION_MAXIMA 5

typedef struct stCalificacion {
    char idRegistroCal[10];
    char nicknameUsuario[30];
    char idCancion[10];
    int puntuacion;
} Calificacion;

static int generarIdCalificacion(void);
int yaCalifico(const char *nicknameUsuario, const char *idCancion);
static int sumarPuntuacionesRec(FILE *archivo, const char *idCancion, int *cantidad);
static float calcularPromedio(const char *idCancion);
static int actualizarPromedioCancion(const char *idCancion, float promedio);
static int leerPuntuacion(void);
static int obtenerCancionPorId(const char *id, Cancion *encontrada);
void calificarCancion(const char *nicknameUsuario);
void verMisCalificaciones(const char *nicknameUsuario);
#endif // CALIFICACIONES_H_INCLUDED

