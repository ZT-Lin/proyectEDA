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



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#include "RAC.h"
#include "RAL.h"
#include"RS.h"

int mostrar_menu(void);
void enter(void);

int preload();

//===========definicion de estructura costo====
typedef struct{
    float mayor, promedio;
    float realizado;/*total_operacion_realizado*/
    float acumulado;/*total_acumulado*/
}Costo;

void initCosto(Costo *l){
    l->mayor=0.0f;
    l->promedio=0.0f;
    l->acumulado=0.0f;
    l->realizado=0.0f;
}
//==========costos de cada una==========
Costo cAlta_rac_ex, cBaja_rac_ex, cEvocar_rac_ex;
Costo cAlta_rac_fr, cBaja_rac_fr, cEvocar_rac_fr;

Costo cAlta_lvo_ex, cBaja_lvo_ex, cEvocar_lvo_ex;
Costo cAlta_lvo_fr, cBaja_lvo_fr, cEvocar_lvo_fr;

Costo cAlta_abb_ex, cBaja_abb_ex, cEvocar_abb_ex;
Costo cAlta_abb_fr, cBaja_abb_fr, cEvocar_abb_fr;


//==========acumular costos==========
void acumular(Costo *c, float valor){
    c->realizado += 1.0f;
    c->acumulado += valor;
    if (valor > c->mayor)
        c->mayor = valor;
}

//==========calcular medio==========
void promedio(Costo *c){
    if(c->realizado !=0) {
            c->promedio = c->acumulado / c->realizado;
    }else{
        c->promedio = 0;
    }
}

int main(){
    // menu
    bool SISTEMA = true;
    char comando_user[100];

    //==========init costos(exito)==========
    initCosto(&cAlta_rac_ex);
    initCosto(&cAlta_lvo_ex);
    initCosto(&cAlta_abb_ex);

    initCosto(&cBaja_rac_ex);
    initCosto(&cBaja_lvo_ex);
    initCosto(&cBaja_abb_ex);

    initCosto(&cEvocar_rac_ex);
    initCosto(&cEvocar_lvo_ex);
    initCosto(&cEvocar_abb_ex);

    //==========init costos(fracaso)==========
    initCosto(&cAlta_rac_fr);
    initCosto(&cAlta_lvo_fr);
    initCosto(&cAlta_abb_fr);

    initCosto(&cBaja_rac_fr);
    initCosto(&cBaja_lvo_fr);
    initCosto(&cBaja_abb_fr);

    initCosto(&cEvocar_rac_fr);
    initCosto(&cEvocar_lvo_fr);
    initCosto(&cEvocar_abb_fr);

    //==========estructuras==========

    //==========variables==========

    while (SISTEMA)
    {
        system("cls");
        if( mostrar_menu() == -1 ){
            printf("============================================================\n");
            printf("\tError: archivo \"Operaciones_Padron.txt\" no encontrado.\n");
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
                break;
            } // mostrar estructura LSOBB
            case '2': {
                break;
            }// mostrar estructura LVO
            case '3':{
                break;
            } // mostrar estructura ABB
            case '4': {
                break;
        } // comparar estructuras
            case '0':{
                SISTEMA = false;
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
/**ESPERANDO RECONSTRUIR**/
/*
int preload(LSOBB *lsobb, ABB *abb, NodoLVO **lvo){
    FILE *operaciones = fopen("Operaciones_Padron.txt", "r");
    if (operaciones == NULL) return -1;

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
            fscanf(operaciones, " %[^\n]", nam);
            strcpy(e_temp.nombreApellido, nam);
            fscanf(operaciones, " %[^\n]", dom);
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
                // LSOBB alta
                costo = altaLSO(lsobb, e_temp, &exito);
                if (exito){
                    acumular(&cAlta_rac_ex, costo);
                } else {
                    acumular(&cAlta_rac_fr, costo);
                }

                // LVO alta
                int ok_lvo = 0;
                float costo_lvo = altaLVO(lvo, e_temp, &ok_lvo);
                if (ok_lvo) {
                    acumular(&cAlta_lvo_ex, costo_lvo);
                } else {
                    acumular(&cAlta_lvo_fr, costo_lvo);
                }

                // ABB alta
                costo = altaABB(abb, e_temp, &exito);
                if (exito){
                    acumular(&cAlta_abb_ex, costo);
                } else {
                    acumular(&cAlta_abb_fr, costo);
                }
                break;
            }
            case 2:{
                // LSOBB baja
                costo = bajaLSO(lsobb, e_temp, &exito);
                if (exito){
                    acumular(&cBaja_rac_ex, costo);
                } else {
                    acumular(&cBaja_rac_fr, costo);
                }

                // LVO baja
                int ok_lvo = 0;
                float costo_lvo = bajaLVO(lvo, e_temp, &ok_lvo);
                if (ok_lvo) {
                    acumular(&cBaja_lvo_ex, costo_lvo);
                } else {
                    acumular(&cBaja_lvo_fr, costo_lvo);
                }

                // ABB baja
                costo = bajaABB(abb, e_temp, &exito);
                if (exito){
                    acumular(&cBaja_abb_ex, costo);
                } else {
                    acumular(&cBaja_abb_fr, costo);
                }
                break;
            }
            case 3:{
                // LSOBB evocar
                costo = evocarLSO(*lsobb, e_temp, &exito, &e_result);
                if (exito){
                    acumular(&cEvocar_rac_ex, costo);
                } else {
                    acumular(&cEvocar_rac_fr, costo);
                }

                // LVO evocar
                int ok_lvo = 0;
                elector res_lvo;
                float costo_lvo = evocarLVO(*lvo, e_temp.dni, &res_lvo, &ok_lvo);
                if(e_temp.dni != VALOR_INFINITO){ //No contar el centinela basicamente
                    if (ok_lvo) {
                        acumular(&cEvocar_lvo_ex, costo_lvo);
                    } else {
                        acumular(&cEvocar_lvo_fr, costo_lvo);
                    }
                }

                // ABB evocar
                costo = evocarABB(abb, e_temp, &exito, &e_result);
                if (exito){
                    acumular(&cEvocar_abb_ex, costo);
                } else {
                    acumular(&cEvocar_abb_fr, costo);
                }
                break;
            }
        }
    }
    promedio(&cAlta_rac_ex);
    promedio(&cAlta_lvo_ex);
    promedio(&cAlta_abb_ex);
    promedio(&cBaja_rac_ex);
    promedio(&cBaja_lvo_ex);
    promedio(&cBaja_abb_ex);
    promedio(&cEvocar_rac_ex);
    promedio(&cEvocar_lvo_ex);
    promedio(&cEvocar_abb_ex);
    promedio(&cAlta_rac_fr);
    promedio(&cAlta_lvo_fr);
    promedio(&cAlta_abb_fr);
    promedio(&cBaja_rac_fr);
    promedio(&cBaja_lvo_fr);
    promedio(&cBaja_abb_fr);
    promedio(&cEvocar_rac_fr);
    promedio(&cEvocar_lvo_fr);
    promedio(&cEvocar_abb_fr);
    fclose(operaciones);
    return 0;
}*/
