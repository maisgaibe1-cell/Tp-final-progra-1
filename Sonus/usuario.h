#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#define ARCHIVO_CANCIONES "canciones.dat"
#define ARCHIVO_USUARIOS "usuarios.dat"
typedef struct stUsuario {
    char idUsuario[10];
    char email[50];
    char contrasenia[20];
    char nickname[30];
} Usuario;

int registrarUsuario(char idNuevo[]);
int existeUsuario(char id[], Usuario *usuarioBuscado);











#endif // USUARIO_H_INCLUDED
