#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

typedef struct stUsuario {
    char idUsuario[10];
    char email[50];
    char contrasenia[20];
    char nickname[30];
} Usuario;

int registrarUsuario(void);
int existeUsuario(char id[]);











#endif // USUARIO_H_INCLUDED
