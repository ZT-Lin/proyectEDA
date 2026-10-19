/*
====== GRUPO 41 =======
Correa Valentin, Lin Franco.
====================


====================FUNCION DE COSTOS====================

cantidad de celdas consultadas para realizar dicha operación en cada una de las estructuras
un punto (1) por cada celda.

SI cuenta celdas repetidas.

==========CONSTANTE UTIL Y SU UBICACION==============

RA.h:
    - ITEMPORPAGINA: usado para paginar la muestra

RAL.h:
    - MRAL: cantidad de balde de Rebalse Abierto Lineal
RAC.h
    - MRAC: cantidad de balde de Rebalse Abierto Cuadratico
RS.h
    - MRS: cantidad de balde de Rebalse Separado

============COMPARACION DE ESTRUCTURAS============
| OPERACION              |                  RAL |                  RAC |                   RS |
===============================================
| ALTA EXITO             |                      |                      |                      |
|   Total realizado      |            2746.0000 |            2746.0000 |            2746.0000 |
|   Total costo          |         3196382.0000 |          124633.0000 |           18115.0000 |
|   Maximo               |            1997.0000 |              67.0000 |              30.0000 |
|   Promedio             |            1164.0138 |              45.3871 |               6.5969 |
-----------------------------------------------------------------------------------------------
| ALTA FRACASO           |                      |                      |                      |
|   Total realizado      |               0.0000 |               0.0000 |               0.0000 |
|   Total costo          |               0.0000 |               0.0000 |               0.0000 |
|   Maximo               |               0.0000 |               0.0000 |               0.0000 |
|   Promedio             |               0.0000 |               0.0000 |               0.0000 |
-----------------------------------------------------------------------------------------------
| BAJA EXITO             |                      |                      |                      |
|   Total realizado      |            2001.0000 |            2001.0000 |            2001.0000 |
|   Total costo          |         1790912.0000 |           80431.0000 |           19473.0000 |
|   Maximo               |            1965.0000 |              66.0000 |              32.0000 |
|   Promedio             |             895.0085 |              40.1954 |               9.7316 |
-----------------------------------------------------------------------------------------------
| BAJA FRACASO           |                      |                      |                      |
|   Total realizado      |               0.0000 |               0.0000 |               0.0000 |
|   Total costo          |               0.0000 |               0.0000 |               0.0000 |
|   Maximo               |               0.0000 |               0.0000 |               0.0000 |
|   Promedio             |               0.0000 |               0.0000 |               0.0000 |
-----------------------------------------------------------------------------------------------
| EVOCAR EXITO           |                      |                      |                      |
|   Total realizado      |            2175.0000 |            2175.0000 |            2175.0000 |
|   Total costo          |         1217521.0000 |           64084.0000 |           11329.0000 |
|   Maximo               |            1964.0000 |              65.0000 |              19.0000 |
|   Promedio             |             559.7798 |              29.4639 |               5.2087 |
-----------------------------------------------------------------------------------------------
| EVOCAR FRACASO         |                      |                      |                      |
|   Total realizado      |            2053.0000 |            2053.0000 |            2053.0000 |
|   Total costo          |         3243918.0000 |          115104.0000 |           14861.0000 |
|   Maximo               |            1998.0000 |              68.0000 |              19.0000 |
|   Promedio             |            1580.0867 |              56.0662 |               7.2387 |
==================================================

==================REBALSE ABIERTO LINEAL / CUADRATICO==================
De acuerdo al limite de recorrer puesto para todas las REBALSES ABIERTAS fueron:
                                            intentos < M
M=cantidad de baldes que pertenece a cada una. Por lo tanto, el peor caso es
cuando el intento supera al M:
                                            intentos >= M
entonces: *para alta y baja (ninguno de los dos consulta el celda cuando realiza
                    sus operaciones correspondientes)
                    ->pertenece al O(M),
                *para evocar, al final de la rutina simpre suma 1 por consultar a la celda para
                    extraer el elector, su costo es siempre costoLocalizar+1, es similar al del alta y baja
                    ->pertenece al O(M)

==========================REBALSE SEPARADO========================
Tiene el mejor costo de todas las estructuras.

Se consulta la lista segun el funcion hashing (consulta al celda->costo+1)
y luego recorre la lista vinculada hasta llegar al final (head->null, costo+longitud de la lista)

el peor caso es cuando todos los elementos guarda en el mismo lugar
=> pertenece al O(M)

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

int mostrar_menu(void);
void enter(void);

int cargarEstructura(RA[], RA[], RS[]);

void mostrarRA(RA[], int);
//==========costos de cada una==========
Costo cAlta_rac_ex, cBaja_rac_ex, cEvocar_rac_ex;
Costo cAlta_rac_fr, cBaja_rac_fr, cEvocar_rac_fr;

Costo cAlta_ral_ex, cBaja_ral_ex, cEvocar_ral_ex;
Costo cAlta_ral_fr, cBaja_ral_fr, cEvocar_ral_fr;

Costo cAlta_rs_ex, cBaja_rs_ex, cEvocar_rs_ex;
Costo cAlta_rs_fr, cBaja_rs_fr, cEvocar_rs_fr;

/* tabla completa: RAL | RAC | RS */
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


