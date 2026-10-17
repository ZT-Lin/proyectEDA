/*
====== GRUPO 41 =======
Correa Valentin, Lin Franco.
====================


====================FUNCION DE COSTOS====================

cantidad de celdas consultadas para realizar dicha operación en cada una de las estructuras
un punto (1) por cada celda.

============COMPARACION DE ESTRUCTURAS============
==============================================
*/

<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
=======


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a
#include <stdbool.h>
#include <ctype.h>

#include "RAC.h"
#include "RAL.h"
<<<<<<< HEAD
#include "RS.h"
#include "costo.h"
#include "elector.h"
#include "funcionHashing.h"
=======
#include"RS.h"
#include "costo.h"
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a

int mostrar_menu(void);
void enter(void);

<<<<<<< HEAD
int cargarEstructura(RA[], RA[], RS[]);
=======
int cargarEstructura(RA[], RA[]);
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a

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
<<<<<<< HEAD
    bloqueCostos("ALTA FRACASO",   &cAlta_ral_fr,   &cAlta_rac_fr,   &cAlta_rs_fr);
=======
    bloqueCostos("ALTA FRACASO",     &cAlta_ral_fr,   &cAlta_rac_fr,   &cAlta_rs_fr);
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a
    lineaTabla('-', 95);

    bloqueCostos("BAJA EXITO",     &cBaja_ral_ex,   &cBaja_rac_ex,   &cBaja_rs_ex);
    lineaTabla('-', 95);
<<<<<<< HEAD
    bloqueCostos("BAJA FRACASO",   &cBaja_ral_fr,   &cBaja_rac_fr,   &cBaja_rs_fr);
=======
    bloqueCostos("BAJA FRACASO",     &cBaja_ral_fr,   &cBaja_rac_fr,   &cBaja_rs_fr);
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a
    lineaTabla('-', 95);

    bloqueCostos("EVOCAR EXITO",   &cEvocar_ral_ex, &cEvocar_rac_ex, &cEvocar_rs_ex);
    lineaTabla('-', 95);
    bloqueCostos("EVOCAR FRACASO", &cEvocar_ral_fr, &cEvocar_rac_fr, &cEvocar_rs_fr);
    lineaTabla('=', 95);
}


