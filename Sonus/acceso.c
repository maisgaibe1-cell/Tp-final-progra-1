#include "artista.h"
#include "usuario.h"
#include "acceso.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



static int validarUsuario(char id[], char contrasenia[])
{
    Usuario a;

    FILE *buffer =fopen("usuarios.dat", "rb");

    if(buffer== NULL)
        return 0;


    while(fread(&a, sizeof(Usuario),1, buffer)==1)
    {
        if(strcmp(a.idUsuario, id)==0 && strcmp(a.contrasenia, contrasenia)==0)
        {
        fclose(buffer);
        return ROL_USUARIO;
        }
    }
    fclose(buffer);

    return ROL_NINGUNO;
}

static int validarArtista(char id[], char contrasenia[])
{
    Artista a;

    FILE *buffer =fopen("artistas.dat", "rb");

    if(buffer== NULL)
        return 0;


    while(fread(&a, sizeof(Artista),1, buffer)==1)
    {
        if(strcmp(a.idArtista, id)==0 && strcmp(a.contrasenia, contrasenia)==0)
        {
        fclose(buffer);
        return ROL_ARTISTA;
        }
    }
    fclose(buffer);

    return ROL_NINGUNO;
}

int login(char idLogueado[])
{
    char id[10];
    char contrasenia[20];
    int rol;

    printf("\nID: ");
    scanf("%9s", id);
    printf("Contrasenia: ");
    scanf("%19s", contrasenia);

    rol = validarUsuario(id, contrasenia);
    if (rol == ROL_NINGUNO) {
        rol = validarArtista(id, contrasenia);
    }

    if (rol == ROL_NINGUNO) {
        printf("\nID o contrasenia incorrectos.\n");
    } else {
        strcpy(idLogueado, id);
    }

    return rol;
}
