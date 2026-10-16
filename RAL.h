#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED

#include "funcionHashing.h"
#include "elector.h"
#include "RA.h"
#define MRAL 2531
/*
    factor de carga del RAL: p=0.79
    cantidad de elector estimado: N=2000

    Baldes: p = N/M -> M=N/p -> M=2000/0.79
        M = 2531,645...... = 2532
        numero primo cercano: 2531
        verificacion: 2000/2531 = 0,79021...... = 0.79
*/

int localizarRAL(const RA ral[], const elector e, int inicial,
                 int *pos, bool *exito){
    (*exito) = false;

    int k=0, actual=0, pcd= 0;
    int costoLocalizar = 0;
    // obtener posicion inicial h(x)
    // actual= inicial
    // primera celda desocupada PCD
    actual = inicial % MRAL;
    pcd = -1;//aun no encontrado

    while( k<MRAL ){
        costoLocalizar++;
        k++;
        if( (ral[actual].estado == OCUPADA) && ( ral[actual].datos.dni == e.dni) ){
                //encontrado, copia de datos
                (*exito) = true;
                (*pos) = actual;
                return costoLocalizar;
        }/*else{
                ocupado pero el dni no es lo que busca
                no encontrado, continua la busqueda
                su tratamiento es logicamente equivalente a estado LIBRE
        }*/

        if( (ral[actual].estado == LIBRE) && (pcd == -1) ) pcd = actual;
        // si es la primer celda desocupada
        if( ral[actual].estado == VIRGEN){
            //final de la lista, chequear si han encontrado PCD
            if(pcd == -1) pcd = actual;
            break;
        }
        actual = (actual + 1) % MRAL;
        // diferente al anterior, este es actual + k, k=1
    }

    // busqueda fallada por intentos exceso de M intentos o celda VIRGEN
    // retorna la primera celda desocupada
    (*pos) = pcd;
    return costoLocalizar;
}

int altaRAL(RA ral[], const elector e, bool *exito){
    (*exito) = false;
    int costoAlta =0, posicion;
    bool exitoL;

    int inicial = hashing(e.dni, MRAL);
    costoAlta += localizarRAC(ral, e, inicial, &posicion, &exitoL);

    if( (exitoL) || ( posicion == -1)) return costoAlta;
    // encuentra con dni repetido, o
    // no hay celda libre para insertar para h(dni, MRAL)
    //debido al exceso de M intento o llegar celda Virgen

    //dar alta en la primera celda desocupada
    ral[posicion].datos = e;
    ral[posicion].estado = OCUPADA;
    (*exito) = true;
    return costoAlta;
}

int bajaRAL(RA ral[], const elector e, bool *exito){
    (*exito) = false;
    int costoBaja =0, posicion;
    bool exitoL;

    int inicial = hashing(e.dni, MRAL);
    costoBaja += localizarRAC(ral, e, inicial, &posicion, &exitoL);

    if( exitoL ){// encontrado, dar de baja
        elector guardado = ral[posicion].datos;
        costoBaja++;//un costo mas para sacarlo de la estructura
        if( elector_sonIguales(guardado, e) ){//comparacion por codigo
            ral[posicion].estado = LIBRE;
            (*exito) = true;
            return costoBaja;
        }
    }
    /*si se encuentra exitoL==true, empieza dar de baja
    sacando de la estructura -> costo por consultar +1
    comparar toda la nupla, si esta bien, recien ahi se da la baja
    actualizando el estado, exito=true, y retornar el costo
    sino, se sale de la rutina*/

    return costoBaja;
}

int evocarRAL(const RA ral[], const elector e, bool *exito, elector *resultado){
    (*exito) = false;
    int costoEvocar = 0, pos=0;

    int inicial = hashing(e.dni, MRAL);
    costoEvocar+= localizarRAL(ral, e,inicial, &pos, exito);

    if( (*exito) ){
        (*resultado) = ral[pos].datos;
        costoEvocar+=1;
    }//encontrado -> copia datos, consulta la celda
    return costoEvocar;
}


#endif // RAL_H_INCLUDED
