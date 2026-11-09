#ifndef ARTISTA_H_INCLUDED
#define ARTISTA_H_INCLUDED

typedef struct stArtista {
    char idArtista[10];
    char nombre[50]; // Nombre público del Artista
    char contrasenia[20]; // Para el login
    char generoPrincipal[30];
} Artista;


#endif // ARTISTA_H_INCLUDED
