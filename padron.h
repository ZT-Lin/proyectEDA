#ifndef PADRON_H_INCLUDED
#define PADRON_H_INCLUDED

#include <nombreApellido.h>

typedef struct{
    int DNI, mesa, circuito;
    fullName nombreApellido;
    char domicilio[80], codPostal[8];
}padron;


#endif // PADRON_H_INCLUDED
