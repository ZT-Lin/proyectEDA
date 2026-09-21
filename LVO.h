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

float altaLVO(NodoLVO **cab, elector e, int *exito) {
    NodoLVO *anterior = NULL;
    NodoLVO *actual = *cab;

    while (actual->persona.dni < e.dni) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual->persona.dni == e.dni) {
        if (exito) *exito = 0; // DNI repetido
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
    return 0.5f; // Costo por enlazar
}

float bajaLVO(NodoLVO **cab, elector e, int *exito) {
    NodoLVO *anterior = NULL;
    NodoLVO *actual = *cab;

    while (actual->persona.dni < e.dni) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual->persona.dni != e.dni || !elector_sonIguales(actual->persona, e)) {
        if (exito) *exito = 0; // Fracaso
        return 0.0f;
    }

    if (anterior == NULL) {
        *cab = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);
    if (exito) *exito = 1;
    return 0.5f; // Costo por desenganchar
}

float evocarLVO(NodoLVO *cab, long dni, elector *encontrado, int *exito) {
    NodoLVO *act = cab;
    float costo = 0.0f;

    while (act != NULL) {
        costo += 1.0f;

        if (act->persona.dni == dni) {
            if (encontrado) *encontrado = act->persona;
            if (exito) *exito = 1;
            return costo;
        }

        if (act->persona.dni > dni) {
            break;
        }

        act = act->siguiente;
    }

    if (exito) *exito = 0; // Fracaso
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