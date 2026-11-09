#ifndef ALBUM_H_INCLUDED
#define ALBUM_H_INCLUDED
#include "artista.h"

typedef struct stAlbum
{
    char idAlbum[10];
    Artista artista;
    char titulo[100];
    int anioLanzamiento;
    int cantidadCanciones;
} Album;

Album cargarAlbum(Artista artistaLogueado);
int generarIdAlbum(const char nombreArchivo[]);
int guardarAlbum(const char nombreArchivo[], Album albumNuevo);
int modificarAlbum(const char nombreArchivo[],Artista artistaLogueado);
int buscarPorId(const char nombreArchivo[],Artista artistaLogueado,char idAlbum[], Album *resultado);
void mostrarArchivoAlbumes(const char nombreArchivo[]);
void mostrarAlbum(Album a);
#endif // ALBUM_H_INCLUDED
