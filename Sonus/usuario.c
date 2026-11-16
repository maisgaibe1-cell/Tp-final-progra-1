#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"
#include <string.h>

int existeUsuario(char id[], Usuario *usuarioBuscado)
{
    FILE *buffer = fopen("usuarios.dat", "rb") ;

    if(buffer == NULL)
    return 0;

    Usuario a;

    while(fread(&a, sizeof(Usuario),1, buffer)==1)
        {
            if(strcmp(a.idUsuario, id)==0)
            {
                *usuarioBuscado=a;
                fclose(buffer);
                return 1;
            }
        }

        fclose(buffer);

        return 0;
}

int registrarUsuario()
{
    FILE *buffer;
    Usuario a;

   printf("\nIngresa ID:");
   scanf("%9s", a.idUsuario);

   if(existeUsuario(a.idUsuario)==1)
   {
      printf("\nYa existe este usuario.");
   }
   else
   {

   printf("\nIngresa email::");
   scanf("%49s", a.email);
   printf("\nIngresa contrasenia:");
   scanf("%19s", a.contrasenia);
   getchar();
   printf("\nNickname: ");
   fgets(a.nickname, sizeof(a.nickname), stdin);


   buffer=fopen("usuarios.dat", "ab");
    if(buffer == NULL)
    return 0;

   fwrite(&a, sizeof(Usuario), 1, buffer);



   fclose(buffer);
  return 1;
  }
}

void menuUsuario(Usuario usuarioLogueado){

    int opcion;

    do{
        printf("\n---MENU USUARIO---\n");
        printf("1. Ver catalogo de un artista\n");
        printf("2. Ver un album\n");
        printf("3. Ver detalle de una cancion\n");
        printf("4. Calificar cancion\n");
        printf("5. Ver mis calificaciones\n");
        printf("6. Mostrar Top 10 mejores canciones\n");
        printf("7. Mostrar albumes lanzados recientemente\n");
        printf("8. Mostrar artista que recibio mas calificaciones\n");
        printf("9. Mostrar el usuario que dejo mas calificaciones\n");
        printf("0. Salir\n");
        scanf("%d", &opcion);
        getchar();

        switch(opcion)
        {
        case 1:
            verCatalogoArtista();
            break;
            case 2:
            verCancionesPorAlbum();
            break;
            case 3:
            verInfoCancion();
            break;
            case 4:
            calificarCancion(usuarioLogueado.idUsuario);
            break;
            case 5:
            verMisCalificaciones(usuarioLogueado.idUsuario);
            break;
            case 6:
            reporteTop10Canciones();
            break;
            case 7:
            reporteAlbumesRecientes();
            break;
           /* case 8:

            break;
            case 9:

            break;
            */
        }
    }
    while(opcion != 0);
}
