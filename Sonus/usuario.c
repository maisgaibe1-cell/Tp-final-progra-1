#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"
#include <string.h>

int existeUsuario(char id[])
{
    FILE *buffer = fopen("Usuarios.dat", "rb") ;

    Usuario a;

    if(buffer == NULL)
    return 0;

    while(fread(&a, sizeof(Usuario),1, buffer)==1)
        {
            if(strcmp(a.idUsuario, id)==0)
            {
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
      printf("\nYa existe este artista.");
   }
   else
   {

   printf("\nIngresa email::");
   scanf("%49s", a.email);
   printf("\nIngresa contrasenia:");
   scanf("%19s", a.contrasenia);
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
