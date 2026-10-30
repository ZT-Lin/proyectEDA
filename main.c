/*
====== GRUPO 41 =======
Correa Valentin, Lin Franco.
====================

==================== FUNCION DE COSTOS ====================
Cantidad de celdas consultadas para realizar dicha operacion en cada una de las estructuras,
un punto (1) por cada celda (incluyendo celdas repetidas).

========== CONSTANTE UTIL Y SU UBICACION ==============
RA.h:
    - ITEMPORPAGINA: usado para paginar la muestra
RAL.h:
    - MRAL: cantidad de baldes de Rebalse Abierto Lineal (2531)
RAC.h:
    - MRAC: cantidad de baldes de Rebalse Abierto Cuadratico (2411)
RS.h:
    - MRS: cantidad de listas en la cabecera de Rebalse Separado (1237)

============ COMPARACION DE ESTRUCTURAS ============
| OPERACION              |                  RAL |                  RAC |                   RS |
===============================================================================================
| ALTA EXITO             |                      |                      |                      |
|   Total realizado      |              2746.00 |              2746.00 |              2746.00 |
|   Total costo          |           3196382.00 |            124633.00 |             18115.00 |
|   Maximo               |              1997.00 |                67.00 |                30.00 |
|   Promedio             |              1164.01 |                45.39 |                 6.60 |
-----------------------------------------------------------------------------------------------
| ALTA FRACASO           |                      |                      |                      |
|   Total realizado      |                 0.00 |                 0.00 |                 0.00 |
|   Total costo          |                 0.00 |                 0.00 |                 0.00 |
|   Maximo               |                 0.00 |                 0.00 |                 0.00 |
|   Promedio             |                 0.00 |                 0.00 |                 0.00 |
-----------------------------------------------------------------------------------------------
| BAJA EXITO             |                      |                      |                      |
|   Total realizado      |              2001.00 |              2001.00 |              2001.00 |
|   Total costo          |           1790912.00 |             80431.00 |             19473.00 |
|   Maximo               |              1965.00 |                66.00 |                32.00 |
|   Promedio             |               895.01 |                40.20 |                 9.73 |
-----------------------------------------------------------------------------------------------
| BAJA FRACASO           |                      |                      |                      |
|   Total realizado      |                 0.00 |                 0.00 |                 0.00 |
|   Total costo          |                 0.00 |                 0.00 |                 0.00 |
|   Maximo               |                 0.00 |                 0.00 |                 0.00 |
|   Promedio             |                 0.00 |                 0.00 |                 0.00 |
-----------------------------------------------------------------------------------------------
| EVOCAR EXITO           |                      |                      |                      |
|   Total realizado      |              2175.00 |              2175.00 |              2175.00 |
|   Total costo          |           1219696.00 |             66259.00 |             13504.00 |
|   Maximo               |              1965.00 |                66.00 |                20.00 |
|   Promedio             |               560.78 |                30.46 |                 6.21 |
-----------------------------------------------------------------------------------------------
| EVOCAR FRACASO         |                      |                      |                      |
|   Total realizado      |              2053.00 |              2053.00 |              2053.00 |
|   Total costo          |           3243918.00 |            115104.00 |             14861.00 |
|   Maximo               |              1998.00 |                68.00 |                19.00 |
|   Promedio             |              1580.09 |                56.07 |                 7.24 |
===============================================================================================

================== ANALISIS DE RESULTADOS Y COMPLEJIDAD TEORICA ==================

1. Rebalse Abierto Lineal (RAL) y Cuadratico (RAC):
   - Peor caso: En direccionamiento abierto el limite de busqueda son M intentos, que serian las celdas totales de la tabla.
     Por ende, el peor caso se da cuando barremos las M posiciones sin toparnos con una celda VIRGEN ni con la clave buscada, cayendo en O(M).
   - Operacion de Evocacion: Equivale directamente a lo que cuesta ubicar la clave en la estructura, sumando 1 punto por cada celda inspeccionada al comparar el DNI.
     Copiar el registro a la variable de salida es una transferencia interna en memoria, asi que no suma un acceso extra (+1).
   - Comportamiento esperado: Manejando rho_RAL = 0.79 y rho_RAC = 0.83, RAC mitiga el agrupamiento primario que castiga feo a RAL tras varias altas y bajas,
     donde los estados LIBRE obligan a seguir recorriendo hasta toparse con una celda VIRGEN. A tener en cuenta: solo en RAC es obligatorio que M sea un numero primo para
     garantizar que la exploracion cuadratica recorra al menos (M + 1)/2 posiciones distintas sin entrar en bucles; en RAL no hace falta porque el paso es 1 y mcd(1, M) = 1.

2. Rebalse Separado (RS):
   - Peor caso: El peor caso teorico de RS no es O(M), sino O(N), siendo N el total de elementos cargados.
     Esto ocurre ante una colision total donde absolutamente todos los registros caen en la misma posicion de la cabecera,
     formando una unica lista encadenada de longitud N. En ese escenario, buscar requiere 1 acceso a la celda cabecera mas N lecturas en los nodos de la lista (1 + N accesos),
     por lo que pertenece a O(N).
   - Comportamiento esperado: Con rho_RS = 1.61, la longitud media de cada lista resulta alpha = 1.61.
     Como las listas se manejan de forma independiente en memoria dinamica y las bajas liberan fisicamente el nodo con free()
     (sin dejar marcas tipo "libre" que estiren las busquedas a futuro), RS ofrece el mejor rendimiento global en todas las operaciones.
     Aparte, no requiere que M sea primo porque las colisiones se resuelven fuera de la tabla estatica.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "RAC.h"
#include "RAL.h"
#include "RS.h"
#include "costo.h"
#include "elector.h"
#include "funcionHashing.h"

void mostrar_menu(void);
void enter(void);
int cargarEstructura(RA[], RA[], RS[]);
void mostrarRA(RA[], int);

// ========== Costos de cada estructura ==========
Costo cAlta_rac_ex, cBaja_rac_ex, cEvocar_rac_ex;
Costo cAlta_rac_fr, cBaja_rac_fr, cEvocar_rac_fr;

Costo cAlta_ral_ex, cBaja_ral_ex, cEvocar_ral_ex;
Costo cAlta_ral_fr, cBaja_ral_fr, cEvocar_ral_fr;

Costo cAlta_rs_ex, cBaja_rs_ex, cEvocar_rs_ex;
Costo cAlta_rs_fr, cBaja_rs_fr, cEvocar_rs_fr;

/* Tabla completa comparativa: RAL | RAC | RS */
void mostrarTablaCostos(void){
    lineaTabla('=', 95);
    printf("| %-22s | %20s | %20s | %20s |\n",
           "OPERACION", "RAL", "RAC", "RS");
    lineaTabla('=', 95);

    bloqueCostos("ALTA EXITO",     &cAlta_ral_ex,   &cAlta_rac_ex,   &cAlta_rs_ex);
    lineaTabla('-', 95);
    bloqueCostos("ALTA FRACASO",   &cAlta_ral_fr,   &cAlta_rac_fr,   &cAlta_rs_fr);
    lineaTabla('-', 95);

    bloqueCostos("BAJA EXITO",     &cBaja_ral_ex,   &cBaja_rac_ex,   &cBaja_rs_ex);
    lineaTabla('-', 95);
    bloqueCostos("BAJA FRACASO",   &cBaja_ral_fr,   &cBaja_rac_fr,   &cBaja_rs_fr);
    lineaTabla('-', 95);

    bloqueCostos("EVOCAR EXITO",   &cEvocar_ral_ex, &cEvocar_rac_ex, &cEvocar_rs_ex);
    lineaTabla('-', 95);
    bloqueCostos("EVOCAR FRACASO", &cEvocar_ral_fr, &cEvocar_rac_fr, &cEvocar_rs_fr);
    lineaTabla('=', 95);
}

