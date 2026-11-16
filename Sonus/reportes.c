#include "canciones.h"
#include "archivos.h"
#include "album.h"
#include "archivos.h"


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
        printf("No hay canciones cargadas.\n");
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
        printf("No hay álbumes cargados.\n");
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
            printf("No hay álbumes lanzados en el último año.\n");
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