int main(){
    // menu
    bool SISTEMA = true, ESTRUCTURA_CARGADO = false;
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
<<<<<<< HEAD
    RS RSeparado[MRS];
    initRA( RACuadratico, MRAC );
    initRA( RALineal, MRAL);
    initRS( RSeparado, MRS );
=======
    initRA( RACuadratico, MRAC );
    initRA( RALineal, MRAL);
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a

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
                if( ESTRUCTURA_CARGADO ){
                    mostrarRA(RALineal, MRAL);
                }else{
                    printf("============================================================\n");
                    printf("\t REBALSE ABIERTO LINEAL NO ESTA CARGADO!\n");
                }
                enter();
                break;
            } // mostrar estructura RAL
            case '2': {
                system("cls");
                if( ESTRUCTURA_CARGADO ){
                    mostrarRA(RACuadratico, MRAC);
                }else{
                    printf("============================================================\n");
                    printf("\t REBALSE ABIERTO CUADRATICO NO ESTA CARGADO!\n");
                }
                enter();
                break;
            }// mostrar estructura RAC
            case '3':{
<<<<<<< HEAD
                system("cls");
                if( ESTRUCTURA_CARGADO ){
                    mostrarRS(RSeparado, MRS);
                }else{
                    printf("============================================================\n");
                    printf("\t REBALSE SEPARADO NO ESTA CARGADO!\n");
                }
                enter();
=======
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a
                break;
            } // mostrar estructura RS
            case '4': {
                //controlar si carga bien los datos
                system("cls");
<<<<<<< HEAD
                if( cargarEstructura( RACuadratico, RALineal, RSeparado ) != 0) {
=======
                if( cargarEstructura(  RACuadratico, RALineal ) != 0) {
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a
                    printf("============================================================\n");
                    printf("\tHubo error en la carga de datos!\n");
                    enter();
                    break;
                }else{
                    printf("============================================================\n");
                    printf("\tCarga de datos con exito!\n");
                    ESTRUCTURA_CARGADO = true;
                    mostrarTablaCostos();
                    enter();
                }
                system("cls");

                // pedir al usuario datos del elector
                elector aConsultar;
                initElector(&aConsultar);
                printf("============================================================\n");
                printf("Ingrese el DNI del elector:\nusuario-> ");
<<<<<<< HEAD
                if (scanf("%d", &aConsultar.dni) != 1) {
                    aConsultar.dni = -1;
                }
                while (getchar() != '\n'); // Limpia el salto de linea para que enter() funcione correctamente
=======
                scanf("%d", &aConsultar.dni);
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a

                enter();
                system("cls");
                // elector aConsultar pero solo dni

                bool exito_rac, exito_ral, exito_rs;
                elector erac, eral, ers;
                initElector(&erac); initElector(&eral); initElector(&ers);

                // costo para buscar elector aConsultar en RAC
                int costoRAC = evocarRAC(RACuadratico, aConsultar, &exito_rac, &erac);
                int costoRAL = evocarRAL(RALineal, aConsultar, &exito_ral, &eral);
<<<<<<< HEAD
                int costoRS  = evocarRS(RSeparado, aConsultar, &exito_rs, &ers);
=======
                //int costoRS   = evocarRS(RSeparado, aConsultar, &exito_rs, &ers);
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a

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
<<<<<<< HEAD
                printf("| %-12s | %-8s | %-10d | %-14s |\n",
                    "RS",    exito_rs  ? "SI" : "NO", costoRS,  exito_rs  ? "encontrado" : "no existe");
=======
                /*printf("| %-12s | %-8s | %-10d | %-14s |\n",
                    "RS",    exito_rs  ? "SI" : "NO", costoRS,  exito_rs  ? "encontrado" : "no existe");*/
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a
                lineaTabla('-', 60);
                printf("============================================================\n");
                printf("\tELECTOR REGISTRADO EN REBALSE ABIERTO LINEAL\n");
                printf("============================================================\n");
<<<<<<< HEAD
                if (exito_ral) elector_mostrar(eral);
=======
                elector_mostrar(eral);
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a

                printf("============================================================\n");
                printf("\tELECTOR REGISTRADO EN REBALSE ABIERTO CUADRATICO\n");
                printf("============================================================\n");
<<<<<<< HEAD
                if (exito_rac) elector_mostrar(erac);

                printf("============================================================\n");
                printf("\tELECTOR REGISTRADO EN REBALSE SEPARADO\n");
                printf("============================================================\n");
                if (exito_rs) elector_mostrar(ers);

                enter();
                break;
            } // comparar estructuras
            case '0':{
                SISTEMA = false;
                liberarRS(RSeparado, MRS); // Liberamos memoria de la estructura dinámica
=======
                elector_mostrar(erac);

                /*printf("============================================================\n");
                printf("\tELECTOR REGISTRADO EN REBALSE SEPARADO\n");
                printf("============================================================\n");
                elector_mostrar(ers);*/

                enter();
                break;
        } // comparar estructuras
            case '0':{
                SISTEMA = false;
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a
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

<<<<<<< HEAD
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
=======
int cargarEstructura(RA rac[], RA ral[]){
    FILE *operaciones = fopen("Operaciones_Padron.txt", "r");
    if (operaciones == NULL) return -1;

   //variables
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a
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
<<<<<<< HEAD
            fscanf(operaciones, " %50[^\n]", nam);
=======
            fscanf(operaciones, " %[^\n]", nam);
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a
            for(int c = 0; nam[c] != '\0'; c++) {
                nam[c] = (char)tolower((unsigned char)nam[c]);
            }//todo a minuscula
            strcpy(e_temp.nombreApellido, nam);
<<<<<<< HEAD
            fscanf(operaciones, " %80[^\n]", dom);
=======
            fscanf(operaciones, " %[^\n]", dom);
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a
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
                if (exito){
                    acumular(&cAlta_ral_ex, costo);
                } else {
                    acumular(&cAlta_ral_fr, costo);
                }
                // RAC alta
                costo = altaRAC(rac, e_temp, &exito);
                if (exito){
                    acumular(&cAlta_rac_ex, costo);
                } else {
                    acumular(&cAlta_rac_fr, costo);
                }
<<<<<<< HEAD
                // RS alta
                costo = altaRS(rs, e_temp, &exito);
                if (exito){
                    acumular(&cAlta_rs_ex, costo);
                } else {
                    acumular(&cAlta_rs_fr, costo);
                }
=======
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a

                break;
            }
            case 2:{
                // RAL baja
                costo = bajaRAL(ral, e_temp, &exito);
                if (exito){
                    acumular(&cBaja_ral_ex, costo);
                } else {
                    acumular(&cBaja_ral_fr, costo);
                }
                // RAC baja
                costo = bajaRAC(rac, e_temp, &exito);
                if (exito){
                    acumular(&cBaja_rac_ex, costo);
                } else {
                    acumular(&cBaja_rac_fr, costo);
                }
<<<<<<< HEAD
                // RS baja
                costo = bajaRS(rs, e_temp, &exito);
                if (exito){
                    acumular(&cBaja_rs_ex, costo);
                } else {
                    acumular(&cBaja_rs_fr, costo);
                }
=======
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a
                break;
            }
            case 3:{
                // RAL evocar
                costo = evocarRAL(ral, e_temp, &exito, &e_result);
                if (exito){
                    acumular(&cEvocar_ral_ex, costo);
                } else {
                    acumular(&cEvocar_ral_fr, costo);
                }
                // RAC evocar
                costo = evocarRAC(rac, e_temp, &exito, &e_result);
                if (exito){
                    acumular(&cEvocar_rac_ex, costo);
                } else {
                    acumular(&cEvocar_rac_fr, costo);
                }
<<<<<<< HEAD
                // RS evocar
                costo = evocarRS(rs, e_temp, &exito, &e_result);
                if (exito){
                    acumular(&cEvocar_rs_ex, costo);
                } else {
                    acumular(&cEvocar_rs_fr, costo);
                }
=======
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a
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

<<<<<<< HEAD
    promedio(&cAlta_rs_ex);
=======
    /*promedio(&cAlta_rs_ex);
>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a
    promedio(&cBaja_rs_ex);
    promedio(&cEvocar_rs_ex);
    promedio(&cAlta_rs_fr);
    promedio(&cBaja_rs_fr);
<<<<<<< HEAD
    promedio(&cEvocar_rs_fr);
    
    fclose(operaciones);
    return 0;
}
=======
    promedio(&cEvocar_rs_fr);*/
    fclose(operaciones);
    return 0;
}

>>>>>>> 6feb72da2a7ae696b1247743b2c470d587e9e00a