int main(void){
    bool SISTEMA = true;
    char comando_user[100];

    // ========== Inicializacion de costos (Exito) ==========
    initCosto(&cAlta_rac_ex);
    initCosto(&cAlta_ral_ex);
    initCosto(&cAlta_rs_ex);

    initCosto(&cBaja_rac_ex);
    initCosto(&cBaja_ral_ex);
    initCosto(&cBaja_rs_ex);

    initCosto(&cEvocar_rac_ex);
    initCosto(&cEvocar_ral_ex);
    initCosto(&cEvocar_rs_ex);

    // ========== Inicializacion de costos (Fracaso) ==========
    initCosto(&cAlta_rac_fr);
    initCosto(&cAlta_ral_fr);
    initCosto(&cAlta_rs_fr);

    initCosto(&cBaja_rac_fr);
    initCosto(&cBaja_ral_fr);
    initCosto(&cBaja_rs_fr);

    initCosto(&cEvocar_rac_fr);
    initCosto(&cEvocar_ral_fr);
    initCosto(&cEvocar_rs_fr);

    // ========== Estructuras ==========
    RA RACuadratico[MRAC], RALineal[MRAL];
    RS RSeparado[MRS];
    initRA(RACuadratico, MRAC);
    initRA(RALineal, MRAL);
    initRS(RSeparado, MRS);

    while (SISTEMA) {
        system("cls");
        mostrar_menu();

        if (scanf("%99s", comando_user) != 1) {
            continue;
        }
        getchar();

        if (strlen(comando_user) != 1) {
            printf("============================================================\n");
            printf("\t Error: opcion invalida\n");
            enter();
            continue;
        }

        switch (comando_user[0]) {
            case '1': {
                system("cls");
                mostrarRA(RALineal, MRAL);
                enter();
                break;
            } // Mostrar estructura RAL
            case '2': {
                system("cls");
                mostrarRA(RACuadratico, MRAC);
                enter();
                break;
            } // Mostrar estructura RAC
            case '3': {
                system("cls");
                mostrarRS(RSeparado, MRS);
                enter();
                break;
            } // Mostrar estructura RS
            case '4': { //controlar si carga bien los datos
                system("cls");
                if (cargarEstructura(RACuadratico, RALineal, RSeparado) != 0) {
                    printf("============================================================\n");
                    printf("\tHubo error en la carga de datos!\n");
                    enter();
                    break;
                } else {
                    printf("============================================================\n");
                    printf("\tCarga de datos con exito!\n");
                    mostrarTablaCostos();
                    enter();
                }
                break;
            } // Comparar estructuras
            case '0': {
                SISTEMA = false;
                liberarRS(RSeparado, MRS); // Liberamos memoria de la estructura dinamica
                break;
            }
            default: {
                printf("============================================================\n");
                printf("\t Error: opcion invalida\n");
                enter();
                continue;
            }
        } // switch
    } // while
    return 0;
} // main

