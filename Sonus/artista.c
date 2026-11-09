#include "artista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int existeArtista(char id[])
{
    FILE *buffer = fopen("artistas.dat", "rb") ;

    Artista a;

    if(buffer == NULL)
    return 0;

    while(fread(&a, sizeof(Artista),1, buffer)==1)
        {
            if(strcmp(a.idArtista, id)==0)
            {
                fclose(buffer);
                return 1;
            }
        }

        fclose(buffer);

        return 0;
}

int registrarArtistas()
{
    FILE *buffer;
    Artista a;

   printf("\nIngresa ID:");
   scanf("%9s", a.idArtista);

   if(existeArtista(a.idArtista)==1)
   {
      printf("\nYa existe este artista.");
      return 0;
   }
   else
   {

   printf("\nNombre:");
   fgets(a.nombre, sizeof(a.nombre), stdin);
   printf("\nIngresa contrasenia:");
   scanf("%19s", a.contrasenia);
   printf("\nGenero Princial: ");
   scanf("%29s", a.generoPrincipal);

   buffer=fopen("artista.dat", "ab");

  if(buffer == NULL)
    return 0;

 fwrite(&a, sizeof(Artista), 1, buffer);



   fclose(buffer);

    return 1;
   }
}
