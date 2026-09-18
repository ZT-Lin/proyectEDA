#ifndef ELECTOR_H_INCLUDED
#define ELECTOR_H_INCLUDED

#include <stdio.h>
#include <string.h>


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

// ============ GETTERS ============
int getDNI( const elector Elector) {
    return Elector.dni;
}

int getCPostal( const elector Elector) {
    return Elector.cPostal;
}

int getMesa( const elector Elector) {
    return Elector.mesa;
}

int getCircuito( const elector Elector) {
    return Elector.circuito;
}

char* getNombreApellido( const elector Elector) {
    return Elector.nombreApellido;
}

char* getDomicilio( const elector Elector) {
    return Elector.domicilio;
}

// ============ SETTERS ============
void setDNI(elector *Elector, const int dni) {
    Elector->dni = dni;
}

void setCPostal(elector *Elector, const int cPostal) {
    Elector->cPostal = cPostal;
}

void setMesa(elector *Elector, const int mesa) {
    Elector->mesa = mesa;
}

void setCircuito(elector *Elector, const int circuito) {
    Elector->circuito = circuito;
}

void setNombreApellido(elector *Elector, const char *nombre) {
    strcpy(Elector->nombreApellido, nombre);
}

void setDomicilio(elector *Elector, const char *domicilio) {
    strcpy(Elector->domicilio, domicilio);
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


#endif // ELECTOR_H_INCLUDED
