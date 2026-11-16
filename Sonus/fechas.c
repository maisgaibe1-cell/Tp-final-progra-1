#include "fechas.h"
#include "time.h"

int anioActual(void)
{
    time_t segundos = time(NULL);               // segundos desde 1970
    struct tm *fecha = localtime(&segundos);    // los convierte a día/mes/año/etc.
    int anio = fecha->tm_year + 1900;           // tm_year cuenta desde 1900

    return anio;
}
