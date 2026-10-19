#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funcionHashing.h"
#include "elector.h" 

// N = 2000, factor de carga = 1.61 -> M = 2000 / 1.61 = 1242.23
// El primo mas cercano es 1237 (chequeado con la tabla de primos para no pifiarle)
#define MRS 1237

typedef struct NodoRS {
    elector datos;
    struct NodoRS *sig;
} NodoRS;

typedef NodoRS* RS;

void initRS(RS tabla[], int M){
    for(int i = 0; i < M; i++){
        tabla[i] = NULL;
    }
}

int localizarRS(const RS tabla[], const elector e, int inicial, NodoRS **ant, NodoRS **act, bool *exito){
    (*exito) = false;
    int actual = inicial % MRS;
    (*ant) = NULL;
    (*act) = tabla[actual];

    // consulta el puntero en la cabecera tabla[inicial % MRS] ya suma 1 acceso
    int costoLocalizar = 1;

    // se saltea de nodo en nodo por la lista enlazada hasta encontrar el DNI o llegar a NULL
    while((*act) != NULL){
        costoLocalizar++; // +1 por cada nodo recorrido en la lista enlazada
        if((*act)->datos.dni == e.dni){
            (*exito) = true;
            return costoLocalizar;
        }
        (*ant) = (*act);
        (*act) = (*act)->sig;
    }

    return costoLocalizar;
}

int altaRS(RS tabla[], const elector e, bool *exito){
    (*exito) = false;
    NodoRS *ant = NULL, *act = NULL;
    bool exitoL = false;
    int inicial = hashing(e.dni, MRS);
    int costoAlta = localizarRS(tabla, e, inicial, &ant, &act, &exitoL);

    if(exitoL) return costoAlta;

    NodoRS *nuevo = (NodoRS *)malloc(sizeof(NodoRS));
    if(nuevo == NULL) return costoAlta; // por si nos quedamos sin memoria en el heap

    // se susa la primitiva del TAD elector para copiar los datos al nodo
    elector_copiar(&nuevo->datos, e);

    // inserta al inicio de la lista en O(1)
    nuevo->sig = tabla[inicial];
    tabla[inicial] = nuevo;
    (*exito) = true;

    return costoAlta;
}

int bajaRS(RS tabla[], const elector e, bool *exito){
    (*exito) = false;
    NodoRS *ant = NULL, *act = NULL;
    bool exitoL = false;
    int inicial = hashing(e.dni, MRS);
    int costoBaja = localizarRS(tabla, e, inicial, &ant, &act, &exitoL);

    if(exitoL){
        // si localiza el DNI, se suma +1 por acceder a la nupla completa para verificar ==
        elector guardado = act->datos;
        costoBaja++;
        if(elector_sonIguales(guardado, e)){
            if(ant == NULL){
                // era el primero de la lista, movemos la cabecera al siguiente
                tabla[inicial] = act->sig;
            } else {
                // estaba en el medio o al final, puenteamos con el anterior
                ant->sig = act->sig;
            }
            free(act); // libera el nodo para no dejar memory leaks
            (*exito) = true;
            return costoBaja;
        }
    }
    return costoBaja;
}

int evocarRS(const RS tabla[], const elector e, bool *exito, elector *resultado){
    *exito = false;
    NodoRS *ant = NULL;
    NodoRS *act = NULL;
    int pos = hashing(e.dni, MRS);
    int costo = localizarRS(tabla, e, pos, &ant, &act, exito);

    if (*exito) {
        elector_copiar(resultado, act->datos);
    }
    return costo;
}

void mostrarRS(const RS tabla[], int M){
    int ocupadas = 0;
    int total = 0;

    for (int i = 0; i < M; i++) {
        if (tabla[i] == NULL) {
            printf("[%d] Vacia\n", i + 1);
        } else {
            ocupadas++;
            printf("[%d]:\n", i + 1);
            NodoRS *act = tabla[i];
            int n = 1;
            while (act != NULL) {
                total++;
                printf("  Nodo %d: ", n++);
                elector_mostrar(act->datos);
                act = act->sig;
            }
        }

        if ((i + 1) % 10 == 0 && (i + 1) < M) {
            printf("-- Pausa (Enter continuar, 's' salir) --");
            int c = getchar();
            if (c == 's' || c == 'S') {
                while (getchar() != '\n');
                break;
            }
            if (c != '\n') {
                while (getchar() != '\n');
            }
        }
    }
    printf("Total: %d electores en %d listas.\n", total, ocupadas);
}

void liberarRS(RS tabla[], int M){
    for (int i = 0; i < M; i++) {
        NodoRS *act = tabla[i];
        while (act != NULL) {
            NodoRS *aux = act;
            act = act->sig;
            free(aux);
        }
        tabla[i] = NULL;
    }
}

#endif
