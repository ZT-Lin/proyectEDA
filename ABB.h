#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED

#include <stdlib.h>
#include "elector.h"
#include <stdbool.h>

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

float localizarABB(const ABB abb, const elector Elector, bool *exito, NodoABB **posicion, NodoABB **padre){
    float costo = 0.0f;
    *exito = false;
    *posicion = NULL;
    *padre = NULL;
    NodoABB *actual = abb.raiz;

    if (abb.raiz == NULL) { //arbol vacio
        return costo;
    }

    while (actual != NULL){
        costo += 1.0f;

        if (actual->root.dni == Elector.dni){ // si el valor == buscado
            (*posicion) = actual;
            (*exito) = true;
            return costo;
        }

        *padre = actual; // guardar nodo padre y avanzar
        if (actual->root.dni > Elector.dni){
            actual = actual->izq;
        }else{
            actual = actual->der;
        }
    }
    *posicion = *padre;
    return costo;
}

float altaABB( ABB *abb, const elector Elector, bool *exito){
     float costo = 0.0f;
     (*exito) = false;
     NodoABB *nuevo = crearNodoABB( Elector );
     if( nuevo == NULL) return costo;

    if ( abb->raiz==NULL || abb==NULL) {
            abb->raiz = nuevo;
            costo += 0.5f;
            (*exito) = true;
            return costo;
    }

    NodoABB *posicion = NULL;
    NodoABB *padre = NULL;
    bool exitoL = false;
    localizarABB(*abb, Elector, &exitoL, &posicion, &padre); // solo para ubicar, no suma costo

     if (exitoL) {
        free(nuevo);
        (*exito) = false;
        return 0.0f; // fracaso: no se modifico ningun puntero
    }

    if (Elector.dni < posicion->root.dni) {
        posicion->izq = nuevo;
    } else {
        posicion->der = nuevo;
    }

    costo += 0.5f;
    (*exito) = true;
    return costo;
}

float bajaABB(ABB *abb, const elector Elector, bool *exito){
    (*exito)=false;
    float costo= 0.0f;

    if (abb->raiz==NULL || abb==NULL) return costo;

    bool exitoL = false;
    NodoABB *encontrado = NULL;
    NodoABB *padre = NULL;

    // Obtiene encontrado Y padre en la misma bajada de localizarABB:
    localizarABB(*abb, Elector, &exitoL, &encontrado, &padre);

    if (!exitoL || !elector_sonIguales(encontrado->root, Elector)) {
        *exito = false;
        return 0.0f;
    }

        // caso 1: sin hijos
        // padre->encontrado => padre->null
        if (encontrado->izq == NULL && encontrado->der == NULL) {
            if (padre == NULL){
                    (abb->raiz) = NULL;              // eliminar la raiz
            }else if (padre->izq == encontrado){
                padre->izq = NULL;
            }else{
                padre->der = NULL;
            }//modificar puntero en arbol
            costo+= 0.5f;
            free(encontrado);
            (*exito) = true;
            return costo;
        }
        // caso 2: un hijo
        // padre->encontrado => padre->rama correspondiente
        if (encontrado->izq == NULL || encontrado->der == NULL) {
            NodoABB *hijo = (encontrado->izq != NULL) ? encontrado->izq : encontrado->der;
            if (padre == NULL){
                    abb->raiz = hijo;
            }else if (padre->izq == encontrado){
                padre->izq = hijo;
            }else{
                padre->der = hijo;
            }// modificacion de puntero en arbol
            costo+= 0.5f;
            free(encontrado);
            (*exito) = true;
            return costo;
        }
        // caso 3: dos hijos
        // politica de reemplazo
        NodoABB *padreMin = encontrado;
        NodoABB *menor = encontrado->der;
        //modificacion de puntero externo del arbol

        while (menor->izq != NULL) {
            padreMin = menor;
            menor = menor->izq;
            //modificacion de puntero externo del arbol
        }

        // copia de datos
        elector_copiar(&encontrado->root, menor->root);

        if (padreMin == encontrado){
            padreMin->der = menor->der;
        } else {
            padreMin->izq = menor->der;
        }

        free(menor);
        *exito = true;
        return 1.5f;
        // encontrado-> se baja al elector del mismo nupla
}

float evocarABB(ABB *abb, const elector Elector, bool *exito, elector *resultado){
    initElector(resultado);
    *exito = false;
    if (abb == NULL || abb->raiz == NULL) return 0.0f;

    NodoABB *encontrado = NULL;
    NodoABB *padre = NULL;
    float costo = localizarABB(*abb, Elector, exito, &encontrado, &padre);

    if (*exito && encontrado != NULL) {
        *resultado = encontrado->root;
    }
    return costo;
}

//==========funcion auxiliar==========
int contarNodosABB(NodoABB *nodo){
    if (nodo == NULL) return 0;
    return 1 + contarNodosABB(nodo->izq) + contarNodosABB(nodo->der);
}
#endif // ABB_H_INCLUDED
