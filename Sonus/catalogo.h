#ifndef CATALOGO_H_INCLUDED
#define CATALOGO_H_INCLUDED

#include "album.h"
#include "canciones.h"


void listarCancionesDelAlbum(const char *idAlbum);
void listarAlbumesArtista(const char *idArtista);
void verCatalogoArtista(void);
static int buscarAlbumPorTitulo(const char *titulo, Album *encontrado);
void verCancionesPorAlbum(void);
int buscarCancionPorTitulo(const char *titulo, Cancion *encontrada);
static int obtenerAlbumPorId(const char *id, Album *encontrado);
void verInfoCancion(void);
int buscarArtistaPorNombre(char *nombre, Artista *encontrado);

#endif // CATALOGO_H_INCLUDED
