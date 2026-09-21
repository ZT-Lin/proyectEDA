/*Alts o Lin agrega esto en el .main que vayamos a usar
NodoLVO *lista_lvo = crearLVO();
Costos costos_lvo = {0};
Eso en el main
Esto en el pre load
case 1 altaLVO(lvo, e_temp, &cLVO->costoAlta);
case 2 bajaLVO(lvo, e_temp, &cLVO->costoBaja);
case 3:
Elector res;
consultarLVO(*lvo, e_temp.dni, &res, &cLVO->costoConsultas);

case 0 liberarLVO(lista_lvo);
.
*/


#ifndef LVO_H_INCLUDED
#define LVO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int insertar_en_lvo(NodoLVO **cab, elector e, double *costo_operacion) {
    NodoLVO *anterior = NULL;
    NodoLVO *actual = *cab;

    while (actual->persona.dni < e.dni) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual->persona.dni == e.dni) {
        return 0; // ya registrado
    }

    NodoLVO *item = (NodoLVO *) malloc(sizeof(NodoLVO));
    if (!item) return 0;

    item->persona = e;
    item->siguiente = actual;

    if (anterior == NULL) {
        *cab = item;
    } else {
        anterior->siguiente = item;
    }

    *costo_operacion += 0.5;
    return 1;
}

int eliminar_de_lvo(NodoLVO **cab, elector e, double *costo_operacion) {
    NodoLVO *anterior = NULL;
    NodoLVO *actual = *cab;

    while (actual->persona.dni < e.dni) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual->persona.dni != e.dni || !elector_sonIguales(actual->persona, e)) {
        return 0;
    }

    if (anterior == NULL) {
        *cab = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    *costo_operacion += 0.5;
    free(actual);
    return 1;
}

int buscar_en_lvo(NodoLVO *cab, long dni, elector *encontrado, double *costo_evocacion) {
    NodoLVO *recorrer = cab;
    int ok = 0;

    while (recorrer != NULL) {
        *costo_evocacion += 1.0;

        if (recorrer->persona.dni == dni) {
            *encontrado = recorrer->persona;
            ok = 1;
            break;
        }

        if (recorrer->persona.dni > dni) {
            break;
        }

        recorrer = recorrer->siguiente;
    }

    return ok;
}

void mostrar_lista_lvo(NodoLVO *cab) {
    NodoLVO *aux = cab;
    int electores = 0;

    printf("\n--- Padron Electoral - LVO ---\n");
    while (aux != NULL && aux->persona.dni != VALOR_INFINITO) {
        imprimirElector(&(aux->persona));
        aux = aux->siguiente;
        electores++;
    }
    printf("Total de registros mostrados: %d\n", electores);
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
