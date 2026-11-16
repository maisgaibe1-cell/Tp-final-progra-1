#include "reportes.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void *cargarArchivo(const char *ruta, size_t tamElemento, int *cantidad)
{
    void *arreglo = NULL;
    *cantidad = 0;

    FILE *archivo = fopen(ruta, "rb");
    if (archivo != NULL)
    {
        fseek(archivo, 0, SEEK_END);
        int total = ftell(archivo) / tamElemento;
        rewind(archivo);

        if (total > 0)
        {
            arreglo = malloc(total * tamElemento);
            if (arreglo != NULL)
                *cantidad = fread(arreglo, tamElemento, total, archivo);
        }
        fclose(archivo);
    }
    return arreglo; // el que llama tiene que hacer free()
}
