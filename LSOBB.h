#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED

#define LSOMAX 2000
#include "elector.h"
#include <math.h>

typedef struct{
    elector datos[LSOMAX];
    int cantidad;
    //cantidad de elector registrado
}LSOBB;

void initLSOBB(LSOBB *lsobb) {
    lsobb->cantidad = 0;
    /*
    1. posicion "vacio"
    2. cantidad-1 = indice del ultimo elemento
    */
}

float localizarLSO(const LSOBB lsobb, const elector Elector, int *posicion, bool *exito){
    (*exito) = false;
    (*posicion) = 0;
    float costo = 0.0f;
    if ( lsobb.cantidad==0 ) return costo;//lista vacia

    int li = 0; //inclusivo
    int ls = lsobb.cantidad-1; //inclusivo
    int medio;
    int dni = Elector.dni;

    int vector_flag[LSOMAX];
    for (int i = 0; i < LSOMAX; i++){
        vector_flag[i] = 0;
    }

    while(li<ls){
            medio = (li+ls)/2;
            if ( !vector_flag[medio] ) costo+=1.0f;
            if( lsobb.datos[medio].dni < dni ){
                li = medio+1;
            }else{
                ls = medio;
            }
            vector_flag[medio]=1;
    }
    (*exito) = (lsobb.datos[li].dni == dni);
    (*posicion) = li;
    return costo;
    // retornar posicion
}

float altaLSO(LSOBB *lsobb, const elector Elector, bool *exito){
    float costo=0.0f;
    (*exito) = false;
    if ( lsobb->cantidad >= LSOMAX) return costo;
    // lista llena

    int posicion=0;
    bool exitoL=false;
    if( lsobb->cantidad==0 ){
        lsobb->datos[0] = Elector;
        lsobb->cantidad++;
        (*exito) = true;
        return costo;
    }
    localizarLSO(*lsobb, Elector, &posicion, &exitoL);

    if ( exitoL ) return costo;
    // sus dni son iguales, no se da la alta

    //======else======
    // dar alta en posicion, mover elementos para hacer lugar
    if (lsobb->datos[posicion].dni < Elector.dni) posicion = posicion + 1;
    // posicion esta dentro de [0,cantidad-1], el dni debe ser mayor o igual
    // si es menor, por orden creciente, debe insertar despues del posicion
    // lista vacio solucionado anteriormente

    int mov = 0;
    for (mov = lsobb->cantidad; mov>posicion; mov--){
        lsobb->datos[mov] = lsobb->datos[mov-1];
        costo+=1.0f;
    }
    // dar alta, aumentar cantidad almacenada
    lsobb->datos[posicion] = Elector;
    lsobb->cantidad++;
    (*exito) = true;
    return costo;
}

int bajaLSO(LSOBB *lsobb, const elector Elector, bool *exito){
    int costo=0;
    (*exito) = false;
    if ( lsobb->cantidad==0 ) return costo;

    int posicion = 0;
    bool exitoL =false;
    localizarLSO(*lsobb, Elector, &posicion, &exitoL);

    if ( exitoL){
        if( elector_sonIguales( lsobb->datos[posicion], Elector)) {
            //debe ser iguales para dar de baja
            int mov=0;
            for (mov = posicion; mov < lsobb->cantidad-1; mov++){
                lsobb->datos[mov] = lsobb->datos[mov+1];
                costo+=1.0f;
            }
            lsobb->cantidad--;
            (*exito) = true;
            return costo;
        }
    }
    return costo;
}

float evocarLSO(const LSOBB lsobb, const elector Elector, bool *exito, elector *resultado){
    float costo = 0.0f;
    (*exito) = false;
    if(lsobb.cantidad == 0) return costo;// no hay resultado para lista vacia

    int posicion = 0;
    costo += localizarLSO(lsobb, Elector, &posicion, exito);

    if((*exito)){
            (*resultado) = lsobb.datos[posicion];
    }
    return costo;
}

#endif // LSO_H_INCLUDED
