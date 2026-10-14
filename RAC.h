#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED

#include "funcionHashing.h"
#include "elector.h"
#define MRAC 2411
/*
    factor de carga del RAC: p=0.83
    cantidad de elector estimado: N=2000
    ranura para cada balde: r=1

    Baldes: p = N/M -> M=N/p -> M=2000/0.83
        M = 2409,638...... = 2410
        numero primo cercano: 2411
        verificacion: 2000/2411 = 0,82953...... = 0.83
*/

typedef struct{
        elector datos;// un solo ranura
}RAC;

void initRAC(RAC rac[]){
    int i = 0;
    for(i=0; i < MRAC; i++) initElector(&rac[i].datos);
}

int localizarRAC(RAC rac[], elector e, bool &exito){
    int i=0;
    (*exito) = false;
    if( )
    i = hashing( )
}


#endif // RAC_H_INCLUDED
