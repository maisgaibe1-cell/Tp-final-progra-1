#ifndef ACCESO_H_INCLUDED
#define ACCESO_H_INCLUDED

#define ROL_NINGUNO 0
#define ROL_USUARIO 1
#define ROL_ARTISTA 2


static int validarUsuario(char id[], char contrasenia[]);
static int validarArtista(char id[], char contrasenia[]);
int login(char idLogueado[]);


#endif // ACCESO_H_INCLUDED
