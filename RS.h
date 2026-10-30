#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funcionHashing.h"
#include "elector.h"
#include "RA.h"

/*
 * ============================================================================
 * JUSTIFICACION TECNICA DEL DIMENSIONAMIENTO DE M (REBALSE SEPARADO)
 * ============================================================================
 * Cantidad estimada de electores: N = 2000
 * Factor de carga fijado por consigna: rho = 1.61
 * Calculo teorico del tamano de tabla:
 *      M = ceil(N / rho) = ceil(2000 / 1.61) = ceil(1242.23...) = 1243
 *
 * Observacion de la catedra sobre primalidad:
 * "En RS no hace falta que sea primo".
 * A diferencia del Rebalse Abierto Cuadratico (RAC), donde la primalidad de M
 * es una condicion matematica necesaria para garantizar que la secuencia de
 * exploracion recorra al menos (M + 1) / 2 celdas distintas sin entrar en
 * ciclos cerrados prematuros, en Rebalse Separado las colisiones se gestionan
 * mediante listas simplemente enlazadas alojadas dinamicamente en el Heap.
 * Cada posicion de la cabecera es un punto de acceso independiente.
 *
 * Por lo tanto, un M no primo (como 1243) o un primo cercano (como 1237) son
 * ambos validos. Se mantiene fijo MRS = 1237 para asegurar compatibilidad con
 * las corridas de prueba previas y la funcion de hashing del proyecto.
 */
#define MRS 1237

/*
 * Estructura de nodo para Rebalse Separado:
 * Cumple estrictamente con la restriccion: "No se utilizaran baldes en la cabecera del RS".
 * La cabecera de la tabla hash es un arreglo unidimensional de punteros a NodoRS.
 */
typedef struct NodoRS {
    elector datos;
    struct NodoRS *sig;
} NodoRS;

typedef NodoRS* RS;

/* Inicializacion de la cabecera: asigna NULL a cada puntero del arreglo */
void initRS(RS tabla[], int M){
    for (int i = 0; i < M; i++){
        tabla[i] = NULL;
    }
}

/*
 * Localizar en RS:
 * Metrica de costo:
 * - 1 acceso a la posicion de la cabecera del arreglo (tabla[actual]).
 * - 1 acceso adicional por cada nodo de la lista enlazada inspeccionado.
 */
int localizarRS(const RS tabla[], const elector e, int inicial, NodoRS **ant, NodoRS **act, bool *exito){
    (*exito) = false;
    int actual = inicial % MRS;
    (*ant) = NULL;
    (*act) = tabla[actual];

    int costoLocalizar = 1; // 1 acceso a la cabecera de la tabla

    while ((*act) != NULL) {
        costoLocalizar++; // +1 por cada nodo recorrido e inspeccionado
        if ((*act)->datos.dni == e.dni) {
            (*exito) = true;
            return costoLocalizar;
        }
        (*ant) = (*act);
        (*act) = (*act)->sig;
    }

    return costoLocalizar;
}

/*
 * Alta en RS:
 * - Si el DNI ya existe, no se inserta y se devuelve el costo de localizacion.
 * - Si no existe, se asigna memoria dinamica para un nuevo nodo, se copian los
 *   datos con elector_copiar y se inserta al inicio de la lista correspondiente
 *   utilizando indexacion modular segura (tabla[inicial % MRS]).
 */
int altaRS(RS tabla[], const elector e, bool *exito){
    (*exito) = false;
    NodoRS *ant = NULL, *act = NULL;
    bool exitoL = false;
    int inicial = hashing(e.dni, MRS);
    int costoAlta = localizarRS(tabla, e, inicial, &ant, &act, &exitoL);

    if (exitoL) return costoAlta; // Elemento repetido

    NodoRS *nuevo = (NodoRS *)malloc(sizeof(NodoRS));
    if (nuevo == NULL) return costoAlta; // Falla en la reserva de memoria

    // Primitiva del TAD elector para transferir la informacion
    elector_copiar(&nuevo->datos, e);

    // Insercion al frente de la lista con indexacion acotada
    int posSegura = inicial % MRS;
    nuevo->sig = tabla[posSegura];
    tabla[posSegura] = nuevo;
    (*exito) = true;

    return costoAlta;
}

