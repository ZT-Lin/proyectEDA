#ifndef PADRON_H_INCLUDED
#define PADRON_H_INCLUDED

#include <stdio.h>
#include <string.h>


typedef struct{
    int dni, cPostal, mesa, circuito;
    char nombreApellido[51];
    char domicilio[81];
}padron;

void inicializarP (padron *P){
    P->dni = 0;
    strcpy(P->nombreApellido, "indefinido");
    strcpy(P->domicilio, "indefinido");
    P->cPostal = 0;
    P->mesa = 0;
    P->circuito = 0;
}

// ============ GETTERS ============
int getDNI( const padron P) {
    return P->dni;
}

int getCPostal( const padron P) {
    return P->cPostal;
}

int getMesa( const padron P) {
    return P->mesa;
}

int getCircuito( const padron P) {
    return P->circuito;
}

char* getNombreApellido( const padron P) {
    return P->nombreApellido;
}

char* getDomicilio( const padron P) {
    return P->domicilio;
}

// ============ SETTERS ============
void setDNI(padron *P, const int dni) {
    P->dni = dni;
}

void setCPostal(padron *P, const int cPostal) {
    P->cPostal = cPostal;
}

void setMesa(padron *P, const int mesa) {
    P->mesa = mesa;
}

void setCircuito(padron *P, const int circuito) {
    P->circuito = circuito;
}

void setNombreApellido(padron *P, const char *nombre) {
    strcpy(P->nombreApellido, nombre);
}

void setDomicilio(padron *P, const char *domicilio) {
    strcpy(P->domicilio, domicilio);
}

// ============== PMI ==============
bool padron_sonIguales(const padron *a, const padron *b) {
    if (a->dni != b->dni) return false;
    if (a->cPostal != b->cPostal) return false;
    if (a->mesa != b->mesa) return false;
    if (a->circuito != b->circuito) return false;
    if (stricmp(a->nombreApellido, b->nombreApellido) != 0) return false;
    if (stricmp(a->domicilio, b->domicilio) != 0) return false;
    return true;
}

#endif // PADRON_H_INCLUDED
