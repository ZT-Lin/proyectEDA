#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED

#define LSOMAX 2000
#include "padron.h"
#include <math.h>

typedef struct{
    padron datos[LSOMAX];
    int cantidad;
}LSOBB;

void LSOBB_inicializar(LSOBB *lista) {
    lista->cantidad = 0;
}


int altaLSO(LSOBB *l, const padron elector){
    if (l->cantidad >= LSOMAX) {
        return -1;  // error: lista llena
    }
    int li = 0; //inclusivo
    int ls = l->cantidad; //inclusivo
    int medio = 0;
    int celdas_visitadas = 0;

    while( li<ls ){
        medio = floor( (li + ls)/2 ); //testigo a izquierda

        //aca visita una celda
        if( getDNI(l->datos[medio]) <  getDNI(elector) ){
            li = medio+1;
        }else{
            ls = medio;
        }
        celdas_visitadas++;
    }

    /*
    cuando sale del while: tiene una lista de tamanio 1
    con lista.contenido.dni >= elector.dni
    hay que insertar por en celda izquierda
    */



}

#endif // LSO_H_INCLUDED
