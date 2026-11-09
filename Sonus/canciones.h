#ifndef CANCIONES_H_INCLUDED
#define CANCIONES_H_INCLUDED

typedef struct stCancion {
    char idCancion[10];
    char titulo[100];
    char idAlbum[10]; // Se usa el nombre del Album como relacion (no es FK)
    char idArtista[10]; // Se usa el nombre del Artista como relacion (no es FK)
    int duracionSegundos;
    float calificacionPromedio; // Se calcula dinámicamente o se actualiza
} Cancion;


#endif // CANCIONES_H_INCLUDED

