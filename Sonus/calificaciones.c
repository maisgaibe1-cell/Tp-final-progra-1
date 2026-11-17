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


int yaCalifico(const char *nicknameUsuario, const char *idCancion)
{
    Calificacion c;
    FILE *archivo = fopen(ARCHIVO_CALIFICACIONES, "rb");

    if (archivo == NULL) {
        return 0;
    }
    while (fread(&c, sizeof(Calificacion), 1, archivo) == 1) {
        if (strcmp(c.nicknameUsuario, nicknameUsuario) == 0 && strcmp(c.idCancion, idCancion) == 0) {
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);

    return 0;
}

static int sumarPuntuacionesRec(FILE *archivo, const char *idCancion, int *cantidad)
{
    Calificacion c;
    int puntos = 0;

    if (fread(&c, sizeof(Calificacion), 1, archivo) != 1)
    {
        return 0;
    }
    if (strcmp(c.idCancion, idCancion) == 0)
    {
        puntos = c.puntuacion;
        (*cantidad)++;
    }

    return puntos + sumarPuntuacionesRec(archivo, idCancion, cantidad);
}

static float calcularPromedio(const char *idCancion)
{
    int suma;
    int cantidad = 0;
    FILE *archivo = fopen(ARCHIVO_CALIFICACIONES, "rb");

    if (archivo == NULL) {
        return 0;
    }
    suma = sumarPuntuacionesRec(archivo, idCancion, &cantidad);
    fclose(archivo);

    if (cantidad == 0) {
        return 0;
    }

    return (float)suma / cantidad;
}

static int actualizarPromedioCancion(const char *idCancion, float promedio)
{
    Cancion c;
    size_t escritos;
    FILE *archivo = fopen(ARCHIVO_CANCIONES, "r+b");

    if (archivo == NULL) {
        return 0;
    }
    while (fread(&c, sizeof(Cancion), 1, archivo) == 1) {
        if (strcmp(c.idCancion, idCancion) == 0) {
            c.calificacionPromedio = promedio;
            fseek(archivo, -(long)sizeof(Cancion), SEEK_CUR);
            escritos = fwrite(&c, sizeof(Cancion), 1, archivo);
            fclose(archivo);
            return escritos == 1;
        }
    }
    fclose(archivo);

    return 0;
}

static int leerPuntuacion(void)
{
    int puntuacion;
    int c;

    printf("Puntuacion (%d a %d): ", PUNTUACION_MINIMA, PUNTUACION_MAXIMA);
    if (scanf("%d", &puntuacion) != 1) {
        puntuacion = 0;
    }
    while ((c = getchar()) != '\n' && c != EOF) { }

    return puntuacion;
}

void calificarCancion(const char *nicknameUsuario)
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

    if (!buscarCancionPorTitulo(titulo, &cancion))
    {
        printf("\nNo se encontro esa cancion.\n");
        return;
    }
    if (yaCalifico(nicknameUsuario, cancion.idCancion)) {
        printf("\nYa calificaste esta cancion.\n");
        return;
    }

    do {
        puntuacion = leerPuntuacion();
    } while (puntuacion < PUNTUACION_MINIMA || puntuacion > PUNTUACION_MAXIMA);

    sprintf(nueva.idRegistroCal, "CAL%03d", generarIdCalificacion());

    strcpy(nueva.nicknameUsuario, nicknameUsuario);

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


void verMisCalificaciones(const char *nicknameUsuario)
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

    while (fread(&cal, sizeof(Calificacion), 1, archivo) == 1)
    {
        if (strcmp(cal.nicknameUsuario, nicknameUsuario) == 0)
        {
            hay = 1;

            if (obtenerCancionPorId(cal.idCancion, &cancion))
            {
                printf("  - %s: %d estrellas (promedio general: %.1f)\n",
                       cancion.titulo,
                       cal.puntuacion,
                       cancion.calificacionPromedio);
            }
        }
    }

    fclose(archivo);

    if (!hay) {
        printf("  Todavia no calificaste ninguna cancion.\n");
    }
}
