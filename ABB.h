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
typedef struct{
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
        (*costo)+=1.0f;

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
    float costo = 0.0f;
    NodoABB *nuevo = crearNodoABB(Elector);
    if (nuevo == NULL) {return -1.0f;} //espacio insuficiente

     // arbol vacio
    if ( abb == NULL || vacioABB( *abb) ) {
        abb->raiz = nuevo;
        costo += 0.5f;
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

    costo += 0.5f;
    return costo;
}

bool bajaABB(ABB *abb, const elector Elector, float *costo){
    if(costo!=NULL) (*costo) = 0.0f;

   // si el arbol es vacio
    if ( abb == NULL || vacioABB(*abb) ) return false;
    // entonces, es arbol no vacio

    // arbol con mas de un nodo; *padre nunca devuelve NULL por localizarABB
    NodoABB *padre = NULL;
    float *costoBusqueda = (float*)malloc(sizeof(float));
    NodoABB *actual = localizarABB(abb, Elector, costoBusqueda, &padre);
    free(costoBusqueda);//aca no se usa
    if( elector_sonIguales(actual->Elector, Elector) ){// dar baja si son iguales
            // copiar el menor de los mayores
            // casos que cubre: 1 nodo(derecho) y 2 nodos
            if (actual->der != NULL) {
                NodoABB *padreMin = actual;
                NodoABB *mini = actual->der;
                costo += 1.0f;//modif puntero *2

                while (mini->izq != NULL) {//buscando
                    padreMin = mini;
                    mini = mini->izq;
                    costo += 1.0f;//modif puntero *2
                }
                //copia de datos
                elector_copiar(&actual->Elector, mini->Elector);
                costo += 1.0f;//copia dato

                if (padreMin == actual)
                    padreMin->der = mini->der;
                else
                    padreMin->izq = mini->der;

                free(mini);
                costo += 0.5f;//modif puntero
                return costo;
            }

            // copiar el mayor de los menores
            // casos que cubre: 1 nodo(izquierdo)
            // aclaracion: caso de 2 nodos esta en arriba
            if (actual->izq != NULL) {
                NodoABB *padreMax = actual;
                NodoABB *maxi = actual->izq;
                costo += 1.0f;//modif puntero*2

            while (maxi->der != NULL) {
                padreMax = maxi;
                maxi = maxi->der;
                costo += 1.0f;//modif puntero *2
            }

            elector_copiar(&actual->Elector, maxi->Elector);
            costo += 1.0f;//copia de datos

            if (padreMax == actual){
                padreMax->izq = maxi->izq;
            }else{
                padreMax->der = maxi->izq;
            }

            free(maxi);
            costo += 0.5f;
            return costo;
        }

        // no tiene hijos
        if (padre == NULL){
            abb->raiz = NULL;
        }else if (padre->izq == actual){
            padre->izq = NULL;
        }else{
            padre->der = NULL;
        }

        free(actual);
        costo += 0.5f;
        return costo;
    }

    //arbol no vacio, no encontro el mismo elector, no se da la baja
    printf("------------------------------------------------------------\n");
    printf("elector <%d> no encontrado! \n", Elector.dni);
    return costo;
}

bool evocarABB(ABB *abb, const elector Elector, float *costo){
    if(costo!=NULL) (*costo)=0;

    // si el arbol es vacio
    if ( abb == NULL || vacioABB(*abb) ) return false;
    // sino, es arbol no vacio

    // no vacio => si es el mismo elector?
    NodoABB *padre;
    NodoABB *actual = localizarABB(abb, Elector, costo, &padre);
    if( actual->Elector.dni == Elector.dni) return true;
    // encontrado

    return false;
    // no encontrado
}
#endif // ABB_H_INCLUDED
