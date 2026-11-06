#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED
// Estructuras de Artistas, Usuarios, Álbumes, Canciones, y Calificaciones
typedef struct stArtista {
    char idArtista[10];
    char nombre[50]; // Nombre público del Artista
    char contrasenia[20]; // Para el login
    char generoPrincipal[30];
} Artista;

typedef struct stUsuario {
    char idUsuario[10]; // ID de cliente único
    char email[50];
    char contrasenia[20]; // Para el login
    char nickname[30];
} Usuario;

typedef struct stAlbum {
    char idAlbum[10];
    Artista artista;
    char titulo[100];
    int anioLanzamiento;
    int cantidadCanciones;
} Album;

typedef struct stCancion {
    char idCancion[10];
    char titulo[100];
    char idAlbum[10]; // Se usa el nombre del Album como relacion (no es FK)
    char idArtista[10]; // Se usa el nombre del Artista como relacion (no es FK)
    int duracionSegundos;
    float calificacionPromedio; // Se calcula dinámicamente o se actualiza
} Cancion;

typedef struct stCalificacion {
    char idRegistroCal[10];
    char nicknameUsuario[30]; // Se usa el nickname del Usuario como relacion
    char idCancion[10]; // Se usa el título de la Cancion como relacion
    int puntuacion; // Valor de 1 a 5 estrellas
} Calificacion;

typedef struct stFecha {
    int dia;
    int mes;
    int anio;
} Fecha;


#endif // ESTRUCTURAS_H_INCLUDED
