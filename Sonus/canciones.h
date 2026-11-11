#ifndef CANCIONES_H_INCLUDED
#define CANCIONES_H_INCLUDED
#include "artista.h"
#include "album.h"

typedef struct stCancion {
    char idCancion[10];
    char titulo[100];
    char idAlbum[10]; // Se usa el nombre del Album como relacion (no es FK)
    char idArtista[10]; // Se usa el nombre del Artista como relacion (no es FK)
    int duracionSegundos;
    float calificacionPromedio; // Se calcula dinámicamente o se actualiza
} Cancion;

Cancion cargarCancion(Artista artistaLogueado);
int generarIdCancion(const char nombreArchivo[]);
int guardarCancion(const char nombreArchivo[],Cancion nuevaCancion);
int modificarCancion(const char nombreArchivo[],Artista artistaLogueado);
int buscarCancionPorId(const char nombreArchivo[],Artista artistaLogueado,char idCancion[], Cancion *cancionBuscada);
void mostrarArchivoCanciones(const char nombreArchivo[]);
void mostrarCancion(Cancion c);
#endif // CANCIONES_H_INCLUDED

