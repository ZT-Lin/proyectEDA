#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "LSOBB.h"

void mostrar_menu(void);
void enter(void);

int preload(LSOBB *); // esperando mas estructuras @Alts

int main()
{
    // menu
    bool SISTEMA = true;
    char comando_user[100];

    // estructuras
    LSOBB lista_secuencial_ordenada;
    inicializarLSOBB(&lista_secuencial_ordenada);

    // precargas
    preload(&lista_secuencial_ordenada);
    enter();

    while (SISTEMA)
    {
        system("cls");
        mostrar_menu();
        scanf("%99s", comando_user);
        getchar();
        if (strlen(comando_user) != 1)
        {
            printf("mal ingresado\n");
            enter();
            continue;
        }

        switch (comando_user[0])
        {
        case '1':
        {
            int *i = (int *)malloc(sizeof(int));
            elector *e_temp = (elector*)malloc(sizeof(elector));

            for ((*i) = 0; (*i) < lista_secuencial_ordenada.cantidad; (*i)++)
            {
                inicializarElector(e_temp);
                *e_temp = lista_secuencial_ordenada.datos[*i];

                printf("------------------------------------------------------------\n");
                printf("DNI:\t%d\n", e_temp->dni);
                printf("Nombre:\t%s\n", e_temp->nombreApellido);
                printf("Domicilio:\t%s\n", e_temp->domicilio);
                printf("Codigo Postal:\t %d\n", e_temp->cPostal);
                printf("Mesa de votacion: %d\n", e_temp->mesa);
                printf("Circuito:\t%d\n", e_temp->circuito);
            }
            printf("------------------------------------------------------------\n");
            printf("Total: %d electores\n", lista_secuencial_ordenada.cantidad);
            enter();
            free(i);
            free(e_temp);
            break;
        } // mostrar estructura LSOBB
        case '2':
        {
            break;
        } // mostrar estructura LVO
        case '3':
        {
            break;
        } // mostrar estructura ABB
        case '4':
        {
            break;
        } // comparar estructuras
        case '0':
        {
            SISTEMA = false;
            break;
        }
        default:
        {
            break;
        }
        } // switch

    } // while
    return 0;
} // main

void mostrar_menu(void)
{
    FILE *menu = fopen("menu.txt", "r");
    if (menu == NULL)
        return;

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), menu) != NULL)
    {
        printf("%s", buffer);
    }
    fclose(menu);
}

void enter(){
    printf("============================================================\n");
    printf("\tPresionar \"enter\" para continuar\n");
    printf("============================================================\n");
    getchar();
}

int preload(LSOBB *lsobb)
{
    FILE *operaciones = fopen("Operaciones_Padron.txt", "r");
    if (operaciones == NULL)
        return -1; // archivo no encontrado

    //variables
    elector e_temp;
    int itemp = 0;
    // guarda los DNI, codigo postal, etc.
    char nam[51], dom[81];
    // guarda nombre y domicilio

    // leer el comando: 1-alta, 2-baja, 3-evocacion
    int comando = 0;
    while (fscanf(operaciones, "%d", &comando) == 1)
    {
        // asegurado que empieza con comando 1 2 3
        /*test / debug
        printf("------------------------------------------------------------\n");
        printf("Comando<%d>\n", comando);
        getchar();
        inicializarP(&e_temp);*/
        // resetear el elector

        switch (comando){
        case 1:{
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
            // orden segun pdf del proyecto
            /*test / debug
            printf("------------------------------------------------------------\n");
            printf("\t dar alta al elector con DNI: <%d>\n", getDNI(e_temp));
            getchar();*/

            // dar de alta en las estructuras
            altaLSO(lsobb, e_temp);
            break;
            }
        case 2:{
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
            // orden segun pdf del proyecto
            /*test / debug
            printf("------------------------------------------------------------\n");
            printf("\t dar baja al elector con DNI: <%d>\n", getDNI(e_temp));
            getchar();*/

            // dar de baja en las estructuras
            bajaLSO(lsobb, e_temp);
            break;
            }
        case 3:{
            fscanf(operaciones, "%d", &itemp);
            setDNI(&e_temp, itemp);
            /*test / debug
            printf("------------------------------------------------------------\n");
            printf("\t evocar al elector con DNI: <%d>\n", itemp);
            getchar();*/
            evocarLSO(*lsobb, e_temp);
            break;
            }
        }
    }
    fclose(operaciones);
    return 0;
}