int main(){
    // menu
    bool SISTEMA = true;
    char comando_user[100];

    //==========init costos(exito)==========
    initCosto(&cAlta_rac_ex);
    initCosto(&cAlta_ral_ex);
    initCosto(&cAlta_rs_ex);

    initCosto(&cBaja_rac_ex);
    initCosto(&cBaja_ral_ex);
    initCosto(&cBaja_rs_ex);

    initCosto(&cEvocar_rac_ex);
    initCosto(&cEvocar_ral_ex);
    initCosto(&cEvocar_rs_ex);

    //==========init costos(fracaso)==========
    initCosto(&cAlta_rac_fr);
    initCosto(&cAlta_ral_fr);
    initCosto(&cAlta_rs_fr);

    initCosto(&cBaja_rac_fr);
    initCosto(&cBaja_ral_fr);
    initCosto(&cBaja_rs_fr);

    initCosto(&cEvocar_rac_fr);
    initCosto(&cEvocar_ral_fr);
    initCosto(&cEvocar_rs_fr);

    //==========estructuras==========
    RA RACuadratico[MRAC], RALineal[MRAL];
    RS RSeparado[MRS];
    initRA( RACuadratico, MRAC );
    initRA( RALineal, MRAL);
    initRS( RSeparado, MRS );

    //==========variables==========

    while (SISTEMA)
    {
        system("cls");
        if( mostrar_menu() == -1 ){
            printf("============================================================\n");
            printf("\tError: archivo \"menu.txt\" no encontrado.\n");
            enter();
            return -1;
        }
        scanf("%99s", comando_user);
        getchar();
        if (strlen(comando_user) != 1){
            printf("============================================================\n");
            printf("\t Error: opcion invalido\n");
            enter();
            continue;
        }

        switch (comando_user[0]){
            case '1':{
                system("cls");
                mostrarRA(RALineal, MRAL);
                enter();
                break;
            } // mostrar estructura RAL
            case '2': {
                system("cls");
                mostrarRA(RACuadratico, MRAC);
                enter();
                break;
            }// mostrar estructura RAC
            case '3':{
                system("cls");
                mostrarRS(RSeparado, MRS);
                enter();
                break;
            } // mostrar estructura RS
            case '4': {
                //controlar si carga bien los datos
                system("cls");
                if( cargarEstructura( RACuadratico, RALineal, RSeparado ) != 0) {
                    printf("============================================================\n");
                    printf("\tHubo error en la carga de datos!\n");
                    enter();
                    break;
                }else{
                    printf("============================================================\n");
                    printf("\tCarga de datos con exito!\n");
                    mostrarTablaCostos();
                    enter();
                }
                system("cls");

                // pedir al usuario datos del elector
                elector aConsultar;
                initElector(&aConsultar);
                printf("============================================================\n");
                printf("Ingrese el DNI del elector:\nusuario-> ");
                if (scanf("%d", &aConsultar.dni) != 1) {
                    aConsultar.dni = -1;
                }
                while (getchar() != '\n'); // Limpia el salto de linea para que enter() funcione correctamente

                system("cls");
                // elector aConsultar pero solo dni

                bool exito_rac, exito_ral, exito_rs;
                elector erac, eral, ers;
                initElector(&erac); initElector(&eral); initElector(&ers);

                // costo para buscar elector aConsultar en RAC
                int costoRAC = evocarRAC(RACuadratico, aConsultar, &exito_rac, &erac);
                int costoRAL = evocarRAL(RALineal, aConsultar, &exito_ral, &eral);
                int costoRS  = evocarRS(RSeparado, aConsultar, &exito_rs, &ers);

                printf("============================================================\n");
                printf("\tCONSULTA DE UN ELECTOR DADO\n");
                printf("============================================================\n");
                printf("DNI consultado: %d\n", aConsultar.dni);
                lineaTabla('-', 60);

                printf("| %-12s | %-8s | %-10s | %-14s |\n",
                    "ESTRUCTURA", "EXITO", "COSTO", "RESULTADO");
                lineaTabla('-', 60);
                printf("| %-12s | %-8s | %-10d | %-14s |\n",
                    "RAL",  exito_ral ? "SI" : "NO", costoRAL, exito_ral ? "encontrado" : "no existe");
                printf("| %-12s | %-8s | %-10d | %-14s |\n",
                    "RAC", exito_rac ? "SI" : "NO", costoRAC, exito_rac ? "encontrado" : "no existe");
                printf("| %-12s | %-8s | %-10d | %-14s |\n",
                    "RS",    exito_rs  ? "SI" : "NO", costoRS,  exito_rs  ? "encontrado" : "no existe");
                lineaTabla('-', 60);
                if (exito_ral){
                    printf("============================================================\n");
                    printf("\tELECTOR REGISTRADO EN REBALSE ABIERTO LINEAL\n");
                    printf("============================================================\n");
                    elector_mostrar(eral);
                }

                if (exito_rac) {
                    printf("============================================================\n");
                    printf("\tELECTOR REGISTRADO EN REBALSE ABIERTO CUADRATICO\n");
                    printf("============================================================\n");
                    elector_mostrar(erac);
                }

                if (exito_rs){
                    printf("============================================================\n");
                    printf("\tELECTOR REGISTRADO EN REBALSE SEPARADO\n");
                    printf("============================================================\n");
                    elector_mostrar(ers);
                }

                enter();
                break;
            } // comparar estructuras
            case '0':{
                SISTEMA = false;
                liberarRS(RSeparado, MRS); // Liberamos memoria de la estructura dinámica
                break;
            }
            default:{
                printf("============================================================\n");
                printf("\t Error: opcion invalido\n");
                enter();
                continue;
            }
        } // switch
    } // while
    return 0;
} // main

