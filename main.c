#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "LSOBB.h"
#include "ABB.h"

int mostrar_menu(void);
void enter(void);

int preload(LSOBB*, ABB*); // esperando mas estructuras @Alts

//===========definicion de estructura costo====

typedef struct{
    float mayor, promedio;
    float tR;/*total_operacion_realizado*/
    float tA;/*total_acumulado*/
}costo;

void initCosto(costo *l){
    l->mayor=0.0f;
    l->promedio=0.0f;
    l->tA=0.0f;
    l->tR=0.0f;
}
//==========costos de cada una==========
costo cAlta_lsobb, cBaja_lsobb, cEvocar_lsobb;
costo cAlta_lvo, cBaja_lvo, cEvocar_lvo;
costo cAlta_abb, cBaja_abb, cEvocar_abb;

int main(){
    // menu
    bool SISTEMA = true;
    char comando_user[100];

    //==========init costos==========
    initCosto(&cAlta_lsobb);
    initCosto(&cAlta_lvo);
    initCosto(&cAlta_abb);
    initCosto(&cBaja_lsobb);
    initCosto(&cBaja_lvo);
    initCosto(&cBaja_abb);
    initCosto(&cEvocar_lsobb);
    initCosto(&cEvocar_lvo);
    initCosto(&cEvocar_abb);

    //==========estructuras==========
    LSOBB lista_secuencial_ordenada;
    initLSOBB(&lista_secuencial_ordenada);

    ABB arbol_binario_busqueda;
    initABB(&arbol_binario_busqueda);

    //==========precargas==========
    if( preload(&lista_secuencial_ordenada,&arbol_binario_busqueda) ==-1 ){
        printf("============================================================\n");
        printf("\tError: archivo \"Operaciones_Padron.txt\" no encontrado.\n");
        enter();
        return -1;
    }
    enter();

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
                int i;
                elector e_temp;

                for (i = 0; i < lista_secuencial_ordenada.cantidad; i++){
                    initElector(&e_temp);
                    e_temp = lista_secuencial_ordenada.datos[i];
                    printf("------------------------------------------------------------\n");
                    printf("DNI:\t%d\n", e_temp.dni);
                    printf("Nombre:\t%s\n", e_temp.nombreApellido);
                    printf("Domicilio:\t%s\n", e_temp.domicilio);
                    printf("Codigo Postal:\t %d\n", e_temp.cPostal);
                    printf("Mesa de votacion: %d\n", e_temp.mesa);
                    printf("Circuito:\t%d\n", e_temp.circuito);
                    if( ((i+1) % 20) == 0) enter();
                }
                printf("------------------------------------------------------------\n");
                printf("Total: %d electores\n", lista_secuencial_ordenada.cantidad);
                enter();
                break;
            } // mostrar estructura LSOBB
            case '2':{
                break;
            } // mostrar estructura LVO
            case '3':{
                break;
            } // mostrar estructura ABB
            case '4':{
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

int preload(LSOBB *lsobb, ABB *abb){
    FILE *operaciones = fopen("Operaciones_Padron.txt", "r");
    if (operaciones == NULL) return -1; // archivo no encontrado

    //variables
    elector e_temp;
    int itemp = 0;
    // guarda los DNI, codigo postal, etc.
    char nam[51], dom[81];
    // guarda nombre y domicilio
    bool exito;


    int comando = 0;
    while (fscanf(operaciones, "%d", &comando) == 1){
            // reset estado de variables necesarios
            initElector( &e_temp);
            exito = false;

            // cargar datos
            if( (comando==1) || (comando == 2) ){
                fscanf(operaciones, "%d", &itemp);
                setDNI(&e_temp, itemp);
                fscanf(operaciones, " %[^\n]", nam);
                setNombreApellido(&e_temp, nam);
                fscanf(operaciones, " %[^\n]", dom);
                setDomicilio(&e_temp, dom);
                fscanf(operaciones, "%d", &itemp);
                setCPostal(&e_temp, itemp);
                fscanf(operaciones, "%d", &itemp);
                setMesa(&e_temp, itemp);
                fscanf(operaciones, "%d", &itemp);
                setCircuito(&e_temp, itemp);
            }else{
                fscanf(operaciones, "%d", &itemp);
                setDNI(&e_temp, itemp);
            }

        switch (comando){
            case 1:{

                // LSOBB
                float costo = altaLSO(lsobb, e_temp, &exito);
                cAlta_lsobb.tR += 1.0f;
                cAlta_lsobb.tA += costo;
                if (costo > cAlta_lsobb.mayor) cAlta_lsobb.mayor = costo;

    // ABB
    costo = altaABB(abb, e_temp, &exito);
    cAlta_abb.tR += 1.0f;
    cAlta_abb.tA += costo;
    if (costo > cAlta_abb.mayor) cAlta_abb.mayor = costo;

                break;
                }
            case 2:{
                cBaja_lsobb.tR+=1.0f;
                cBaja_lvo.tR+=1.0f;
                cBaja_abb.tR+=1.0f;


                break;
            }
            case 3:{
                cEvocar_lsobb.tR+=1.0f;
                cEvocar_lvo.tR+=1.0f;
                cEvocar_abb.tR+=1.0f;


                break;
            }
        }
    }
    fclose(operaciones);
    return 0;
}
