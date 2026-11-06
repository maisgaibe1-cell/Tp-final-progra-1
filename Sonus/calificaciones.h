#ifndef CALIFICACIONES_H_INCLUDED
#define CALIFICACIONES_H_INCLUDED

typedef struct stCalificacion {
    char idRegistroCal[10];
    char nicknameUsuario[30]; // Se usa el nickname del Usuario como relacion
    char idCancion[10]; // Se usa el título de la Cancion como relacion
    int puntuacion; // Valor de 1 a 5 estrellas
} Calificacion;


#endif // CALIFICACIONES_H_INCLUDED