void mostrar_menu(void){
    printf("============================================================\n");
    printf("     PADRON ELECTORAL - COMPARACION DE ESTRUCTURAS HASH     \n");
    printf("============================================================\n");
    printf("  1. Mostrar Rebalse Abierto Lineal (RAL)\n");
    printf("  2. Mostrar Rebalse Abierto Cuadratico (RAC)\n");
    printf("  3. Mostrar Rebalse Separado (RS)\n");
    printf("  4. Comparacion de estructuras\n");
    printf("  0. Salir\n");
    printf("============================================================\n");
    printf("usuario -> ");
}

void enter(void){
    printf("============================================================\n");
    printf("\tPresionar \"enter\" para continuar\n");
    printf("============================================================\n");
    getchar();
}

int cargarEstructura(RA rac[], RA ral[], RS rs[]){
    FILE *operaciones = fopen("Operaciones_Padron.txt", "r");
    if (operaciones == NULL) return -1;

    // Reinicializamos estructuras estaticas y dinamicas por si se carga mas de una vez y no se haga cosas raras
    initRA(rac, MRAC);
    initRA(ral, MRAL);
    liberarRS(rs, MRS);
    initRS(rs, MRS);

    // Reinicializamos contadores de costos para no acumular sobre una carga que estaba antes
    initCosto(&cAlta_rac_ex);   initCosto(&cAlta_ral_ex);   initCosto(&cAlta_rs_ex);
    initCosto(&cBaja_rac_ex);   initCosto(&cBaja_ral_ex);   initCosto(&cBaja_rs_ex);
    initCosto(&cEvocar_rac_ex); initCosto(&cEvocar_ral_ex); initCosto(&cEvocar_rs_ex);
    initCosto(&cAlta_rac_fr);   initCosto(&cAlta_ral_fr);   initCosto(&cAlta_rs_fr);
    initCosto(&cBaja_rac_fr);   initCosto(&cBaja_ral_fr);   initCosto(&cBaja_rs_fr);
    initCosto(&cEvocar_rac_fr); initCosto(&cEvocar_ral_fr); initCosto(&cEvocar_rs_fr);

    float costo = 0.0f;
    elector e_temp;
    elector e_result;
    int itemp = 0;
    char nam[51], dom[81];
    bool exito;

    int comando = 0;
    while (fscanf(operaciones, "%d", &comando) == 1) {
        initElector(&e_temp);
        exito = false;

        if ((comando == 1) || (comando == 2)) {
            fscanf(operaciones, "%d", &itemp);
            e_temp.dni = itemp;

            // Consumir salto de linea pendiente tras el DNI antes de leer el nombre
            fscanf(operaciones, "%*[\r\n ]");
            if (fgets(nam, sizeof(nam), operaciones) != NULL) {
                nam[strcspn(nam, "\r\n")] = '\0';
                for (int c = 0; nam[c] != '\0'; c++) {
                    nam[c] = (char)tolower((unsigned char)nam[c]);
                }
                strcpy(e_temp.nombreApellido, nam);
            }

            // Leer domicilio
            if (fgets(dom, sizeof(dom), operaciones) != NULL) {
                dom[strcspn(dom, "\r\n")] = '\0';
                for (int c = 0; dom[c] != '\0'; c++) {
                    dom[c] = (char)tolower((unsigned char)dom[c]);
                }
                strcpy(e_temp.domicilio, dom);
            }

            fscanf(operaciones, "%d", &itemp);
            e_temp.cPostal = itemp;
            fscanf(operaciones, "%d", &itemp);
            e_temp.mesa = itemp;
            fscanf(operaciones, "%d", &itemp);
            e_temp.circuito = itemp;
        } else {
            fscanf(operaciones, "%d", &itemp);
            e_temp.dni = itemp;
        }

        switch (comando) {
            case 1: {
                // RAL alta
                costo = (float)altaRAL(ral, e_temp, &exito);
                if (exito) acumular(&cAlta_ral_ex, costo);
                else       acumular(&cAlta_ral_fr, costo);

                // RAC alta
                costo = (float)altaRAC(rac, e_temp, &exito);
                if (exito) acumular(&cAlta_rac_ex, costo);
                else       acumular(&cAlta_rac_fr, costo);

                // RS alta
                costo = (float)altaRS(rs, e_temp, &exito);
                if (exito) acumular(&cAlta_rs_ex, costo);
                else       acumular(&cAlta_rs_fr, costo);

                break;
            }
            case 2: {
                // RAL baja
                costo = (float)bajaRAL(ral, e_temp, &exito);
                if (exito) acumular(&cBaja_ral_ex, costo);
                else       acumular(&cBaja_ral_fr, costo);

                // RAC baja
                costo = (float)bajaRAC(rac, e_temp, &exito);
                if (exito) acumular(&cBaja_rac_ex, costo);
                else       acumular(&cBaja_rac_fr, costo);

                // RS baja
                costo = (float)bajaRS(rs, e_temp, &exito);
                if (exito) acumular(&cBaja_rs_ex, costo);
                else       acumular(&cBaja_rs_fr, costo);

                break;
            }
            case 3: {
                // RAL evocar
                costo = (float)evocarRAL(ral, e_temp, &exito, &e_result);
                if (exito) acumular(&cEvocar_ral_ex, costo);
                else       acumular(&cEvocar_ral_fr, costo);

                // RAC evocar
                costo = (float)evocarRAC(rac, e_temp, &exito, &e_result);
                if (exito) acumular(&cEvocar_rac_ex, costo);
                else       acumular(&cEvocar_rac_fr, costo);

                // RS evocar
                costo = (float)evocarRS(rs, e_temp, &exito, &e_result);
                if (exito) acumular(&cEvocar_rs_ex, costo);
                else       acumular(&cEvocar_rs_fr, costo);

                break;
            }
        }
    }

    promedio(&cAlta_rac_ex);
    promedio(&cBaja_rac_ex);
    promedio(&cEvocar_rac_ex);
    promedio(&cAlta_rac_fr);
    promedio(&cBaja_rac_fr);
    promedio(&cEvocar_rac_fr);

    promedio(&cAlta_ral_ex);
    promedio(&cBaja_ral_ex);
    promedio(&cEvocar_ral_ex);
    promedio(&cAlta_ral_fr);
    promedio(&cBaja_ral_fr);
    promedio(&cEvocar_ral_fr);

    promedio(&cAlta_rs_ex);
    promedio(&cBaja_rs_ex);
    promedio(&cEvocar_rs_ex);
    promedio(&cAlta_rs_fr);
    promedio(&cBaja_rs_fr);
    promedio(&cEvocar_rs_fr);

    fclose(operaciones);
    return 0;
}
