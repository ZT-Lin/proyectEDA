/*Consideraciones a tener en cuenta:
El número estimado de electores en el archivo es de 2000.
Las listas deber´an estar ordenadas de menor a mayor respecto del D.N.I..
Para la lista secuencial, en la b´usqueda binaria la consigna a utilizar ser´a bisecci´on, l´ımite inferior inclusivo, l´ımi-
te superior inclusivo, testigo a izquierda y segmento mas grande a la izquierda. Para ella no se utilizar´a ning´un
elemento ficticio para indicar inicio o fin de lista.
La confirmaci´on de la baja en la rutina de baja debe realizarse por c´odigo, es decir comparando toda la nupla (en
todas las estructuras) .
La politica de reemplazo en la baja de los ´Arboles cuando el nodo tiene dos hijos es el menor de los mayores y el
reemplazo deber´a realizarse con copia de datos.
El valor utilizado como +infinito en LVO es el n´umero 999.999.999.
El D.N.I. es un entero.
El campo Nombre y apellido es una secuencia de hasta 50 caracteres.
El campo domicilio es una secuencia de hasta 80 caracteres.
El C´odigo Postal es un entero.
El N´umero de mesa es un entero.
El Circuito es un entero.
El ingreso de datos no debe ser sensible a may ´usculas y min ´usculas, esto significa por ejemplo que SOSA = SoSa
= sosa.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "LSOBB.h"

#define MAX_NOMBRE 51
#define MAX_DOM 81
#define EST_ELECTORES 2000 /*Electores estimados*/
#define INFINITO_LVO 99999999 

void mostrar_menu(void);
void enter(void);

int preload(LSOBB *); // esperando mas estructuras @Alts

int main(){
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
            printf("============================================================\n");
            printf("\t\t opcion invalido\n");
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
            printf("============================================================\n");
            printf("\t\t opcion invalido\n");
            enter();
            continue;
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




typedef struct {
    long dni;
    char nombreApellido[MAX_NOMBRE];
    char domicilio[MAX_DOM];
    int cp;
    int mesa;
    int circuito;
} Elector;

typedef struct {
    double costoAlta;
    double costoBaja;
    double costoConsultas;
    int altasBien, altasMal, BajarBien, BajasMal, ConsultasBien, ConsultasMal;
} Costos;

/*Lista Vinculada Ordenada con terminaci´on dada por contenido (+ infinito) (LVO)*/

typedef struct NodoLVO{
    Elector dato;
    struct NodoLVO *sig;
} NodoLVO;

NodoLVO *crearLVO(void){
    NodoLVO *centinela = (NodoLVO*)malloc(sizeof(NodoLVO));
    centinela ->dato.dni = INFINITO_LVO;
    centinela->dato.nombreApellido = /*buscar que caracter poner aca*/
    centinela->dato.domicilio = /*same*/
    centinela->dato.cp = 0;
    centinela->dato.mesa = 0;
    centinela->dato.circuito = 0;
    centinela->sig = NULL;
    return centinela;
}


/*Lista Secuencial Ordenada con b´usqueda binaria (LSOBB)*/
typedef struct {
    Elector electores[EST_ELECTORES];
    int cant;
}



 void initLVO() {
    lvo_head = (NodoLVO*)malloc(sizeof(NodoLVO));
    lvo_head->elector.dni = INFINITO_LVO;
    lvo_head->sig = NULL;
 }

 void altaLVO(NodoLVO lista, Elector e, double *costo) {
    NodoLVO *ant = NULL;
    NodoLVO *act = *lista;
     
    while (act ->dato.dni == e.dni)
    {
        return 0;
    }

    NodoLVO *nuevo = (NodoLVO*) malloc(sizeof(NodoLVO))
    nuevo->dato = e;

    nuevo -> sig = act;
    (*costo) += 0.5;

    if(ant == NULL){
        *lista = nuevo;
    } else {
        ant ->sig = nuevo;
    }
    (costo*) += 0.5;

    
 }

 void bajaLVO(Elector e){
    NodoLVO *actual = lvo_head, *ant = NULL;
    while (actual ->elector.dni < e.dni){
        ant = actual;
        actual = actual->sig;
    }
    if (actual->elector.dni == e.dni && son_iguales(actual->elector, e)){
        if (ant == NULL) lvo_head = actual ->sig;
        else ant -> sig = actual ->sig;

        costo_bajas_lvo += 0.5;
        free(actual)
    }
 }

 void evocarLVO(int dni){
    NodoLV* actual = lvo_head;
    while (actual->elector.dni < dni){
        costo_consultas_lvo += 1.0;
        actual = actual->sig;
    }
    costo_consultas_lvo += 1.0;
 }



















 /*Arbol Binario de B´usqueda (ABB).*/
typedef struct NodoABB{
    Elector elector;
    struct NodoABB *izq; 
    struct NodoABB *dere;
} NodoABB;

 float costo_altas_lvo = 0, costo_bajas_lvo= 0, costo_consulta_lvo = 0;
 float costo_altas_lsobb = 0, costo_bajas_lsobb= 0, costo_consulta_lsobb = 0;
 float costo_altas_abb = 0, costo_bajas_abb= 0, costo_consulta_abb = 0;

 /*Hacer el coso para que no se repitan los dni. Acordate Valen o Lin*/