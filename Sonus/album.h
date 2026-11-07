#ifndef ALBUM_H_INCLUDED
#define ALBUM_H_INCLUDED

typedef struct stAlbum
{
    char idAlbum[10];
    Artista artista;
    char titulo[100];
    int anioLanzamiento;
    int cantidadCanciones;
} Album;



#endif // ALBUM_H_INCLUDED
