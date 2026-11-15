#include <stdio.h>
#include <string.h>
#include "catalogo.h"
#include "artista.h"
#include "canciones.h"




void listarCancionesDelAlbum(const char *idAlbum)
{
    Cancion c;
    int hay = 0;
    FILE *archivo= fopen(ARCHIVO_CANCIONES, "rb");

    if(archivo != NULL)
    {
        while(fread(&c, sizeof(Cancion), 1, archivo)== 1)
        {
            if(strcmp(c.idAlbum, idAlbum)== 0)
            {
              printf("      - %s (%d:%02d) - Calificacion: %.1f\n", c.titulo,c.duracionSegundos / 60, c.duracionSegundos % 60, c.calificacionPromedio);
              hay = 1;
            }
        }
   fclose(archivo);
    }
   if(!hay)
   {
       printf("      (sin canciones)\n");
   }
}

void listarAlbumesArtista(const char *idArtista)
{
    Album a;
    int hay = 0;
    FILE *archivo= fopen(ARCHIVO_ALBUMES,"rb");

      while (fread(&a, sizeof(Album), 1, archivo) == 1)
        {
            if (strcmp(a.artista.idArtista, idArtista) == 0)
            {
                printf("\n  Album: %s (%d)\n", a.titulo, a.anioLanzamiento);
                listarCancionesDelAlbum(a.idAlbum);
                hay = 1;
            }
        }
        fclose(archivo);
    }
    if (!hay)
    {
        printf("\n  Este artista no tiene albumes.\n");
    }
}


  void verCatalogoArtista(void)
  {
      char nombre[50];
      Artista a;

      printf("\nNombre del artista: ");
      fgets(nombre,sizeof(nombre), stdin);

      if(!buscarArtistaPorNombre(nombre, &a))
      {
          printf("\nNo se encontro el artista.\n");
          return;
      }
     printf("\n--- %s (%s) ---\n", artista.nombre, artista.generoPrincipal);
     listarAlbumesDeArtista(artista.idArtista);
  }

  static int buscarAlbumPorTitulo(const char *titulo, Album *encontrado)
{
    Album a;
    FILE *archivo = fopen(ARCHIVO_ALBUMES, "rb");

    if (archivo == NULL) {
        return 0;
    }
    while (fread(&a, sizeof(Album), 1, archivo) == 1) {
        if (strcmp(a.titulo, titulo) == 0) {
            *encontrado = a;
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);

    return 0;
}

void verCancionesPorAlbum(void)
{
    char titulo[100];
    Album album;

    printf("\nTitulo del album: ");
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    if (!buscarAlbumPorTitulo(titulo, &album)) {
        printf("\nNo se encontro ese album.\n");
        return;
    }
    printf("\n--- %s - %s (%d) ---\n", album.titulo, album.artista.nombre, album.anioLanzamiento);
    listarCancionesDeAlbum(album.idAlbum);
}

int buscarCancionPorTitulo(const char *titulo, Cancion *encontrada)
{
    Cancion c;
    FILE *archivo = fopen(ARCHIVO_CANCIONES, "rb");

    if (archivo == NULL) {
        return 0;
    }
    while (fread(&c, sizeof(Cancion), 1, archivo) == 1) {
        if (strcmp(c.titulo, titulo) == 0) {
            *encontrada = c;
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);

    return 0;
}

static int obtenerAlbumPorId(const char *id, Album *encontrado)
{
    Album a;
    FILE *archivo = fopen(ARCHIVO_ALBUMES, "rb");

    if (archivo == NULL) {
        return 0;
    }
    while (fread(&a, sizeof(Album), 1, archivo) == 1) {
        if (strcmp(a.idAlbum, id) == 0) {
            *encontrado = a;
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);

    return 0;
}

void verInfoCancion(void)
{
    char titulo[100];
    Cancion cancion;
    Album album;

    printf("\nTitulo de la cancion: ");
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    if (!buscarCancionPorTitulo(titulo, &cancion)) {
        printf("\nNo se encontro esa cancion.\n");
        return;
    }

    printf("\n--- %s ---\n", cancion.titulo);
    if (obtenerAlbumPorId(cancion.idAlbum, &album)) {
        printf("Artista: %s\n", album.artista.nombre);
        printf("Album: %s (%d)\n", album.titulo, album.anioLanzamiento);
    }
    printf("Duracion: %d:%02d\n", cancion.duracionSegundos / 60, cancion.duracionSegundos % 60);
    if (cancion.calificacionPromedio == 0) {
        printf("Calificacion promedio: todavia sin calificaciones\n");
    } else {
        printf("Calificacion promedio: %.1f / 5\n", cancion.calificacionPromedio);
    }
}
