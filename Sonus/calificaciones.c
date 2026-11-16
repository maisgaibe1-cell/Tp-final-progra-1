#include "calificaciones.h"
#include <stdio.h>
#include <string.h>
#include "calificaciones.h"
#include "canciones.h"
#include "catalogo.h"



static int generarIdCalificacion(void){
    long bytes;
    FILE *archivo = fopen(ARCHIVO_CALIFICACIONES, "rb");

    if (archivo == NULL) {
        return 1;
    }
    fseek(archivo, 0, SEEK_END);
    bytes = ftell(archivo);
    fclose(archivo);

    return (int)(bytes / sizeof(Calificacion)) + 1;
}

void calificarCancion(const char *idUsuario)
{
    char titulo[100];
    Cancion cancion;
    Calificacion nueva;
    FILE *archivo;
    float promedio;
    int puntuacion;

    printf("\nTitulo de la cancion: ");
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    if (!buscarCancionPorTitulo(titulo, &cancion)) {
        printf("\nNo se encontro esa cancion.\n");
        return;
    }
    if (yaCalifico(idUsuario, cancion.idCancion)) {
        printf("\nYa calificaste esta cancion.\n");
        return;
    }

    do {
        puntuacion = leerPuntuacion();
    } while (puntuacion < PUNTUACION_MINIMA || puntuacion > PUNTUACION_MAXIMA);

    sprintf(nueva.idRegistroCal, "CAL%03d", generarIdCalificacion());
    strcpy(nueva.idUsuario, idUsuario);
    strcpy(nueva.idCancion, cancion.idCancion);
    nueva.puntuacion = puntuacion;

    archivo = fopen(ARCHIVO_CALIFICACIONES, "ab");
    if (archivo == NULL) {
        printf("\nNo se pudo guardar la calificacion.\n");
        return;
    }
    fwrite(&nueva, sizeof(Calificacion), 1, archivo);
    fclose(archivo);

    promedio = calcularPromedio(cancion.idCancion);
    actualizarPromedioCancion(cancion.idCancion, promedio);

    printf("\nCalificacion registrada. Promedio actual de la cancion: %.1f\n", promedio);
}


static int obtenerCancionPorId(const char *id, Cancion *encontrada)
{
    Cancion c;
    FILE *archivo = fopen(ARCHIVO_CANCIONES, "rb");

    if (archivo == NULL) {
        return 0;
    }
    while (fread(&c, sizeof(Cancion), 1, archivo) == 1) {
        if (strcmp(c.idCancion, id) == 0) {
            *encontrada = c;
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);

    return 0;
}

void verMisCalificaciones(const char *idUsuario)
{
    Calificacion cal;
    Cancion cancion;
    int hay = 0;
    FILE *archivo = fopen(ARCHIVO_CALIFICACIONES, "rb");

    if (archivo == NULL) {
        printf("\nTodavia no calificaste ninguna cancion.\n");
        return;
    }

    printf("\n--- Mis calificaciones ---\n");
    while (fread(&cal, sizeof(Calificacion), 1, archivo) == 1) {
        if (strcmp(cal.idUsuario, idUsuario) == 0) {
            hay = 1;
            if (obtenerCancionPorId(cal.idCancion, &cancion)) {
                printf("  - %s: %d estrellas (promedio general: %.1f)\n",
                       cancion.titulo, cal.puntuacion, cancion.calificacionPromedio);
            }
        }
    }
    fclose(archivo);

    if (!hay) {
        printf("  Todavia no calificaste ninguna cancion.\n");
    }
}

int yaCalifico(const char *idUsuario, const char *idCancion)
{
    Calificacion c;
    FILE *archivo = fopen(ARCHIVO_CALIFICACIONES, "rb");

    if (archivo == NULL) {
        return 0;
    }
    while (fread(&c, sizeof(Calificacion), 1, archivo) == 1) {
        if (strcmp(c.idUsuario, idUsuario) == 0 && strcmp(c.idCancion, idCancion) == 0) {
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);

    return 0;
}
