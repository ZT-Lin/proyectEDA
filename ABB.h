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
    NodoABB *padre = abb->raiz;
    NodoABB *hijo = abb->raiz;

    while (hijo != NULL) {
        (*costo)++;

        if (dni == hijo->Elector.dni) {
            return hijo; // v == x? -> encontrado
        }

        padre = hijo;
        if (dni < hijo->Elector.dni) {
            hijo = hijo->izq; // v < x? -> - A1 menor
        } else {
            hijo = hijo->der; // v > x? -> A2 - mayor
        }
    }

    return padre;
}

float altaABB(ABB *abb, const elector Elector){
    float costo = 0.0;
    NodoABB *nuevo = crearNodoABB(Elector);
    if (nuevo == NULL) {return -1.0;} //espacio insuficiente

     // arbol vacio
    if (abb->raiz == NULL) {
        abb->raiz = nuevo;
        costo += 0.5;
        return costo;
    }

    // si el elector que me devuelve tiene mismo dni
    int costoBusqueda = 0;
    NodoABB *interno = localizarABB(abb, Elector, &costoBusqueda);
    if( interno->Elector.dni == nuevo->Elector.dni ) {
            free(nuevo);
            return -2.0;
    }

    // no es mismo dni + arbol no vacio => interno = posicion a insertar segun dni
    if (Elector.dni < interno->Elector.dni) {
        interno->izq = nuevo;
    } else {
        interno->der = nuevo;
    }

    costo += 0.5;
    return costo;
}

float bajaABB(ABB *abb, const elector Elector){}
float evocarABB(ABB *abb, const elector Elector){}
#endif // ABB_H_INCLUDED
