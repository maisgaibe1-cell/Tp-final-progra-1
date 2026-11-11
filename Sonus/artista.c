#include "artista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "album.h"
#include "canciones.h"
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

int registrarArtistas()
{
    FILE *buffer;
    Artista a;

   printf("\nIngresa ID:");
   scanf("%9s", a.idArtista);

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

void menuArtista(Artista artistaLogueado)
{
    int opcion;
    do
    {
        printf("\n--- MENU ARTISTA ---\n");
        printf("1. Agregar album\n");
        printf("2. Modificar album\n");
        printf("3. Agregar cancion\n");
        printf("4. Modificar cancion\n");
        printf("5. Mostrar mis canciones\n");
        printf("0. Salir\n");
        scanf("%d", &opcion);
        getchar();
        switch(opcion)
        {
        case 1:
            cargarAlbum(artistaLogueado);
            break;
        case 2:
            modificarAlbum("albumes.dat",artistaLogueado);
            break;
        case 3:
        {
            Cancion nueva = cargarCancion(artistaLogueado);
            if(guardarCancion("canciones.dat", nueva) == 1)
            {
                printf("Cancion guardada\n");
            }
            break;
        }
        case 4:
            modificarCancion("canciones.dat", artistaLogueado);
            break;
        case 5:
            mostrarArchivoCanciones("canciones.dat");
            break;
        }
    }
    while(opcion != 0);
}
