#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED

#include "elector.h"

// nodo del arbol
typedef struct nodoABB{
    elector root;
    struct nodoABB *izq;
    struct nodoABB *der;
} NodoABB;

void initNodoABB(NodoABB *nodo){
    initElector(&nodo->root);
    nodo->der = NULL;
    nodo->izq = NULL;
}

NodoABB *crearNodoABB(elector E){
    NodoABB *nuevo = (NodoABB *)malloc(sizeof(NodoABB));
    if (nuevo == NULL)
    {
        printf("Error: sin memoria\n");
        return NULL;
    }
    nuevo->root = E;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

// arbol ABB
typedef struct{
    NodoABB *raiz;
} ABB;

void initABB(ABB *abb){
    abb->raiz = NULL;
}

bool vacioABB(const ABB abb){
    return (abb.raiz == NULL);
}

NodoABB* localizarABB(const ABB abb, const elector Elector, float *costo, NodoABB **padre){
    if (costo != NULL) (*costo) = 0.0f;
    if (padre != NULL) (*padre) = NULL;
    if (abb.raiz == NULL) return NULL;

    NodoABB *actual = abb.raiz;
    NodoABB *previo = NULL;

    while (actual != NULL){
        (*costo) += 1.0f;

        if (actual->root.dni == Elector.dni){ // si el valor == buscado
            (*padre) = previo;
            return actual;
        }

        previo = actual; // guardar nodo padre y avanzar
        if (actual->root.dni > Elector.dni){
            actual = actual->izq;
        }else{
            actual = actual->der;
        }
    }

    (*padre) = previo;
    return NULL;
}

bool altaABB( ABB *abb, const elector Elector, float *costo){
     (*costo) = 0.0f;
     NodoABB *nuevo = crearNodoABB( Elector );
     if( nuevo == NULL) return false;

    // si el arbol es vacio, dar alta en raiz
    if (vacioABB(*abb)) {
            abb->raiz = nuevo;
            (*costo) += 0.5;
            return true;
    }

    NodoABB *padre = NULL;
    float costoBusqueda = 0; //no se usa en esta funcion
    NodoABB *encontrado = localizarABB(*abb, Elector, &costoBusqueda, &padre);

     if (encontrado != NULL && encontrado->root.dni == Elector.dni)  {
            return false;
    }// no se da alta al elector del mismo dni

    if( padre->root.dni > Elector.dni){
        padre->izq = nuevo;
    }else{
        padre->der = nuevo;
    }
    (*costo) +=0.5;
    return true;
}

bool bajaABB(ABB *abb, const elector Elector, float *costo){
    (*costo) = 0.0f;

    // si el arbol es vacio, no se puede dar baja
    if (vacioABB(*abb)) return false;

    NodoABB *padre = NULL;
    float costoBusqueda = 0; //no se usa en esta funcion
    NodoABB *encontrado = localizarABB(*abb, Elector, &costoBusqueda, &padre);

     if ( encontrado != NULL && elector_sonIguales(encontrado->root, Elector) ){
        // caso 1: sin hijos
        // padre->encontrado => padre->null
        if( padre->der == encontrado){
            padre->der = NULL;
            (*costo)+=0.5f;
            return true
        }else{
            padre->izq = NULL;
            (*costo)+=0.5f;
            return true
        }
        // caso 2: un hijo
        // padre->encontrado => padre->rama correspondiente
        // caso 3: dos hijos
        // politica de reemplazo
     }
    // encontrado-> se baja al elector del mismo nupla

    return false;
}

bool evocarABB(ABB *abb, const elector Elector, float *costo, elector *resultado){
    (*costo) = 0.0f;

    // si el arbol es vacio
    if (abb == NULL || vacioABB(*abb)) return false;
    // sino, es arbol no vacio

    // no vacio => si es el mismo elector?
    NodoABB *padre = NULL;
    NodoABB *encontrado = localizarABB(*abb, Elector, costo, &padre);
    if (encontrado != NULL && encontrado->root.dni == Elector.dni) {
            *resultado = encontrado->root;
            return true;
    }// encontrado, exportar al <resultado>



    return false;
}
#endif // ABB_H_INCLUDED
