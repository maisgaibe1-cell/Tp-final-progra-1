#include <stdio.h>
#include "menus.h"
#include "acceso.h"
#include "usuario.h"
#include "artista.h"
#include "album.h"
#include "canciones.h"
#include "catalogo.h"
#include "calificaciones.h"
#include "reportes.h"


void menuPrincipal(void)
{
    int opcion;
    int rol;
    char idLogueado[10];
    Usuario usuario;
    Artista artista;

    do{
        printf("\n--- SONUS ---\n");
        printf("1. Iniciar sesion\n");
        printf("2. Registrar usuario\n");
        printf("3. Registrar artista\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

         switch (opcion) {
        case 1:
            rol = login(idLogueado);
            if (rol == ROL_USUARIO && existeUsuario(idLogueado, &usuario))
                {
                menuUsuario(usuario);
            } else if (rol == ROL_ARTISTA && existeArtista(idLogueado, &artista)) {
                menuArtista(artista);
            }
            break;
        case 2:
            if (registrarUsuario(idLogueado) && existeUsuario(idLogueado, &usuario)) {
                menuUsuario(usuario);
            }
            break;
        case 3:
            if (registrarArtistas(idLogueado) && existeArtista(idLogueado, &artista)) {
                menuArtista(artista);
            }
            break;
        }
    } while (opcion != 0);
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
            case 8:
            reporteArtistaMasCalificado();
            break;
            case 9:
            reporteUsuarioMasActivo();
            break;

        }
    }
    while(opcion != 0);
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
            cargarAlbum(artistaLogueado);

            break;
        case 2:
            modificarAlbum("albumes.dat",artistaLogueado);
            break;
        case 3:
            Cancion nueva = cargarCancion(artistaLogueado);
            if(guardarCancion("canciones.dat", nueva) == 1)
            {
                printf("Cancion guardada\n");
            }
            break;
        case 4:
            modificarCancion("canciones.dat", artistaLogueado);
            break;
        case 5:
            mostrarArchivoCanciones("canciones.dat");
            break;
         case 6:
            reporteTop10Canciones();
            break;
        case 7:
            reporteAlbumesRecientes();
            break;

        case 8:
           reporteArtistaMasCalificado();

            break;
        case 9:
        reporteUsuarioMasActivo();
            break;

        default:

            break;
        }

    }
    while(opcion != 0);
}