int mostrar_menu(void){
    FILE *menu = fopen("menu.txt", "r");
    if (menu == NULL)
        return -1;

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), menu) != NULL)
    {
        printf("%s", buffer);
    }
    fclose(menu);
    return 0;
}

void enter(){
    printf("============================================================\n");
    printf("\tPresionar \"enter\" para continuar\n");
    printf("============================================================\n");
    getchar();
}

int cargarEstructura(RA rac[], RA ral[], RS rs[]){
    FILE *operaciones = fopen("Operaciones_Padron.txt", "r");
    if (operaciones == NULL) return -1;

    // Reinicializamos estructuras estáticas y dinámicas por si se carga más de una vez
    initRA(rac, MRAC);
    initRA(ral, MRAL);
    liberarRS(rs, MRS);
    initRS(rs, MRS);

    // Reinicializamos contadores de costos para no acumular sobre una carga previa
    initCosto(&cAlta_rac_ex); initCosto(&cAlta_ral_ex); initCosto(&cAlta_rs_ex);
    initCosto(&cBaja_rac_ex); initCosto(&cBaja_ral_ex); initCosto(&cBaja_rs_ex);
    initCosto(&cEvocar_rac_ex); initCosto(&cEvocar_ral_ex); initCosto(&cEvocar_rs_ex);
    initCosto(&cAlta_rac_fr); initCosto(&cAlta_ral_fr); initCosto(&cAlta_rs_fr);
    initCosto(&cBaja_rac_fr); initCosto(&cBaja_ral_fr); initCosto(&cBaja_rs_fr);
    initCosto(&cEvocar_rac_fr); initCosto(&cEvocar_ral_fr); initCosto(&cEvocar_rs_fr);


    //variables
    float costo=0.0f;
    // resultado de cada operacion
    elector e_temp;
    // elector reutilizable
    elector e_result;
    // elector para evocar
    int itemp = 0;
    // guarda los DNI, codigo postal, etc.
    char nam[51], dom[81];
    // guarda nombre y domicilio
    bool exito;

    int comando = 0;
    while (fscanf(operaciones, "%d", &comando) == 1){
        initElector(&e_temp);
        exito = false;

        if ((comando == 1) || (comando == 2)){
            fscanf(operaciones, "%d", &itemp);
            e_temp.dni = itemp;
            fscanf(operaciones, " %50[^\n]", nam);
            for(int c = 0; nam[c] != '\0'; c++) {
                nam[c] = (char)tolower((unsigned char)nam[c]);
            }//todo a minuscula
            strcpy(e_temp.nombreApellido, nam);
            fscanf(operaciones, " %80[^\n]", dom);
            for(int c = 0; dom[c] != '\0'; c++) {
                dom[c] = (char)tolower((unsigned char)dom[c]);
            }//todo a minuscula
            strcpy(e_temp.domicilio, dom);
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

        switch (comando){
            case 1:{
                // RAL alta
                costo = altaRAL(ral, e_temp, &exito);
                if (exito) acumular(&cAlta_ral_ex, costo);
                else       acumular(&cAlta_ral_fr, costo);

                // RAC alta
                costo = altaRAC(rac, e_temp, &exito);
                if (exito) acumular(&cAlta_rac_ex, costo);
                else       acumular(&cAlta_rac_fr, costo);

                // RS alta
                costo = altaRS(rs, e_temp, &exito);
                if (exito) acumular(&cAlta_rs_ex, costo);
                else       acumular(&cAlta_rs_fr, costo);

                break;
            }
            case 2:{
                // RAL baja
                costo = bajaRAL(ral, e_temp, &exito);
                if (exito) acumular(&cBaja_ral_ex, costo);
                else       acumular(&cBaja_ral_fr, costo);

                // RAC baja
                costo = bajaRAC(rac, e_temp, &exito);
                if (exito) acumular(&cBaja_rac_ex, costo);
                else       acumular(&cBaja_rac_fr, costo);

                // RS baja
                costo = bajaRS(rs, e_temp, &exito);
                if (exito) acumular(&cBaja_rs_ex, costo);
                else       acumular(&cBaja_rs_fr, costo);

                break;
            }
            case 3:{
                // RAL evocar
                costo = evocarRAL(ral, e_temp, &exito, &e_result);
                if (exito) acumular(&cEvocar_ral_ex, costo);
                else       acumular(&cEvocar_ral_fr, costo);

                // RAC evocar
                costo = evocarRAC(rac, e_temp, &exito, &e_result);
                if (exito) acumular(&cEvocar_rac_ex, costo);
                else       acumular(&cEvocar_rac_fr, costo);

                // RS evocar
                costo = evocarRS(rs, e_temp, &exito, &e_result);
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
