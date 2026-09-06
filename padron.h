#ifndef PADRON_H_INCLUDED
#define PADRON_H_INCLUDED

#include <stdio.h>
#include <string.h>


typedef struct{
    int DNI, cPostal, mesa, circuito;
    char nombreApellido[51];
    char domicilio[81];
}padron;

void inicializarP (padron *P){
    P->DNI = 0;
    strcpy(P->nombreApellido, "indefinido");
    strcpy(P->domicilio, "indefinido");
    P->cPostal = 0;
    P->mesa = 0;
    P->circuito = 0;
}

// ============ GETTERS ============
int getDNI( const padron *P) {
    return P->DNI;
}

int getCPostal( const padron *P) {
    return P->cPostal;
}

int getMesa( const padron *P) {
    return P->mesa;
}

int getCircuito( const padron *P) {
    return P->circuito;
}

char* getNombreApellido( const padron *P) {
    return P->nombreApellido;
}

char* getDomicilio( const padron *P) {
    return P->domicilio;
}

// ============ SETTERS ============
void setDNI(padron *P, int dni) {
    P->DNI = dni;
}

void setCPostal(padron *P, int cPostal) {
    P->cPostal = cPostal;
}

void setMesa(padron *P, int mesa) {
    P->mesa = mesa;
}

void setCircuito(padron *P, int circuito) {
    P->circuito = circuito;
}

void setNombreApellido(padron *P,  char *nombre) {
    strcpy(P->nombreApellido, nombre);
}

void setDomicilio(padron *P,  char *domicilio) {
    strcpy(P->domicilio, domicilio);
}


#endif // PADRON_H_INCLUDED
