#ifndef LVO_H_INCLUDED
#define LVO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "elector.h"

#define VALOR_INFINITO 999999999L

typedef struct celda_padron {
    elector persona;
    struct celda_padron *siguiente;
} NodoLVO;

NodoLVO *inicializar_lvo(void) {
    NodoLVO *centinela = (NodoLVO *) malloc(sizeof(NodoLVO));
    if (centinela == NULL) return NULL;

    centinela->persona.dni = VALOR_INFINITO;
    centinela->persona.nombreApellido[0] = '\0';
    centinela->persona.domicilio[0] = '\0';
    centinela->persona.cPostal = 0;
    centinela->persona.mesa = 0;
    centinela->persona.circuito = 0;
    centinela->siguiente = NULL;

    return centinela;
}

float localizarLVO(NodoLVO *cab, long dni, int *exito, NodoLVO **ant, NodoLVO **pos) {
    float costo = 0.0f;
    *exito = 0;
    *ant = NULL;
    *pos = cab;

    while (*pos != NULL && (*pos)->persona.dni < dni) {
        costo += 1.0f;
        *ant = *pos;
        *pos = (*pos)->siguiente;
    }

    if (*pos != NULL) {
        costo += 1.0f; 
        if ((*pos)->persona.dni == dni) {
            *exito = 1;
        }
    }

    return costo;
}

float altaLVO(NodoLVO **cab, elector e, int *exito) {
    NodoLVO *anterior = NULL;
    NodoLVO *actual = NULL;
    int exitoL = 0;

    localizarLVO(*cab, e.dni, &exitoL, &anterior, &actual);

    if (exitoL) {
        if (exito) *exito = 0;
        return 0.0f;
    }

    NodoLVO *nuevo = (NodoLVO *) malloc(sizeof(NodoLVO));
    if (!nuevo) {
        if (exito) *exito = 0;
        return 0.0f;
    }

    nuevo->persona = e;
    nuevo->siguiente = actual; 

    if (anterior == NULL) {
        *cab = nuevo;           
    } else {
        anterior->siguiente = nuevo; 
    }

    if (exito) *exito = 1;
    return 1.0f; 
}

float bajaLVO(NodoLVO **cab, elector e, int *exito) {
    if (cab == NULL || *cab == NULL) {
        if (exito) *exito = 0;
        return 0.0f;
    }

    NodoLVO *anterior = NULL;
    NodoLVO *actual = NULL;
    int exitoL = 0;

    localizarLVO(*cab, e.dni, &exitoL, &anterior, &actual);

    // Si no encontro el DNI o la tupla entera no coincide
    if (!exitoL || !elector_sonIguales(actual->persona, e)) {
        if (exito) *exito = 0;
        return 0.0f;
    }

    if (anterior == NULL) {
        *cab = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente; 
    }

    free(actual);
    if (exito) *exito = 1;
    return 0.5f; 
}

float evocarLVO(NodoLVO *cab, long dni, elector *encontrado, int *exito) {
    NodoLVO *anterior = NULL;
    NodoLVO *actual = NULL;

    // Evocar devuelve el costo exacto medido por localizar
    float costo = localizarLVO(cab, dni, exito, &anterior, &actual);

    if (*exito && encontrado != NULL) {
        *encontrado = actual->persona;
    }

    return costo;
}

void vaciar_lvo(NodoLVO *cab) {
    NodoLVO *borrador;
    while (cab != NULL) {
        borrador = cab;
        cab = cab->siguiente;
        free(borrador);
    }
}

#endif
