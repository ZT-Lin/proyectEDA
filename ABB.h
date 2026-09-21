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

float localizarABB(const ABB abb, const elector Elector, bool *exito, NodoABB **posicion){
    float costo = 0.0f;
    (*exito) = false;
    NodoABB *actual = abb.raiz;
    NodoABB *previo = NULL;

    if (abb.raiz == NULL) { //arbol vacio
        (*posicion) = NULL;
        (*exito) = false;
        return costo;
    }

    while (actual != NULL){
        costo += 1.0f;

        if (actual->root.dni == Elector.dni){ // si el valor == buscado
            (*posicion) = actual;
            (*exito) = true;
            return costo;
        }

        previo = actual; // guardar nodo padre y avanzar
        if (actual->root.dni > Elector.dni){
            actual = actual->izq;
        }else{
            actual = actual->der;
        }
    }
    (*posicion) = previo;
    return costo;
}

float altaABB( ABB *abb, const elector Elector, bool *exito){
     float costo = 0.0f;
     (*exito) = false;
     NodoABB *nuevo = crearNodoABB( Elector );
     if( nuevo == NULL) return costo;

    // si el arbol es vacio, dar alta en raiz
    if (vacioABB(*abb)) {
            abb->raiz = nuevo;
            costo += 0.5;
            (*exito) = true;
            return costo;
    }

    NodoABB *posicion;
    bool exitoL;
    localizarABB(*abb, Elector, &exitoL, &posicion);

     if (exitoL)  {// encuentra un elector con mismo dni
        free(nuevo);
        (*exito) = false;
        return costo;
    }

    if (Elector.dni < posicion->root.dni) {// el posicion es el ultimo nodo
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

    // si el arbol es vacio, no se puede dar baja
    if (vacioABB(*abb)) return costo;

    bool exitoL = false;
    NodoABB *encontrado;
    localizarABB(*abb, Elector, &exitoL, &encontrado);

     if (!exitoL || !elector_sonIguales(encontrado->root, Elector)) return costo;//no encontro

     //si encontro, recorrer hasta "encontrado"
     NodoABB *padre = NULL;
     NodoABB *p = abb->raiz;
     while (p != NULL && p != encontrado) {
        padre = p;
        p = (Elector.dni < p->root.dni) ? p->izq : p->der;
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
        if (encontrado->izq != NULL || encontrado->der != NULL) {
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
        costo+= 1.0f;

        // eliminar menor y sus hijos
        if (padreMin == encontrado){
                padreMin->der = menor->der;
        }else{
            padreMin->izq = menor->der;
        }// modificacion punteor en arbol
        costo+= 0.5f;

        free(menor);
        (*exito) = true;
        return costo;
        // encontrado-> se baja al elector del mismo nupla

    return false;//no encontrado
}

float evocarABB(ABB *abb, const elector Elector, bool *exito, elector *resultado){
    float costo = 0.0f;
    initElector(resultado);
    (*exito) = false;

    // si el arbol es vacio
    if (abb == NULL || vacioABB(*abb)) return costo;

    // sino, es arbol no vacio
    // no vacio => si es el mismo elector?;
    NodoABB *encontrado;
    costo += localizarABB(*abb, Elector, exito, &encontrado);

    if (*exito) {
            *resultado = encontrado->root;
            costo+=1.0f;// consultar al nodo encontrado
            return costo;
    }// encontrado, exportar al <resultado>
    return costo;
}

//==========funcion auxiliar==========
int contarNodosABB(NodoABB *nodo){
    if (nodo == NULL) return 0;
    return 1 + contarNodosABB(nodo->izq) + contarNodosABB(nodo->der);
}
#endif // ABB_H_INCLUDED
