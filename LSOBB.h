#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED

#define LSOMAX 2000
#include "padron.h"
#include <math.h>

typedef struct{
    padron datos[LSOMAX];
    int cantidad = 0;
}LSOBB;

void LSOBB_inicializar(LSOBB *lsobb) {
    lsobb->cantidad = 0;
}

int vaciaLSO(const LSOBB lsobb){
    return (lsobb.cantidad == 0);
}

int llenaLSO(const LSOBB lsobb){
    return (lsobb.cantidad > LSOMAX);
}

int localizarLSO(LSOBB lsobb, const padron p){
    int li = 0; //inclusivo
    int ls = lsobb.cantidad; //inclusivo
    int medio = 0;

    while(li<ls){
            medio = (li+ls)/2;
            if( getDNI(lsobb.datos[medio]) < getDNI(p) ){
                li = medio+1;
            }else{
                ls = medio-1;
            }
    }

    if ( getDNI(lsobb.datos[medio]) == getDNI(p) ){
        return medio;
    }else{
        return -1; // no encontrado
    }
}

int altaLSO(LSOBB *lsobb, const padron elector){
    if ( llenaLSO(*lsobb) ) { return -1;} // lista llena

    int posicion = localizarLSO(*lsobb,elector);
    if (posicion == -1){ return -1;} //no encontrado

    //dar alta en posicion x

    int fin = lsobb->cantidad;
    int costo = 0;
    while (posicion < fin){
        lsobb->datos[fin+1] = lsobb->datos[fin];
        fin--;
        costo++;
    }
    lsobb->datos[posicion] = elector;
    return costo;
}

int bajaLSO(LSOBB *lsobb, const padron elector){
    if ( llenaLSO(*lsobb) ) { return -1;} // lista llena

    int posicion = localizarLSO(*lsobb,elector);
    if (posicion == -1){ return -1;} //no encontrado

    //dar alta en posicion x

    int fin = lsobb->cantidad;
    int costo = 0;
    while (posicion < fin){
        lsobb->datos[posicion] = l->datos[posicion+1];
        posicion++;
        costo++;
    }
    return costo;
}


#endif // LSO_H_INCLUDED
