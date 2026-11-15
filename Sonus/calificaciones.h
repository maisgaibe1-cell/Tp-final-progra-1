#ifndef CALIFICACIONES_H_INCLUDED
#define CALIFICACIONES_H_INCLUDED
#include "canciones.h"


#define ARCHIVO_CALIFICACIONES "calificaciones.bin"
#define PUNTUACION_MINIMA 1
#define PUNTUACION_MAXIMA 5

typedef struct stCalificacion {
    char idRegistroCal[10];
    char nicknameUsuario[30];
    char idCancion[10];
    int puntuacion;
} Calificacion;

static int generarIdCalificacion(void);
void calificarCancion(const char *idUsuario);
static int obtenerCancionPorId(const char *id, Cancion *encontrada);
void verMisCalificaciones(const char *idUsuario);

#endif // CALIFICACIONES_H_INCLUDED

