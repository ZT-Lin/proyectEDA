#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED

#include "elector.h"

// nodo del arbol
typedef struct nodoABB{
    elector Elector;
    struct nodoABB *izq;
    struct nodoABB *der;
} NodoABB;

void initNodoABB(NodoABB *nodo){
    inicializarElector( &nodo->Elector );
    nodo->der = NULL;
    nodo->izq = NULL;
}

NodoABB* crearNodoABB(elector E){
        NodoABB *nuevo = (NodoABB *) malloc(sizeof(NodoABB));
        if(nuevo == NULL) {
            printf("Error: sin memoria\n");
            return NULL;
        }
        nuevo->Elector = E;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        return nuevo;
}

// arbol ABB
typedef struct abb{
    NodoABB *raiz;
} ABB;

void initABB(ABB *abb){
    abb->raiz = NULL;
}

bool vacioABB(const ABB abb){
    return (abb.raiz == NULL);
}

NodoABB* localizarABB(const ABB *abb, const elector Elector, int *costo) {
    (*costo)=0;
    if (abb == NULL || abb->raiz == NULL) {
        return NULL;
    }

    int dni = Elector.dni;
    NodoABB *actual = abb->raiz;

    while (actual != NULL) {
        (*costo)++;

        if (dni == actual->Elector.dni) {
            return actual; // v == x? -> encontrado
        } else if (dni < actual->Elector.dni) {
            actual = actual->izq; // v < x? -> - A1 menor
        } else {
            actual = actual->der; // v > x? -> A2 - mayor
        }
    }

    return NULL;
}

#endif // ABB_H_INCLUDED
