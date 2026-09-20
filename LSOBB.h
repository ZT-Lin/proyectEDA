#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED

#define LSOMAX 2000
#include "elector.h"
#include <math.h>

typedef struct{
    elector datos[LSOMAX];
    int cantidad;
}LSOBB;

void initLSOBB(LSOBB *lsobb) {
    lsobb->cantidad = 0;
    /*
    1. posicion "vacio"
    2. cantidad-1 = indice del ultimo elemento
    */
}

bool vacioLSO(const LSOBB lsobb){
    return (lsobb.cantidad == 0);
}

bool llenaLSO(const LSOBB lsobb){
    return (lsobb.cantidad >= LSOMAX);
}

int localizarLSO(const LSOBB lsobb, const elector Elector, int *costo){
    if ( costo != NULL ) (*costo) = 0;
    if ( vacioLSO(lsobb) ) return 0;//lista vacia

    int li = 0; //inclusivo
    int ls = lsobb.cantidad-1; //inclusivo
    int medio;
    int dni = getDNI(Elector);

    while(li<ls){
            medio = (li+ls)/2;
            if (costo != NULL) (*costo)++;
            if( getDNI(lsobb.datos[medio]) < dni ){
                li = medio+1;
            }else{
                ls = medio;
            }
    }

    return li;
    // retornar costo de localizacion
}

bool altaLSO(LSOBB *lsobb, const elector Elector, int *costo){
    if ( costo != NULL ) (*costo)=0;
    if ( llenaLSO(*lsobb) ) return false;
    // lista llena


    int costoBusqueda = 0; //aca no se usa
    int posicion = localizarLSO(*lsobb, Elector, &costoBusqueda);

    if ( elector_sonIguales( lsobb->datos[posicion], Elector) ) return false;
    // son iguales, no se da la alta

    // dar alta en posicion x, mover elementos para hacer lugar
    int mov = 0;
    for (mov = lsobb->cantidad; mov>posicion; mov--){
        lsobb->datos[mov] = lsobb->datos[mov-1];
        if (costo != NULL) (*costo)++;
    }
    // dar alta, aumentar cantidad almacenada
    lsobb->datos[posicion] = Elector;
    lsobb->cantidad++;
    return true;
}

bool bajaLSO(LSOBB *lsobb, const elector Elector, int *costo){
    if ( costo != NULL ) (*costo)=0;
    if ( vacioLSO(*lsobb) ) return false;

    int costoBusqueda = 0; //aca no se usa
    int posicion = localizarLSO(*lsobb, Elector, &costoBusqueda);

    if ( ! elector_sonIguales(lsobb->datos[posicion], Elector) ) return false;
    //debe ser iguales para dar de baja

    int mov=0;
    for (mov = posicion; mov < lsobb->cantidad-1; mov++){
        lsobb->datos[mov] = lsobb->datos[mov+1];
        if (costo != NULL) (*costo)++;
    }
    lsobb->cantidad--;
    return true;
}

bool evocarLSO(const LSOBB lsobb, const elector Elector, int *costo, elector *resultado){
    if( costo!=NULL) (*costo)=0;

    int costoBusqueda=0;
    int posicion = localizarLSO(lsobb, Elector, &costoBusqueda);
    if (costo != NULL) (*costo) = costoBusqueda;

    (*resultado) = lsobb.datos[posicion];
    if ( (*resultado).dni != Elector.dni ) return false;
    // segun pdf, nos da nada mas que dni, no se controla que todo sea igual
    return true;
}

#endif // LSO_H_INCLUDED
