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

int localizarLSO(const LSOBB lsobb, const elector Elector, int *posicion){
    if ( vacioLSO(lsobb) ){return 0;}//lista vacia

    int li = 0; //inclusivo
    int ls = lsobb.cantidad-1; //inclusivo
    int medio;
    int dni = getDNI(Elector);
    int costo=0;

    while(li<ls){
            medio = (li+ls)/2;
            if( getDNI(lsobb.datos[medio]) < dni ){
                li = medio+1;
            }else{
                ls = medio;
            }
            costo++;//consulta 1 celda por iteracion
    }
    (*posicion) = li;
    return costo;
    // retornar costo de localizacion
}

int altaLSO(LSOBB *lsobb, const elector Elector){
    if ( llenaLSO(*lsobb) ) { return -1;}
    // lista llena

    int posicion=0;
    localizarLSO(*lsobb,Elector,&posicion);
    if ( elector_sonIguales( lsobb->datos[posicion], Elector) ) { return -2;}
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
    lsobb->datos[posicion] = Elector;
    lsobb->cantidad++;
    return costo;
}

int bajaLSO(LSOBB *lsobb, const elector Elector){
    if ( vacioLSO(*lsobb) ) { return -1;}
    // lista vacia

    int posicion=0;
    localizarLSO(*lsobb,Elector,&posicion);

    if ( elector_sonIguales(lsobb->datos[posicion],Elector) ){
        //debe ser iguales para dar de baja
        int costo = 0;
        int mov=0;
        for (mov = posicion; mov < lsobb->cantidad; mov++){
            lsobb->datos[mov] = lsobb->datos[mov+1];
            costo++;
        }

        lsobb->cantidad--;
        return costo;
    }
    return -1;
    // no se encuentra elector para dar de baja
}

int evocarLSO(const LSOBB lsobb, const elector Elector){

    int posicion=0;
    int costo = localizarLSO(lsobb,Elector,&posicion);

    elector e_temp;
    e_temp = lsobb.datos[posicion];
    costo++;
    if( getDNI(e_temp)!= getDNI(Elector) ){
        // segun pdf, nos da nada mas que dni, no se controla que todo sea igual
        printf("------------------------------------------------------------\n");
        printf("elector <%d> no encontrado! \n", Elector.dni);
        return -1;
    }

    printf("------------------------------------------------------------\n");
    printf("DNI:\t%d\n",e_temp.dni);
    printf("Nombre:\t%s\n",e_temp.nombreApellido);
    printf("Domicilio:\t%s\n",e_temp.domicilio);
    printf("Codigo Postal:\t %d\n",e_temp.cPostal);
    printf("Mesa de votacion: %d\n",e_temp.mesa);
    printf("Circuito:\t%d\n",e_temp.circuito);

    return costo;
}

#endif // LSO_H_INCLUDED
