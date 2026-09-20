/*Alts o Lin agrega esto en el main que vayamos a usar
NodoABB *arbol_abb = NULL;
Costos costos_abb = {0};

Case 1: insertarABB(abb, e_temp, &cABB->costoAlta); 
Case 2: bajaABB(abb, e_temp, &cABB->costoBaja);
Case 3:
Elector res;
consultarABB(*abb, e_temp.dni, &res, &cABB->costoConsultas);

En el case 3 del menurdobich
case '3': {
    mostrarABB(arbol_abb);
    enter();
    break;
}

y al salir poner liberarABB(arbol_abb); para liberar anashe

.

*/


#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "elector.h"

// Estructura para el arbol de electores
typedef struct nodo_arbol {
    Elector dato;
    struct nodo_arbol *sub_izq;
    struct nodo_arbol *sub_der;
} NodoABB;

// Alta en el arbol ordenada por DNI
int insertarABB(NodoABB **raiz, Elector elect, double *costo) {
    if (*raiz == NULL) {
        NodoABB *nuevo = (NodoABB *) malloc(sizeof(NodoABB));
        if (!nuevo) return 0;

        nuevo->dato = elect;
        nuevo->sub_izq = NULL;
        nuevo->sub_der = NULL;
        
        *raiz = nuevo;
        *costo += 0.5; // puntero enlazado
        return 1;
    }

    if (elect.dni == (*raiz)->dato.dni) {
        return 0; // dni repetido
    }

    if (elect.dni < (*raiz)->dato.dni) {
        return insertarABB(&((*raiz)->sub_izq), elect, costo);
    } else {
        return insertarABB(&((*raiz)->sub_der), elect, costo);
    }
}

// Baja con reemplazo por menor de los mayores
int bajaABB(NodoABB **raiz, Elector elect, double *costo) {
    if (*raiz == NULL) {
        return 0;
    }

    if (elect.dni < (*raiz)->dato.dni) {
        return bajaABB(&((*raiz)->sub_izq), elect, costo);
    } else if (elect.dni > (*raiz)->dato.dni) {
        return bajaABB(&((*raiz)->sub_der), elect, costo);
    }

    // DNI encontrado, validar todos los campos del elector
    if (!mismoElector(&((*raiz)->dato), &elect)) {
        return 0;
    }

    NodoABB *nodo_elim = *raiz;

    // Caso 1: hoja
    if ((*raiz)->sub_izq == NULL && (*raiz)->sub_der == NULL) {
        *raiz = NULL;
        *costo += 0.5;
        free(nodo_elim);
        return 1;
    }

    // Caso 2: un solo hijo
    if ((*raiz)->sub_izq == NULL) {
        *raiz = (*raiz)->sub_der;
        *costo += 0.5;
        free(nodo_elim);
        return 1;
    }
    if ((*raiz)->sub_der == NULL) {
        *raiz = (*raiz)->sub_izq;
        *costo += 0.5;
        free(nodo_elim);
        return 1;
    }

    // Caso 3: dos hijos, busca al sucesor
    NodoABB *p_padre = *raiz;
    NodoABB *sucesor = (*raiz)->sub_der;

    while (sucesor->sub_izq != NULL) {
        p_padre = sucesor;
        sucesor = sucesor->sub_izq;
    }

    // Copiamos datos (costo 1)
    (*raiz)->dato = sucesor->dato;
    *costo += 1.0;

    // Desenganche del sucesor (costo 0.5)
    if (p_padre == *raiz) {
        p_padre->sub_der = sucesor->sub_der;
    } else {
        p_padre->sub_izq = sucesor->sub_der;
    }
    *costo += 0.5;

    free(sucesor);
    return 1;
}

// Busqueda / evocacion por clave DNI
int consultarABB(NodoABB *raiz, long dni_buscado, Elector *encontrado, double *costo) {
    NodoABB *p_act = raiz;

    while (p_act != NULL) {
        *costo += 1.0;

        if (p_act->dato.dni == dni_buscado) {
            *encontrado = p_act->dato;
            return 1;
        }

        if (dni_buscado < p_act->dato.dni) {
            p_act = p_act->sub_izq;
        } else {
            p_act = p_act->sub_der;
        }
    }

    return 0;
}

// Barrido preorden detallando hijos
void barridoPreordenABB(NodoABB *raiz, int *cant) {
    if (raiz == NULL) return;

    imprimirElector(&(raiz->dato));
    (*cant)++;

    if (raiz->sub_izq == NULL && raiz->sub_der == NULL) {
        printf("      -> Sin hijos.\n");
    } else {
        if (raiz->sub_izq != NULL) {
            printf("      -> Hijo izq: DNI %ld\n", raiz->sub_izq->dato.dni);
        } else {
            printf("      -> Sin hijo izquierdo.\n");
        }

        if (raiz->sub_der != NULL) {
            printf("      -> Hijo der: DNI %ld\n", raiz->sub_der->dato.dni);
        } else {
            printf("      -> Sin hijo derecho.\n");
        }
    }

    barridoPreordenABB(raiz->sub_izq, cant);
    barridoPreordenABB(raiz->sub_der, cant);
}

void mostrarABB(NodoABB *raiz) {
    int total_elect = 0;
    printf("\n--- Padron - Arbol Binario de Busqueda (ABB) - Barrido Preorden ---\n");
    barridoPreordenABB(raiz, &total_elect);
    printf("Total de electores en ABB: %d\n", total_elect);
}

// Liberar memoria del arbol
void destruirABB(NodoABB *raiz) {
    if (raiz == NULL) return;
    destruirABB(raiz->sub_izq);
    destruirABB(raiz->sub_der);
    free(raiz);
}

#endif