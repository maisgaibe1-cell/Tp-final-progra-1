#include <stdio.h>
#include <string.h>
#include "album.h"
#include "artista.h"
#define MAX_TAM_NOMBRE 40

Album cargarAlbum(Artista artistaLogueado)
{
    Album album;
    int nombreValido=0;
    int nuevoNumero= generarIdAlbum("albumes.dat");

    printf("Creando album..\n");

    sprintf(album.idAlbum,"ALB%03d", nuevoNumero);

    printf("Titulo\n");
    fgets(album.titulo,sizeof(album.titulo),stdin);
    album.titulo[strcspn(album.titulo,"\n")]='\0';

    printf("Anio lanzamiento\n");
    scanf("%d",&album.anioLanzamiento);
    getchar();

    printf("Cantidad de canciones\n");
    scanf("%d",&album.cantidadCanciones);
    getchar();
    //carga de datos del artista para el album

    Artista artista;
    printf("Datos del artista\n");

    while(nombreValido==0)
    {
        printf("Nombre del artista\n");
        fgets(artista.nombre,sizeof(artista.nombre),stdin);
        artista.nombre[strcspn(artista.nombre,"\n")]='\0';

        if(strcmp(artista.nombre,artistaLogueado.nombre)==0)
        {
            album.artista= artistaLogueado;

            nombreValido=1;
            printf("Artista verificado\n");
        }
        else
        {
            printf("Error. Este nombre no pertenece al artista\n");
        }
    }
    return album;
}
int generarIdAlbum(const char nombreArchivo[])
{
    Album a;
    int maxId=0;
    int num;

    FILE*archivo= fopen(nombreArchivo,"rb");

    if(archivo==NULL)
    {
        return 1;
    }

    while(fread(&a,sizeof(Album),1,archivo)==1)
    {
        sscanf(a.idAlbum, "ALB%d", &num);
        if(num>maxId)
        {
            maxId=num;
        }
    }
    fclose(archivo);
    return maxId + 1;
}
int guardarAlbum(const char nombreArchivo[], Album albumNuevo)
{
    FILE*archivo= fopen(nombreArchivo,"ab");

    size_t escritos;
    if(archivo==NULL)
    {
        return 0;
    }

    escritos= fwrite(&albumNuevo,sizeof(Album),1,archivo);

    fclose(archivo);
    return escritos==1;
}
int modificarAlbum(const char nombreArchivo[],Artista artistaLogueado)
{
    char idAlbum[10];

    FILE*archivo;

    printf("Ingrese el ID del album que desea modificar\n");
    fgets(idAlbum,sizeof(idAlbum),stdin);
    idAlbum[strcspn(idAlbum,"\n")]='\0';

    Album nuevoAlbum;
    Album a;

    if(buscarAlbumPorId(nombreArchivo,artistaLogueado,idAlbum,&nuevoAlbum)==1)
    {
        printf("Titulo\n");
        fgets(nuevoAlbum.titulo,sizeof(nuevoAlbum.titulo),stdin);
        nuevoAlbum.titulo[strcspn(nuevoAlbum.titulo,"\n")]='\0';

        printf("Anio lanzamiento\n");
        scanf("%d",&nuevoAlbum.anioLanzamiento);
        getchar();

        printf("Cantidad de canciones\n");
        scanf("%d",&nuevoAlbum.cantidadCanciones);
        getchar();

        archivo=fopen(nombreArchivo,"r+b");

        if(archivo==NULL)
        {
            printf("Aun no se crearon albumes\n");
            return 0;
        }

        while(fread(&a,sizeof(Album),1, archivo)==1)
        {
            if(strcmp(a.idAlbum,nuevoAlbum.idAlbum)==0)
            {
                fseek(archivo,-(long) sizeof(Album),SEEK_CUR);

                if(fwrite(&nuevoAlbum,sizeof(Album),1,archivo)==1)
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
        printf("No se pudo encontrar un album con ese ID\n");
        return 0;
    }
}
int buscarAlbumPorId(const char nombreArchivo[],Artista artistaLogueado,char idAlbum[], Album *resultado)
{
    FILE* archivo= fopen(nombreArchivo,"rb");

    if(archivo==NULL)
    {
        return 0;
    }

    Album a;

    while(fread(&a,sizeof(Album),1,archivo)==1)
    {
        if((strcmp(a.idAlbum,idAlbum)==0) && (strcmp(a.artista.nombre,artistaLogueado.nombre)==0))
        {
            *resultado=a;
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);
    return 0;
}
void mostrarArchivoAlbumes(const char nombreArchivo[])
{
    FILE* archivo= fopen(nombreArchivo,"rb");

    if(archivo==NULL)
    {
        return;
    }
    Album a;

    while(fread(&a,sizeof(Album),1,archivo)==1)
    {
        mostrarAlbum(a);
    }
    fclose(archivo);
}
void mostrarAlbum(Album a)
{
    printf("ID Album: %s - Titulo: %s -Artista: %s -Genero Artista: %s -Anio de lanzamiento: %d - Cantidad de canciones: %d \n",
           a.idAlbum,
           a.titulo,
           a.artista.nombre,
           a.artista.generoPrincipal,
           a.anioLanzamiento,
           a.cantidadCanciones);
}
