#include "datosPrueba.h"
#include <stdio.h>
#include <string.h>
#include "artista.h"
#include "usuario.h"
#include "album.h"
#include "canciones.h"
#include "calificaciones.h"

#define CANT_ARTISTAS 3
#define CANT_USUARIOS 4
#define CANT_ALBUMES 5
#define CANT_CANCIONES 14
#define CANT_CALIFICACIONES 22

static Artista armarArtista(const char *id, const char *nombre, const char *genero)
{
    Artista a;
    memset(&a, 0, sizeof(Artista));
    strcpy(a.idArtista, id);
    strcpy(a.nombre, nombre);
    strcpy(a.contrasenia, "1234");
    strcpy(a.generoPrincipal, genero);
    return a;
}

static Usuario armarUsuario(const char *id, const char *email, const char *nickname)
{
    Usuario u;
    memset(&u, 0, sizeof(Usuario));
    strcpy(u.idUsuario, id);
    strcpy(u.email, email);
    strcpy(u.contrasenia, "1234");
    strcpy(u.nickname, nickname);
    return u;
}

static Album armarAlbum(const char *id, Artista artista, const char *titulo, int anio, int cantCanciones)
{
    Album a;
    memset(&a, 0, sizeof(Album));
    strcpy(a.idAlbum, id);
    a.artista = artista;
    strcpy(a.titulo, titulo);
    a.anioLanzamiento = anio;
    a.cantidadCanciones = cantCanciones;
    return a;
}

static Cancion armarCancion(const char *id, const char *titulo, const char *idAlbum,
                            const char *idArtista, int duracion)
{
    Cancion c;
    memset(&c, 0, sizeof(Cancion));
    strcpy(c.idCancion, id);
    strcpy(c.titulo, titulo);
    strcpy(c.idAlbum, idAlbum);
    strcpy(c.idArtista, idArtista);
    c.duracionSegundos = duracion;
    c.calificacionPromedio = 0.0;
    return c;
}

static Calificacion armarCalificacion(const char *id, const char *nicknameUsuario,
                                      const char *idCancion, int puntuacion)
{
    Calificacion c;
    memset(&c, 0, sizeof(Calificacion));
    strcpy(c.idRegistroCal, id);
    strcpy(c.nicknameUsuario, nicknameUsuario);
    strcpy(c.idCancion, idCancion);
    c.puntuacion = puntuacion;
    return c;
}

static void calcularPromedios(Cancion *canciones, int cantC, Calificacion *calif, int cantK)
{
    for (int i = 0; i < cantC; i++)
    {
        int suma = 0;
        int cantidad = 0;

        for (int j = 0; j < cantK; j++)
        {
            if (strcmp(calif[j].idCancion, canciones[i].idCancion) == 0)
            {
                suma += calif[j].puntuacion;
                cantidad++;
            }
        }
        if (cantidad > 0)
            canciones[i].calificacionPromedio = (float)suma / cantidad;
    }
}

static int existeArchivo(const char *ruta)
{
    FILE *archivo = fopen(ruta, "rb");
    int existe = (archivo != NULL);

    if (existe)
        fclose(archivo);
    return existe;
}

static int guardarRegistros(const char *ruta, const void *registros, size_t tam, int cantidad)
{
    FILE *archivo = fopen(ruta, "wb");
    int escritos = 0;

    if (archivo != NULL)
    {
        escritos = fwrite(registros, tam, cantidad, archivo);
        fclose(archivo);
    }
    return escritos == cantidad;
}

