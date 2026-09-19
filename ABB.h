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
    initElector( &nodo->Elector );
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

NodoABB* localizarABB(const ABB *abb, const elector Elector, float *costo, NodoABB **padre) {
    if (abb == NULL || vacioABB(*abb)) {
        return NULL;
    }

    int dni = Elector.dni;
    *padre = NULL;
    NodoABB *hijo = abb->raiz;

    while (hijo != NULL) {
        (*costo)+=1.0;

        if (dni == hijo->Elector.dni) {
            return hijo; // v == x? -> encontrado
        }

        *padre = hijo;
        if (dni < hijo->Elector.dni) {
            hijo = hijo->izq; // v < x? ->  A1 - menor
        } else {
            hijo = hijo->der; // v > x? -> A2 - mayor
        }
    }

    return *padre;
}

float altaABB(ABB *abb, const elector Elector){
    float costo = 0.0;
    NodoABB *nuevo = crearNodoABB(Elector);
    if (nuevo == NULL) {return -1.0;} //espacio insuficiente

     // arbol vacio
    if ( abb == NULL || vacioABB( *abb) ) {
        abb->raiz = nuevo;
        costo += 0.5;
        return costo;
    }

    // si el elector que me devuelve tiene mismo dni
    float costoBusqueda = 0;
    NodoABB *padre;
    NodoABB *interno = localizarABB(abb, Elector, &costoBusqueda, &padre);
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

float bajaABB(ABB *abb, const elector Elector){
    float costo = 0.0;

   // si el arbol es vacio
    if ( abb == NULL || vacioABB(*abb) ) {
            printf("------------------------------------------------------------\n");
            printf("elector <%d> no encontrado! \n", Elector.dni);
            return costo;
    }// entonces, es arbol no vacio

    // arbol con mas de un nodo; *padre nunca devuelve NULL por localizarABB
    NodoABB *padre = NULL;
    NodoABB *actual = localizarABB(abb, Elector, &costo, &padre);
    if( elector_sonIguales(actual->Elector, Elector) ){// dar baja si son iguales
        //caso 1: padre -> actual (sin hijos)
        //entonces: padre -> null
        if (actual->izq == NULL && actual->der == NULL) {
            if (padre == NULL) {
                abb->raiz = NULL;
            } else if (padre->izq == actual) {
                padre->izq = NULL;
            } else {
                padre->der = NULL;
            }
            free(actual);
            costo += 0.5;
            return costo;
        }// if falla -> mas de 0 hijo =>caso 2 o caso 3
        //caso 2: padre -> actual ( un solo hijo)
        //entonces: padre -> hijo
        if (actual->izq == NULL) {
            if (padre == NULL) {
                abb->raiz = actual->der;
            } else if (padre->izq == actual) {
                padre->izq = actual->der;
            } else {
                padre->der = actual->der;
            }
            free(actual);
            costo += 0.5;
            return costo;
        }
        //case 3:

    }

    //arbol no vacio, no encontro el mismo elector, no se da la baja
    printf("------------------------------------------------------------\n");
    printf("elector <%d> no encontrado! \n", Elector.dni);
    return costo;
}

float evocarABB(ABB *abb, const elector Elector){
    float costo = 0.0;

    // si el arbol es vacio
    if ( abb == NULL || vacioABB(*abb) ) {
            printf("------------------------------------------------------------\n");
            printf("elector <%d> no encontrado! \n", Elector.dni);
            return costo;
    }// entonces, es arbol no vacio


    // no vacio => si es el mismo elector?
    NodoABB *padre;
    NodoABB *actual = localizarABB(abb, Elector, &costo, &padre);
    if( elector_sonIguales(actual->Elector, Elector) ){
        elector e_temp = actual->Elector;
        printf("------------------------------------------------------------\n");
        printf("DNI:\t%d\n",e_temp.dni);
        printf("Nombre:\t%s\n",e_temp.nombreApellido);
        printf("Domicilio:\t%s\n",e_temp.domicilio);
        printf("Codigo Postal:\t %d\n",e_temp.cPostal);
        printf("Mesa de votacion: %d\n",e_temp.mesa);
        printf("Circuito:\t%d\n",e_temp.circuito);
        if (actual->izq != NULL){
            printf("hijo izquierdo: %d\n", actual->izq->Elector.dni);
        }else{
            printf("hijo izquierdo: no tiene\n");
        }

        if (actual->der != NULL){
            printf("hijo derecho: %d\n", actual->der->Elector.dni);
        }else{
            printf("hijo derecho: no tiene\n");
        }
        return costo;
    }

    printf("------------------------------------------------------------\n");
    printf("elector <%d> no encontrado! \n", Elector.dni);
    return costo;
}
#endif // ABB_H_INCLUDED
