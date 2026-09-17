#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED

#define LSOMAX 2000
#include "padron.h"
#include <math.h>

typedef struct{
    padron datos[LSOMAX];
    int cantidad = 0;
}LSOBB;

void LSOBB_inicializar(LSOBB *lista) {
    lista->cantidad = 0;
}

int vaciaLSO(LSOBB l){
    return (l.cantidad == 0);
}

int llenaLSO(LSOBB l){
    return (l.cantidad > LSOMAX);
}

int localizarLSO(LSOBB l, const padron p){
    int li = 0; //inclusivo
    int ls = l.cantidad; //inclusivo
    int medio = 0;

    while(li<ls){
            medio = (li+ls)/2;
            if( getDNI(l.datos[medio]) < getDNI(p) ){
                li = medio+1;
            }else{
                ls = medio-1;
            }
    }

    if ( getDNI(l.datos[medio]) == getDNI(p) ){
        return medio;
    }else{
        return -1; // no encontrado
    }
}

int altaLSO(LSOBB *l, const padron elector){
    if ( llenaLSO(*l) ) { return -1;} // lista llena

    int posicion = localizarLSO(*l,elector);
    if (posicion == -1){ return -1;} //no encontrado

    //dar alta en posicion x

    int fin = l->cantidad;
    int costo = 0;
    while (posicion < fin){
        l->datos[fin+1] = l->datos[fin];
        costo+1;
    }
    l->datos[posicion] = elector;
    return costo;
}

int bajaLSO(LSOBB *l, const padron elector){
    if ( llenaLSO(*l) ) { return -1;} // lista llena

    int posicion = localizarLSO(*l,elector);
    if (posicion == -1){ return -1;} //no encontrado

    //dar alta en posicion x

    int fin = l->cantidad;
    int costo = 0;
    while (posicion <= fin){
        l->datos[fin+1] = l->datos[fin];
        costo+1;
    }
    return costo;
}


#endif // LSO_H_INCLUDED
