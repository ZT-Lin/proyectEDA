#ifndef PADRON_H_INCLUDED
#define PADRON_H_INCLUDED

#include <nombreApellido.h>

typedef struct{
    int DNI, cPostal, mesa, circuito;
    char nombreApellido[51];
    char domicilio[81];
}padron;


#endif // PADRON_H_INCLUDED
