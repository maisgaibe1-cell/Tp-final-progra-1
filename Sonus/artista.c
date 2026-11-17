#include "artista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "album.h"
#include "canciones.h"
#include "reportes.h"

int existeArtista(char id[], Artista* artistaBuscado)
{
    FILE *buffer = fopen("artistas.dat", "rb") ;

    if(buffer == NULL)
    return 0;

    Artista a;

    while(fread(&a, sizeof(Artista),1, buffer)==1)
        {
            if(strcmp(a.idArtista, id)==0)
            {
                *artistaBuscado=a;
                fclose(buffer);
                return 1;
            }
        }

        fclose(buffer);

        return 0;
}

int registrarArtistas(char idNuevo[])
{
    FILE *buffer;
    Artista a;

   printf("\nIngresa ID:");
   scanf("%9s", a.idArtista);
   getchar();

   Artista existe;
   if(existeArtista(a.idArtista,&existe)==1)
   {
      printf("\nYa existe este artista.");
      return 0;
   }
   else
   {

   printf("\nNombre:");
   fgets(a.nombre, sizeof(a.nombre), stdin);
   a.nombre[strcspn(a.nombre, "\n")] = '\0';

   printf("\nIngresa contrasenia:");
   scanf("%19s", a.contrasenia);

   printf("\nGenero Princial: ");
   scanf("%29s", a.generoPrincipal);

   buffer=fopen("artistas.dat", "ab");

  if(buffer == NULL)
    return 0;

 fwrite(&a, sizeof(Artista), 1, buffer);
   fclose(buffer);

 printf("\nArtista registrado.\n");
    return 1;
   }
}


int buscarArtistaPorNombre(char *nombre, Artista *encontrado)
{
    Artista a;
    FILE *archivo =fopen(ARCHIVO_ARTISTAS, "rb");

    if(archivo == NULL)
        return 0;

    while(fread(&a, sizeof(Artista),1,archivo) == 1)
    {
        if(strcmp(a.nombre , nombre)== 0)
        {
            *encontrado = a;
            fclose(archivo);
            return 1;
        }
    }
fclose(archivo);
return 0;
}
