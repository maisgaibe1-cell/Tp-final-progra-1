
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "canciones.h"
#include "archivos.h"
#include "album.h"
#include "archivos.h"
#include "fechas.h"

void ordenarPorPromedioDesc(Cancion *canciones, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int posMax = i;
        for (int j = i + 1; j < n; j++)
            if (canciones[j].calificacionPromedio > canciones[posMax].calificacionPromedio)
                posMax = j;

        Cancion aux = canciones[i];
        canciones[i] = canciones[posMax];
        canciones[posMax] = aux;
    }
}

void reporteTop10Canciones(void)
{
    int cant;
    Cancion *canciones = cargarArchivo("canciones.dat", sizeof(Cancion), &cant);

    if (canciones == NULL)
       {
          printf("No hay canciones cargadas.\n");
       }
    else
    {
        ordenarPorPromedioDesc(canciones, cant);

        int limite;

        if (cant < 10){
            limite = cant;
        }
        else{
            limite = 10;
        }

        for (int i = 0; i < limite; i++)
            printf("Cancion: %d. Nombre: %s -Calificacion promedio: %.2f\n", i + 1, canciones[i].titulo,
                   canciones[i].calificacionPromedio);
        free(canciones);
    }
}

void ordenarAlbumesPorAnio(Album *v, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int posMin = i;
        for (int j = i + 1; j < n; j++)
            if (v[j].anioLanzamiento < v[posMin].anioLanzamiento)
                posMin = j;

        Album aux = v[i];
        v[i] = v[posMin];
        v[posMin] = aux;
    }
}

void reporteAlbumesRecientes(void)
{
    int cant;
    Album *albumes = cargarArchivo("albumes.dat", sizeof(Album), &cant);

    if (albumes == NULL)
        printf("No hay �lbumes cargados.\n");
    else
    {
        int anioLimite = anioActual() - 1;
        int cantRecientes = 0;

        // filtra "en el lugar": deja los recientes al principio del mismo arreglo
        for (int i = 0; i < cant; i++)
        {
            if (albumes[i].anioLanzamiento >= anioLimite)
            {
                albumes[cantRecientes] = albumes[i];
                cantRecientes++;
            }
        }

        if (cantRecientes == 0)
            printf("No hay �lbumes lanzados en el �ltimo a�o.\n");
        else
        {
            ordenarAlbumesPorAnio(albumes, cantRecientes);
            for (int i = 0; i < cantRecientes; i++)
                printf("%d - %s (%s)\n", albumes[i].anioLanzamiento,
                       albumes[i].titulo, albumes[i].artista.nombre);
        }
        free(albumes);
    }
}


static int contarCalificacionesDeCancion(const char *idCancion)
{
    Calificacion cal;
    int cantidad = 0;
    FILE *archivo = fopen(ARCHIVO_CALIFICACIONES, "rb");

    if (archivo == NULL) {
        return 0;
    }
    while (fread(&cal, sizeof(Calificacion), 1, archivo) == 1) {
        if (strcmp(cal.idCancion, idCancion) == 0) {
            cantidad++;
        }
    }
    fclose(archivo);

    return cantidad;
}

static int contarCalificacionesDeArtista(const char *idArtista)
{
    Cancion c;
    int total = 0;
    FILE *archivo = fopen(ARCHIVO_CANCIONES, "rb");

    if (archivo == NULL) {
        return 0;
    }
    while (fread(&c, sizeof(Cancion), 1, archivo) == 1) {
        if (strcmp(c.idArtista, idArtista) == 0) {
            total += contarCalificacionesDeCancion(c.idCancion);
        }
    }
    fclose(archivo);

    return total;
}

void reporteArtistaMasCalificado(void)
{
    Artista a;
    Artista mejor;
    int cantidad;
    int maximo = 0;
    FILE *archivo = fopen(ARCHIVO_ARTISTAS, "rb");

    if (archivo == NULL) {
        printf("\nNo hay artistas registrados.\n");
        return;
    }
    while (fread(&a, sizeof(Artista), 1, archivo) == 1) {
        cantidad = contarCalificacionesDeArtista(a.idArtista);
        if (cantidad > maximo) {
            maximo = cantidad;
            mejor = a;
        }
    }
    fclose(archivo);

    if (maximo == 0) {
        printf("\nTodavia no hay calificaciones.\n");
        return;
    }
    printf("\n--- Artista mas calificado ---\n");
    printf("%s (%s) - %d calificaciones\n", mejor.nombre, mejor.generoPrincipal, maximo);
}

static int contarCalificacionesDeUsuario(const char *nicknameUsuario)
{
    Calificacion cal;
    int cantidad = 0;
    FILE *archivo = fopen(ARCHIVO_CALIFICACIONES, "rb");

    if (archivo == NULL) {
        return 0;
    }
    while (fread(&cal, sizeof(Calificacion), 1, archivo) == 1) {
        if (strcmp(cal.nicknameUsuario, idUsuario) == 0) {
            cantidad++;
        }
    }
    fclose(archivo);

    return cantidad;
}

void reporteUsuarioMasActivo(void)
{
    Usuario u;
    Usuario mejor;
    int cantidad;
    int maximo = 0;
    FILE *archivo = fopen(ARCHIVO_USUARIOS, "rb");

    if (archivo == NULL) {
        printf("\nNo hay usuarios registrados.\n");
        return;
    }
    while (fread(&u, sizeof(Usuario), 1, archivo) == 1) {
        cantidad = contarCalificacionesDeUsuario(u.nickname);
        if (cantidad > maximo) {
            maximo = cantidad;
            mejor = u;
        }
    }
    fclose(archivo);

    if (maximo == 0) {
        printf("\nTodavia no hay calificaciones.\n");
        return;
    }
    printf("\n--- Usuario mas activo ---\n");
    printf("%s - %d calificaciones\n", mejor.nickname, maximo);
}
