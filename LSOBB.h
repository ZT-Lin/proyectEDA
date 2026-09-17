#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED

#define LSOMAX 2000
#include "padron.h"
#include <math.h>

typedef struct{
    padron datos[LSOMAX];
    int cantidad;
}LSOBB;

void LSOBB_inicializar(LSOBB *lsobb) {
    lsobb->cantidad = 0;
}

int vacioLSO(const LSOBB lsobb){
    return (lsobb.cantidad == 0);
}

int llenaLSO(const LSOBB lsobb){
    return (lsobb.cantidad >= LSOMAX);
}

int localizarLSO(const LSOBB lsobb, const padron elector, int *costo){
    if ( vacioLSO(lsobb) ){return 0;}//lista vacia

    int li = 0; //inclusivo
    int ls = lsobb.cantidad-1; //inclusivo
    int medio;
    int localizar = getDNI(elector);

    while(li<ls){
            medio = (li+ls)/2;
            if( getDNI(lsobb.datos[medio]) < localizar ){
                li = medio+1;
            }else{
                ls = medio;
            }
            *costo++;//consulta 1 celda por iteracion
    }

    return li;
    // retornar posicion donde
}

int altaLSO(LSOBB *lsobb, const padron elector){
    if ( llenaLSO(*lsobb) ) { return -1;}
    // lista llena

    int posicion = localizarLSO(*lsobb,elector,0);
    if ( padron_sonIguales( &lsobb->datos[posicion], &elector) ) { return -1;}
    // son iguales, no se da la alta

    // dar alta en posicion x
    // mover elementos para hacer lugar
    int costo = 0;
    int mov = 0;
    for (mov = lsobb->cantidad; mov>posicion; mov--){
        lsobb->datos[mov] = lsobb->datos[mov-1];
        costo++;
    }
    // dar alta, aumentar cantidad almacenada
    lsobb->datos[posicion] = elector;
    lsobb->cantidad++;
    return costo;
}

int bajaLSO(LSOBB *lsobb, const padron elector){
    if ( vacioLSO(*lsobb) ) { return -1;}
    // lista vacia

    int posicion = localizarLSO(*lsobb,elector,0);

    if ( padron_sonIguales(&lsobb->datos[posicion],&elector) ){
        //debe ser iguales para dar de baja
        int costo = 0;
        int mov=0;
        for (mov = posicion; mov < lsobb->cantidad-1; mov++){
            lsobb->datos[mov] = lsobb->datos[mov+1];
            costo++;
        }

        lsobb->cantidad--;
        return costo;
    }
    return -1;
    // no se encuentra elector para dar de baja
}


#endif // LSO_H_INCLUDED