/*
 * Baja en RS:
 * - Si localiza el DNI, se accede a la nupla completa del nodo para verificar
 *   la coincidencia exacta de todos los campos mediante elector_sonIguales.
 * - Confirmada la igualdad, se desenlaza el nodo y se libera con free().
 */
int bajaRS(RS tabla[], const elector e, bool *exito){
    (*exito) = false;
    NodoRS *ant = NULL, *act = NULL;
    bool exitoL = false;
    int inicial = hashing(e.dni, MRS);
    int costoBaja = localizarRS(tabla, e, inicial, &ant, &act, &exitoL);

    if (exitoL) {
        costoBaja++; // Acceso a la nupla completa para confirmacion por codigo
        if (elector_sonIguales(act->datos, e)) {
            int posSegura = inicial % MRS;
            if (ant == NULL) {
                tabla[posSegura] = act->sig;
            } else {
                ant->sig = act->sig;
            }
            free(act); // Liberacion segura del nodo
            (*exito) = true;
            return costoBaja;
        }
    }

    return costoBaja;
}

/*
 * Evocacion en RS:
 * - Retorna estrictamente el costo devuelto por localizarRS.
 * - La asignacion del elector encontrado al parametro de salida (*resultado)
 *   mediante elector_copiar constituye la entrega del resultado y no anade
 *   ninguna inspeccion estructural de celda adicional.
 */
int evocarRS(const RS tabla[], const elector e, bool *exito, elector *resultado){
    *exito = false;
    NodoRS *ant = NULL;
    NodoRS *act = NULL;
    int pos = hashing(e.dni, MRS);
    int costo = localizarRS(tabla, e, pos, &ant, &act, exito);

    if (*exito) {
        elector_copiar(resultado, act->datos);
    }
    return costo;
}

/*
 * Muestra paginada de RS:
 * - Enumera las listas de 1 a M (i + 1).
 * - Muestra elementos o indica lista vacia.
 * - Pausa cada ITEMPORPAGINA listas, permitiendo continuar con ENTER o salir con 'q'/'Q'.
 */
void mostrarRS(const RS tabla[], int M){
    int ocupadas = 0;
    int total = 0;
    int contadorPaginacion = 0;

    for (int i = 0; i < M; i++) {
        printf("------------------------------------------------------------\n");
        if (tabla[i] == NULL) {
            printf("[%d] Lista VACIA\n", i + 1);
        } else {
            ocupadas++;
            printf("[%d] Lista OCUPADA:\n", i + 1);
            NodoRS *act = tabla[i];
            int n = 1;
            while (act != NULL) {
                total++;
                printf("  -> Elemento #%d:\n", n++);
                elector_mostrar(act->datos);
                act = act->sig;
            }
        }

        contadorPaginacion++;
        if (contadorPaginacion == ITEMPORPAGINA) {
            contadorPaginacion = 0;
            printf("------------------------------------------------------------\n");
            printf("  Enter = seguir    q = salir\n  usuario ->\t");
            int c = getchar();
            if (c == 'q' || c == 'Q') {
                while (getchar() != '\n');
                printf("  ... cancelado\n");
                break;
            }
            while (c != '\n' && c != EOF) c = getchar();
            system("cls");
        }
    }
    printf("============================================================\n");
    printf(" Total: %d electores registrados en %d listas activas.\n", total, ocupadas);
    printf("============================================================\n");
}

/*
 * Liberacion de memoria dinamica de RS:
 * Recorre las M listas enlazadas liberando cada nodo y resetea los punteros a NULL.
 */
void liberarRS(RS tabla[], int M){
    for (int i = 0; i < M; i++) {
        NodoRS *act = tabla[i];
        while (act != NULL) {
            NodoRS *aux = act;
            act = act->sig;
            free(aux);
        }
        tabla[i] = NULL;
    }
}

#endif // RS_H_INCLUDED
