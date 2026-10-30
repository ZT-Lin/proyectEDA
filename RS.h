#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funcionHashing.h"
#include "elector.h"
#include "RA.h"

#define MRS 1237



typedef struct NodoRS {
    elector datos;
    struct NodoRS *sig;
} NodoRS;

typedef NodoRS* RS;

/* Inicializacion de la cabecera: asigna NULL a cada puntero del arreglo */
void initRS(RS tabla[], int M){
    for (int i = 0; i < M; i++){
        tabla[i] = NULL;
    }
}


int localizarRS(const RS tabla[], const elector e, int inicial, NodoRS **ant, NodoRS **act, bool *exito){
    (*exito) = false;
    int actual = inicial % MRS;
    (*ant) = NULL;
    (*act) = tabla[actual];

    int costoLocalizar = 1; // 1 acceso a la cabecera de la tabla

    while ((*act) != NULL) {
        costoLocalizar++; // +1 por cada nodo recorrido e inspeccionado
        if ((*act)->datos.dni == e.dni) {
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

    if (exitoL) return costoAlta; // Elemento repetido

    NodoRS *nuevo = (NodoRS *)malloc(sizeof(NodoRS));
    if (nuevo == NULL) return costoAlta; // Falla en la reserva de memoria

    // Primitiva del TAD elector para transferir la informacion
    elector_copiar(&nuevo->datos, e);

    // Insercion al frente de la lista con indexacion acotada
    int posSegura = inicial % MRS;
    nuevo->sig = tabla[posSegura];
    tabla[posSegura] = nuevo;
    (*exito) = true;

    return costoAlta;
}

int bajaRS(RS tabla[], const elector e, bool *exito){
    (*exito) = false;
    NodoRS *ant = NULL, *act = NULL;
    bool exitoL = false;
    int inicial = hashing(e.dni, MRS);
    int costoBaja = localizarRS(tabla, e, inicial, &ant, &act, &exitoL);

    if (exitoL) {
        costoBaja++; // Acceso a la nupla completa para confirmacion por codigo
        if (elector_sonIguales(act->datos, e)) {
            int posSegura = inicial % MRS;
            if (ant == NULL) {
                tabla[posSegura] = act->sig;
            } else {
                ant->sig = act->sig;
            }
            free(act); // Liberacion segura del nodo
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
    int contadorPaginacion = 0;

    for (int i = 0; i < M; i++) {
        printf("------------------------------------------------------------\n");
        if (tabla[i] == NULL) {
            printf("[%d] Lista VACIA\n", i + 1);
        } else {
            ocupadas++;
            printf("[%d] Lista OCUPADA:\n", i + 1);
            NodoRS *act = tabla[i];
            int n = 1;
            while (act != NULL) {
                total++;
                printf("  -> Elemento #%d:\n", n++);
                elector_mostrar(act->datos);
                act = act->sig;
            }
        }

        contadorPaginacion++;
        if (contadorPaginacion == ITEMPORPAGINA) {
            contadorPaginacion = 0;
            printf("------------------------------------------------------------\n");
            printf("  Enter = seguir    q = salir\n  usuario ->\t");
            int c = getchar();
            if (c == 'q' || c == 'Q') {
                while (getchar() != '\n');
                printf("  ... cancelado\n");
                break;
            }
            while (c != '\n' && c != EOF) c = getchar();
            system("cls");
        }
    }
    printf("============================================================\n");
    printf(" Total: %d electores registrados en %d listas activas.\n", total, ocupadas);
    printf("============================================================\n");
}

/*
 * Liberacion de memoria dinamica de RS:
 * Recorre las M listas enlazadas liberando cada nodo y resetea los punteros a NULL.
 */
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

#endif // RS_H_INCLUDED
