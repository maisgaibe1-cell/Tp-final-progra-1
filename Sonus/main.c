#include <stdio.h>
#include <stdlib.h>
#include "artista.h"
#include "usuario.h"
#include "acceso.h"

int main()
{
printf("\n-----USUARIO-----\n");
 registrarUsuario();
printf("\n--------------\n");

 printf("\n-----ARTISTA-----\n");
 registrarArtistas();
printf("\n--------------\n");


    char idLogueado[10];
    int rol = login(idLogueado);

    if (rol == ROL_USUARIO) {
        printf("\nEntraste como USUARIO. ID: %s\n", idLogueado);
    } else if (rol == ROL_ARTISTA) {
        printf("\nEntraste como ARTISTA. ID: %s\n", idLogueado);
    } else {
        printf("\nNo se pudo iniciar sesion.\n");
    }


    return 0;
}
