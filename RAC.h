#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED

#include "funcionHashing.h"
#include "elector.h"
#include "RA.h"
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

int localizarRAC(const RA rac[], const elector e, int inicial,
                 int *pos, bool *exito){
    (*exito) = false;

    int k=0, actual=0, pcd= 0;
    int costoLocalizar = 0;
    // obtener posicion inicial h(x)
    // actual= inicial+k, y
    // primera celda desocupada PCD
    actual = (inicial + k) % MRAC;
    pcd = -1;//aun no encontrado
    elector guardado;

    while( k<MRAC ){
        guardado = rac[actual].datos;
        costoLocalizar++;
        k++;
        if( (guardado.estado == OCUPADA) && ( guardado.datos.dni == e.dni) ){
                //encontrado, copia de datos
                (*exito) = true;
                (*pos) = actual;
                return costoLocalizar;
        }/*else{
                ocupado pero el dni no es lo que busca
                no encontrado, continua la busqueda
                su tratamiento es logicamente equivalente a estado LIBRE
        }*/
        if( (guardado.estado == LIBRE) && (pcd == -1) ) pcd = actual;
        // si es la primer celda desocupada
        if( guardado.estado == VIRGEN){
            //final de la lista, chequear si han encontrado PCD
            if(pcd == -1) pcd = actual;
            break;
        }
        actual = (actual + k) % MRAC;
        // diferente al anterior, este es actual + k
    }

    // busqueda fallada por intentos exceso de M intentos o celda VIRGEN
    // retorna la primera celda desocupada
    (*pos) = pcd;
    return costoLocalizar;
}

int altaRAC(RA rac[], const elector e, bool *exito){
    (*exito) = false;
    int costoAlta =0, posicion;
    bool exitoL;

    int inicial = hashing(e.dni, MRAC);
    costoAlta += localizarRAC(rac, e, inicial, &posicion, &exitoL);

    if( (exitoL) || ( posicion == -1)) return costoAlta;
    // encuentra con dni repetido, o
    // no hay celda libre para insertar para h(dni, MRAL)
    //debido al exceso de M intento o llegar celda Virgen

    //dar alta en la primera celda desocupada
    rac[posicion].datos = e;
    rac[posicion].estado = OCUPADA;
    (*exito) = true;
    return costoAlta;
}

int bajaRAC(RA rac[], const elector e, bool *exito){
    (*exito) = false;
    int costoBaja =0, posicion;
    bool exitoL;

    int inicial = hashing(e.dni, MRAC);
    costoBaja += localizarRAC(rac, e, inicial, &posicion, &exitoL);

    if( exitoL ){// encontrado, dar de baja
        elector guardado = rac[posicion].datos;
        costoBaja++;//un costo mas para sacarlo de la estructura
        if( elector_sonIguales(guardado, e) ){//comparacion por codigo
            rac[posicion].estado = LIBRE;
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

int evocarRAC(const RA rac[], const elector e, bool *exito, elector *resultado){
    (*exito) = false;
    int costoEvocar = 0, pos=0;

    int inicial = hashing(e.dni, MRAC);
    costoEvocar+= localizarRAC(rac, e,inicial, &pos, exito);

    if( (*exito) ){
        (*resultado) = rac[pos].datos;
        costoEvocar+=1;
    }//encontrado -> copia datos, consulta la celda
    return costoEvocar;
}

#endif // RAC_H_INCLUDED
