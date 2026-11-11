#include "canciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "album.h"


Cancion cargarCancion(Artista artistaLogueado){

        Cancion cancion;
        Album albumEncontrado;

        int nombreValido=0;

        printf("Creando cancion...\n");

        printf("ID Album:");
        fgets(cancion.idAlbum,sizeof(cancion.idAlbum),stdin);
        cancion.idAlbum[strcspn(cancion.idAlbum,"\n")]='\0';

        while(buscarAlbumPorId("albumes.dat",artistaLogueado,cancion.idAlbum, &albumEncontrado)==0){
            printf("Este album no existe o no es tuyo, ingresalo de nuevo");

            fgets(cancion.idAlbum,sizeof(cancion.idAlbum),stdin);
            cancion.idAlbum[strcspn(cancion.idAlbum,"\n")]='\0';
        }

        int nuevoNumero= generarIdCancion("canciones.dat");

        sprintf(cancion.idCancion,"CAN%03d",nuevoNumero);

        strcpy(cancion.idArtista,albumEncontrado.artista.idArtista);

        printf("Titulo\n");
        fgets(cancion.titulo,sizeof(cancion.titulo),stdin);
        cancion.titulo[strcspn(cancion.titulo,"\n")]='\0';

        printf("Duracion en segundos\n");
        scanf("%d",&cancion.duracionSegundos);
        getchar();

        cancion.calificacionPromedio= 0.0;

        return cancion;
}
int generarIdCancion(const char nombreArchivo[])
{
    Cancion c;
    int maxId=0;
    int num;

    FILE*archivo= fopen(nombreArchivo,"rb");

    if(archivo==NULL)
    {
        return 1;
    }

    while(fread(&c,sizeof(Cancion),1,archivo)==1)
    {
        sscanf(c.idCancion, "CAN%d", &num);
        if(num>maxId)
        {
            maxId=num;
        }
    }
    fclose(archivo);
    return maxId + 1;
}
int guardarCancion(const char nombreArchivo[],Cancion nuevaCancion){
    FILE*archivo= fopen(nombreArchivo,"ab");

    if(archivo==NULL){
        return 0;
    }

    size_t escritos= fwrite(&nuevaCancion,sizeof(Cancion),1,archivo);

    fclose(archivo);
    return escritos==1;
}
int modificarCancion(const char nombreArchivo[],Artista artistaLogueado){
    char idCancion[10];

    FILE*archivo;

    printf("Ingrese el ID de la cancion que desea modificar\n");
    fgets(idCancion,sizeof(idCancion),stdin);
    idCancion[strcspn(idCancion,"\n")]='\0';

    Cancion nuevaCancion;
    Cancion c;

    if(buscarCancionPorId(nombreArchivo,artistaLogueado,idCancion,&nuevaCancion)==1)
    {
        printf("Titulo\n");
        fgets(nuevaCancion.titulo,sizeof(nuevaCancion.titulo),stdin);
        nuevaCancion.titulo[strcspn(nuevaCancion.titulo,"\n")]='\0';

        printf("Duracion en segundos\n");
        scanf("%d",&nuevaCancion.duracionSegundos);
        getchar();

        archivo=fopen(nombreArchivo,"r+b");

        if(archivo==NULL)
        {
            printf("Aun no se crearon Canciones\n");
            return 0;
        }

        while(fread(&c,sizeof(Cancion),1, archivo)==1)
        {
            if(strcmp(c.idCancion,nuevaCancion.idCancion)==0)
            {
                fseek(archivo,-(long) sizeof(Cancion),SEEK_CUR);

                if(fwrite(&nuevaCancion,sizeof(Cancion),1,archivo)==1)
                {
                    fclose(archivo);
                    return 1;
                }
            }
        }
        fclose(archivo);
        return 0;
    }
    else
    {
        printf("No se pudo encontrar la cancion con ese ID\n");
        return 0;
    }
}
int buscarCancionPorId(const char nombreArchivo[],Artista artistaLogueado,char idCancion[], Cancion *cancionBuscada)
{
    FILE* archivo= fopen(nombreArchivo,"rb");

    if(archivo==NULL)
    {
        return 0;
    }

    Cancion c;

    while(fread(&c,sizeof(Cancion),1,archivo)==1)
    {
        if((strcmp(c.idCancion,idCancion)==0) && (strcmp(c.idArtista,artistaLogueado.idArtista)==0))
        {
            *cancionBuscada=c;
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);
    return 0;
}
void mostrarArchivoCanciones(const char nombreArchivo[])
{
    FILE* archivo= fopen(nombreArchivo,"rb");

    if(archivo==NULL)
    {
        return;
    }
    Cancion c;

    while(fread(&c,sizeof(Cancion),1,archivo)==1)
    {
        mostrarCancion(c);
    }
    fclose(archivo);
}
void mostrarCancion(Cancion c)
{
    printf("ID Cancion: %s - Titulo: %s -ID Album: %s -ID Artista: %s -Duracion(seg): %d - Calificacion Promedio: %f \n",
           c.idCancion,
           c.titulo,
           c.idAlbum,
           c.idArtista,
           c.duracionSegundos,
           c.calificacionPromedio);
}

