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







/*Cositas generales y funciones funcionales y utilidades utiles*/




//Comparar si es el mismo elector
int mismoElector(const Elector *a, const Elector *b){
    return a->dni == b->dni &&
    strcasecmp(a->nombreApellido, b->nombreApellido) == 0 &&
    strcasecmp(a->domicilio, b->domicilio) == 0 &&
    a-> cp == b -> cp &&
    a->mesa == b -> mesa &&
    a->circuito == b -> circuito;
}
//Imprimir los datos del Elector
void imprimirElector(const Elector e){
    printf("DNI: %-9ld | %-30s | %-30s |CP:%-5d |Mesa: %.4d |Circuito: %-4\n", e->dni,e->nombre,e->domicilio,e->cp,e->mesa,e->circuito);
}

//Para comparar strings
int strcasecmp(const char *a, const char *b){
    while (*a !=  '\0' && *b != '\0'){
        int ca = tolower((unsigned char) *a);
        int cb = tolower((unsigned char) *b);
        if (ca != cb) {
            return ca-cb
        }
    }
    return (unsigned char) *a - (unsigned char) *b;
}


/*Añadir mas cositas xd*/






/*Lista Secuencial Ordenada con b´usqueda binaria (LVO)*/
typedef struct {
    Elector electores[EST_ELECTORES];
    int cant;
}




 /*Arbol Binario de B´usqueda (ABB).*/
typedef struct NodoABB{
    Elector elector;
    struct NodoABB *izq; 
    struct NodoABB *der;
} NodoABB;

NodoABB crearNodoABB(Elector e){
    NodoABB *n = (NodoABB *)malloc(sizeof(NodoABB))
    n->dato = e;
    n->izq = NULL;
    n->der = NULL;
    return n;
}


//Lo hago recursivo como recomendacion del Tansi
int insertarABB(NodoABB raiz, Elector e, double costo){
    if(*raiz == NULL){
        *raiz = crearNodoABB(e);
        (*costo) += 0.5;
        return 1; //SI se inserto bien, da 1
    }
    if (e.dni == (*raiz)->dato.dni){
        return 0; //Devuelve 0 si esta DUPLICADO
    } else if (e.dni < (*raiz)->dato.dni){
        return insertarABB(&(*raiz)->izq,e,costo);
    }else {
        return insertarABB(&(*raiz)->der,e,costo);
    }
}


//Me ayudo gemini en este porque se me trabo el cerebro kkk
int bajaABB(NodoABB **raiz, Elector e, double *costo) {
    if (*raiz == NULL)
        return 0;
 
    if (e.dni < (*raiz)->dato.dni)
        return bajaABB(&(*raiz)->izq, e, costo);
    if (e.dni > (*raiz)->dato.dni)
        return bajaABB(&(*raiz)->der, e, costo);
 
    /* encontramos el DNI, confirmamos con toda la tupla */
    if (!esMismoElector((*raiz)->dato, e))
        return 0;
 
    NodoABB *borrar = *raiz;
 
    if ((*raiz)->izq == NULL && (*raiz)->der == NULL) {
        *raiz = NULL;
        *costo += 0.5;
        free(borrar);
    } else if ((*raiz)->izq == NULL) {
        *raiz = (*raiz)->der;
        *costo += 0.5;
        free(borrar);
    } else if ((*raiz)->der == NULL) {
        *raiz = (*raiz)->izq;
        *costo += 0.5;
        free(borrar);
    } else {
        /* dos hijos: buscamos el menor de los mayores */
        NodoABB *padre = *raiz;
        NodoABB *sucesor = (*raiz)->der;
        while (sucesor->izq != NULL) {
            padre = sucesor;
            sucesor = sucesor->izq;
        }
        (*raiz)->dato = sucesor->dato;
        *costo += 1; /* copia de datos */
 
        if (padre == *raiz)
            padre->der = sucesor->der;
        else
            padre->izq = sucesor->der;
        *costo += 0.5;
 
        free(sucesor);
    }
    return 1;
}

int consultaABB(NodoABB *raiz, long dni, Elector *result, double *costo) {
    NodoABB *act = raiz;
    while (act != NULL) {
        *costo += 1;
        if (dni == act->dato.dni) {
            *result = act->dato;
            return 1;
        }
        if (dni < act->dato.dni)
            act = act->izq;
        else
            act = act->der;
    }
    return 0;
}
void mostrarABBrecursi(NodoABB *raiz, int *cant) {
    if (raiz == NULL)
        return;
 
    imprimirElector(raiz->dato);
    (*cant)++;
 
    if (raiz->izq == NULL && raiz->der == NULL) {
        printf("sin hijos\n");
    } else {
        if (raiz->izq != NULL)
            printf("hijo izq: %ld\n", raiz->izq->dato.dni);
        else
            printf("sin hijo izq\n");
 
        if (raiz->der != NULL)
            printf("hijo der: %ld\n", raiz->der->dato.dni);
        else
            printf("sin hijo der\n");
    }
 
    mostrarABBrecursi(raiz->izq, cant);
    mostrarABBrecursi(raiz->der, cant);
}
 
void mostrarABB(NodoABB *raiz) {
    printf("\n-- ABB  --\n");
    int cant = 0;
    mostrarABBrec(raiz, &cant);
    printf("Total: %d\n", cant);
}
 
void liberarABB(NodoABB *raiz) {
    if (raiz == NULL) return;
    liberarABB(raiz->izq);
    liberarABB(raiz->der);
    free(raiz);
}




