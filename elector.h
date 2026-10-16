#ifndef ELECTOR_H_INCLUDED
#define ELECTOR_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef struct{
    int dni, cPostal, mesa, circuito;
    char nombreApellido[51];
    char domicilio[81];
}elector;

void initElector (elector *Elector){
    Elector->dni = 0;
    strcpy(Elector->nombreApellido, "indefinido");
    strcpy(Elector->domicilio, "indefinido");
    Elector->cPostal = 0;
    Elector->mesa = 0;
    Elector->circuito = 0;
}

// ============== PMI ==============
bool elector_sonIguales(const elector a, const elector b) {
    if (a.dni != b.dni) return false;
    if (a.cPostal != b.cPostal) return false;
    if (a.mesa != b.mesa) return false;
    if (a.circuito != b.circuito) return false;
    if (stricmp(a.nombreApellido, b.nombreApellido) != 0) return false;
    if (stricmp(a.domicilio, b.domicilio) != 0) return false;
    return true;
}

bool elector_copiar(elector *destino, const elector origen){
    destino->dni = origen.dni;
    strcpy(destino->nombreApellido, origen.nombreApellido);
    strcpy(destino->domicilio, origen.domicilio);
    destino->cPostal = origen.cPostal;
    destino->circuito = origen.circuito;
    destino->mesa = origen.mesa;
    return elector_sonIguales(*destino, origen);
}

void elector_mostrar( const elector aMostrar){
    printf("DNI:                 %d\n", aMostrar.dni);
    printf("Nombre y apellido:   %s\n", aMostrar.nombreApellido);
    printf("Domicilio:           %s\n", aMostrar.domicilio);
    printf("Codigo postal:       %d\n", aMostrar.cPostal);
    printf("Numero de mesa:      %d\n", aMostrar.mesa);
    printf("Numero de circuito:  %d\n", aMostrar.circuito);
}

#endif // ELECTOR_H_INCLUDED