int cargarDatosDePrueba(void)
{
    if (existeArchivo("artistas.dat"))
        return 0;

    Artista artistas[CANT_ARTISTAS] = {
        armarArtista("ART001", "Luna Roja", "Rock"),
        armarArtista("ART002", "Mar Azul", "Pop"),
        armarArtista("ART003", "DJ Nube", "Electronica")
    };

    Usuario usuarios[CANT_USUARIOS] = {
        armarUsuario("USR001", "ana@mail.com", "anaMusic"),
        armarUsuario("USR002", "beto@mail.com", "betoRock"),
        armarUsuario("USR003", "caro@mail.com", "caroBeat"),
        armarUsuario("USR004", "dani@mail.com", "daniSound")
    };

    Album albumes[CANT_ALBUMES] = {
        armarAlbum("ALB001", artistas[0], "Fuego Lento", 2019, 3),
        armarAlbum("ALB002", artistas[0], "Cenizas", 2026, 3),
        armarAlbum("ALB003", artistas[1], "Oceano", 2025, 3),
        armarAlbum("ALB004", artistas[1], "Primera Ola", 2021, 2),
        armarAlbum("ALB005", artistas[2], "Neon", 2026, 3)
    };

    Cancion canciones[CANT_CANCIONES] = {
        armarCancion("CAN001", "Brasas", "ALB001", "ART001", 215),
        armarCancion("CAN002", "Humo", "ALB001", "ART001", 198),
        armarCancion("CAN003", "Noche Larga", "ALB001", "ART001", 243),
        armarCancion("CAN004", "Cenizas", "ALB002", "ART001", 187),
        armarCancion("CAN005", "Renacer", "ALB002", "ART001", 261),
        armarCancion("CAN006", "Ultima Chispa", "ALB002", "ART001", 224),
        armarCancion("CAN007", "Marea", "ALB003", "ART002", 205),
        armarCancion("CAN008", "Sal y Arena", "ALB003", "ART002", 192),
        armarCancion("CAN009", "Horizonte", "ALB003", "ART002", 233),
        armarCancion("CAN010", "Orilla", "ALB004", "ART002", 178),
        armarCancion("CAN011", "Espuma", "ALB004", "ART002", 201),
        armarCancion("CAN012", "Pulso", "ALB005", "ART003", 256),
        armarCancion("CAN013", "Luces", "ALB005", "ART003", 289),
        armarCancion("CAN014", "Vacio", "ALB005", "ART003", 244)
    };

    Calificacion calificaciones[CANT_CALIFICACIONES] = {
        armarCalificacion("CAL001", "USR001", "CAN001", 5),
        armarCalificacion("CAL002", "USR001", "CAN002", 4),
        armarCalificacion("CAL003", "USR001", "CAN004", 5),
        armarCalificacion("CAL004", "USR001", "CAN005", 4),
        armarCalificacion("CAL005", "USR001", "CAN007", 5),
        armarCalificacion("CAL006", "USR001", "CAN009", 3),
        armarCalificacion("CAL007", "USR001", "CAN012", 4),
        armarCalificacion("CAL008", "USR001", "CAN013", 5),
        armarCalificacion("CAL009", "USR002", "CAN001", 4),
        armarCalificacion("CAL010", "USR002", "CAN003", 3),
        armarCalificacion("CAL011", "USR002", "CAN007", 5),
        armarCalificacion("CAL012", "USR002", "CAN008", 4),
        armarCalificacion("CAL013", "USR002", "CAN012", 2),
        armarCalificacion("CAL014", "USR002", "CAN004", 3),
        armarCalificacion("CAL015", "USR003", "CAN007", 4),
        armarCalificacion("CAL016", "USR003", "CAN008", 5),
        armarCalificacion("CAL017", "USR003", "CAN010", 3),
        armarCalificacion("CAL018", "USR003", "CAN001", 5),
        armarCalificacion("CAL019", "USR003", "CAN006", 4),
        armarCalificacion("CAL020", "USR004", "CAN007", 5),
        armarCalificacion("CAL021", "USR004", "CAN013", 3),
        armarCalificacion("CAL022", "USR004", "CAN002", 2)
    };

    calcularPromedios(canciones, CANT_CANCIONES, calificaciones, CANT_CALIFICACIONES);

    return guardarRegistros("artistas.dat", artistas, sizeof(Artista), CANT_ARTISTAS)
        && guardarRegistros("usuarios.dat", usuarios, sizeof(Usuario), CANT_USUARIOS)
        && guardarRegistros("albumes.dat", albumes, sizeof(Album), CANT_ALBUMES)
        && guardarRegistros("canciones.dat", canciones, sizeof(Cancion), CANT_CANCIONES)
        && guardarRegistros("calificaciones.dat", calificaciones, sizeof(Calificacion), CANT_CALIFICACIONES);
}
