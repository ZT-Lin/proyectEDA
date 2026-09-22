/*
==================== GRUPO 41 =======Correa Valentin, Lin Franco. ====================


====================FUNCION DE COSTOS====================
    Alta y Baja:
        LSOBB: cantidad de corrimiento de la celda, costo = 1.
        ABB y LVO: modificacion de punteros, costo = 0.5

        La politica de reemplazo en la baja de los Arboles:
            cuando el nodo tiene dos hijos es el menor de los mayores y el
            reemplazo debera realizarse con copia de datos. se debera sumar
            un costo mas (1) por la copia de la tupla mas 0.5 por reenganchar.

    Evocar:
        todos: cantidad total de celdas consultadas, un punto (1) por cada celda.

====================ANALISIS====================
ALTA:
    LSOBB: una vez encontrado la posicion a insertar segun funcion LOCALIZAR,
        se realiza n veces el corrimiento de atras hacia adelante hasta el posicion
        que corresponde con FOR(iteracion). Luego, copia los datos.
        -En Promedio el alta nos da 413.07, y en el peor de los casos, 1932.0 corrimientos, por lo que
        el costo de este se incrementa demasiado para ser viable en grandes listas
        => pertenece a O(n)

    LVO:
        - Recorre secuencialmente nodo por nodo con un WHILE comparando DNIs hasta encontrar
        el lugar que mantenga el orden.
        - Una vez ubicado, solo se engancha el nodo nuevo modificando punteros (costo 0.5).
        - Por eso el costo queda fijo en 1.00 de promedio y 1.0 de maximo, sin importar donde caiga el DNI 
        dentro de la lista.
        => Pertenece a O(n).



    ABB:
        -Al hacer la busqueda vertical comparando el DNI con la funcion localizar, una vez encuentra al nodo padre, crea al nodo y lo engancha
        como un hijo izquierdo o derecho (Costo 0,5)
        -Como el recorrido para ubicar el lugar no suma costo, el resultado nos da fijo 0.50 de promedio
        y 0.5 de maximo, igual que en la LVO.
        => Pertenece a O(log2 n).



BAJA
    LSOBB:
        - Busca por biseccion y valida con elector_sonIguales
        - Al igual que con el alta, tiene que hacer muchos corrimientos cuando elimina algo tapandolos con un for
        lo que da un promedio de 502.61 y un maximo de 1893.0 corrimientos
        => Pertenece a O(n).
    LVO:
        - Avanza con el WHILE hasta dar con el DNI y coincidir la tupla.
        - Desenganchar y liberar el nodo cuesta solo 0.5 de puntero, y ese es el unico costo que queda:
        promedio en 0.50 y maximo en 0.5.
        => Pertenece a O(n).
    ABB:
        - Si no tiene hijos o solo tiene uno, se reacomodan con un costo de 0,5
        - Si tiene dos hijos, entonces busca al menor de los mayores, copia el registro y lo desengancha. 1(copiar) + 0,5(desenganchar)
        - En esta corrida no se dio ningun caso de nodo con dos hijos (o se conto enlace simple), por eso el promedio dio 0.50 y el maximo 0.5 
        quedaron en 0.50 (el peor caso teorico seria 1.50 si se diera el reemplazo).
        => Pertenece a O(1) estructural.

EVOCAR
    LSOBB:
        -Como es una biseccion pura, tiene limites inclusivos y el segmento mayor esta a la izquierda
        -En exito da un promedio de 12.14 y maximo de 13.0, mientras que en fracaso da 10.88 y maximo de 12.0 (no pasa nunca de 13 comparaciones)
        => Pertenece a O(log2 n),
    LVO:
        - Tiene una busqueda secuencial, recorre celda por celda hasta encontrar el DNI o cortar por orden con el centinela
        - Tiene un rendimiento bastante pobre: en exito promedia 566.80 con maximo de 1994.0, y en fracaso 463.47 con maximo de 1206.0
        => Pertenece a O(n).
    ABB:
        - Va comparando por rama izquierda o derecha segun el DNI.
        - Da casi los mismos numeros que la busqueda binaria del LSOBB: en exito promedio de 11.84 con maximo de 22.0, y en fracaso 12.03 con maximo de 21.0
        => Pertenece a O(log2 n).

==================== CONCLUSION ====================
LSOBB es buenisima para buscar (O(log2 n)), pero para un sistema real con altas y bajas no sirve
por el costo enorme de correr celdas en memoria contigua cada dos por tres.

LVO resulta tener costo estructural fijo para meter y sacar electores: enlazar o desenlazar un nodo es siempre barato 
(costo fijo de 0.5 a 1.0, sin importar el tamaño del padron). El problema aparece al evocar, donde al no
tener forma de hacer busqueda binaria, tiene que recorrer la lista celda por celda y el costo se dispara
a un promedio de 566.80 y picos de casi 2000 (1994.0),

ABB es claramente la mejor opcion de las tres para el padron: empata la velocidad de busqueda del LSOBB
(evocaciones con promedio 11.84 en exito y 12.03 en fracaso, frente a los 12.14 y 10.88 del LSOBB) 
y ademas mantiene el costo estructural de alta y baja tan bajo como la LVO (0.50 fijo), sin tener que desplazar nada
Es la estructura mas equilibrada y eficiente para el padron electoral entre las tres evaluadas.
==================================================
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#include "LSOBB.h"
#include "ABB.h"
#include "LVO.h"

int mostrar_menu(void);
void enter(void);

int preload(LSOBB*, ABB*); // esperando mas estructuras @Alts
void mostrarABB(NodoABB*, int*, int, int*);

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
Costo cAlta_lsobb_ex, cBaja_lsobb_ex, cEvocar_lsobb_ex;
Costo cAlta_lsobb_fr, cBaja_lsobb_fr, cEvocar_lsobb_fr;
Costo cAlta_lvo_ex, cBaja_lvo_ex, cEvocar_lvo_ex;
Costo cAlta_lvo_fr, cBaja_lvo_fr, cEvocar_lvo_fr;
Costo cAlta_abb_ex, cBaja_abb_ex, cEvocar_abb_ex;
Costo cAlta_abb_fr, cBaja_abb_fr, cEvocar_abb_fr;

NodoLVO *lista_lvo = NULL;

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

    //==========init costos==========
    initCosto(&cAlta_lsobb_ex);
    initCosto(&cAlta_lvo_ex);
    initCosto(&cAlta_abb_ex);
    initCosto(&cBaja_lsobb_ex);
    initCosto(&cBaja_lvo_ex);
    initCosto(&cBaja_abb_ex);
    initCosto(&cEvocar_lsobb_ex);
    initCosto(&cEvocar_lvo_ex);
    initCosto(&cEvocar_abb_ex);
    initCosto(&cAlta_lsobb_fr);
    initCosto(&cAlta_lvo_fr);
    initCosto(&cAlta_abb_fr);
    initCosto(&cBaja_lsobb_fr);
    initCosto(&cBaja_lvo_fr);
    initCosto(&cBaja_abb_fr);
    initCosto(&cEvocar_lsobb_fr);
    initCosto(&cEvocar_lvo_fr);
    initCosto(&cEvocar_abb_fr);

    //==========estructuras==========
    LSOBB lista_secuencial_ordenada;
    initLSOBB(&lista_secuencial_ordenada);

    lista_lvo = inicializar_lvo();

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

    //==========variables==========
    int total = 0;
    int pagina = 1;
    int i;
    elector e_temp;

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
                system("cls");
                pagina = 0;
                total = lista_secuencial_ordenada.cantidad;

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
                    if( ((i+1) % 20) == 0) {
                            pagina++;
                            printf("------------------------------------------------------------\n");
                            printf("pagina %d ( %d/%d)\n",pagina,i+1,total);
                            enter();
                            system("cls");
                    }
                }
                if (i % 20 != 0) {
                    printf("------------------------------------------------------------\n");
                    printf("Pagina %d | Mostrados: %d / %d\n", pagina, i, total);
                }
                printf("Total: %d electores\n", total);
                enter();
                break;
            } // mostrar estructura LSOBB
            case '2': {
                NodoLVO *aux = lista_lvo;
                int cant = 0, en_pag = 0;
                pagina = 0;
                system("cls");

                while (aux != NULL && aux->persona.dni != VALOR_INFINITO) {
                    printf("------------------------------------------------------------\n");
                    printf("DNI:\t%d\n", aux->persona.dni);
                    printf("Nombre:\t%s\n", aux->persona.nombreApellido);
                    printf("Domicilio:\t%s\n", aux->persona.domicilio);
                    printf("Codigo Postal:\t %d\n", aux->persona.cPostal);
                    printf("Mesa de votacion: %d\n", aux->persona.mesa);
                    printf("Circuito:\t%d\n", aux->persona.circuito);
                    cant++;
                    en_pag++;

                    if (en_pag == 20) {
                        pagina++;
                        printf("------------------------------------------------------------\n");
                        printf("pagina %d ( %d registros mostrados)\n", pagina, cant);
                        enter();
                        system("cls");
                        en_pag = 0;
                    }
                    aux = aux->siguiente;
                }
                printf("------------------------------------------------------------\n");
                printf("Total: %d electores en LVO\n", cant);
                enter();
                break;
            }// mostrar estructura LVO
            case '3':{
                system("cls");
                pagina = 0;
                i = 0;
                total = contarNodosABB(arbol_binario_busqueda.raiz);

                mostrarABB(arbol_binario_busqueda.raiz, &i, total, &pagina);
                if (i % 20 != 0) {
                    printf("------------------------------------------------------------\n");
                    printf("Pagina %d | Mostrados: %d / %d\n", pagina, i, total);
                }

                printf("Total: %d electores\n", total);
                enter();
                break;
            } // mostrar estructura ABB
            case '4': {
    system("cls");
    promedio(&cAlta_lsobb_ex);   promedio(&cAlta_lsobb_fr);
    promedio(&cBaja_lsobb_ex);   promedio(&cBaja_lsobb_fr);
    promedio(&cEvocar_lsobb_ex); promedio(&cEvocar_lsobb_fr);

    promedio(&cAlta_lvo_ex);     promedio(&cAlta_lvo_fr);
    promedio(&cBaja_lvo_ex);     promedio(&cBaja_lvo_fr);
    promedio(&cEvocar_lvo_ex);   promedio(&cEvocar_lvo_fr);

    promedio(&cAlta_abb_ex);     promedio(&cAlta_abb_fr);
    promedio(&cBaja_abb_ex);     promedio(&cBaja_abb_fr);
    promedio(&cEvocar_abb_ex);   promedio(&cEvocar_abb_fr);

    printf("\n");
    printf("  ============================================================================\n");
    printf("                          COMPARACION DE ESTRUCTURAS\n");
    printf("  ============================================================================\n\n");

    printf("  %-18s   %-20s   %-20s   %-20s\n", "", "LSOBB", "LVO", "ABB");
    printf("  %-18s   %-20s   %-20s   %-20s\n", "Operacion", "(Media / Maximo)", "(Media / Maximo)", "(Media / Maximo)");
    printf("  ----------------------------------------------------------------------------\n\n");

    printf("  -- ALTAS --\n");
    printf("  %-18s   %7.2f / %-9.1f   %7.2f / %-9.1f   %7.2f / %-9.1f\n",
        "Exito",
        cAlta_lsobb_ex.promedio, cAlta_lsobb_ex.mayor,
        cAlta_lvo_ex.promedio,   cAlta_lvo_ex.mayor,
        cAlta_abb_ex.promedio,   cAlta_abb_ex.mayor);
    printf("  %-18s   %7.2f / %-9.1f   %7.2f / %-9.1f   %7.2f / %-9.1f\n\n",
        "Fracaso",
        cAlta_lsobb_fr.promedio, cAlta_lsobb_fr.mayor,
        cAlta_lvo_fr.promedio,   cAlta_lvo_fr.mayor,
        cAlta_abb_fr.promedio,   cAlta_abb_fr.mayor);

    printf("  -- BAJAS --\n");
    printf("  %-18s   %7.2f / %-9.1f   %7.2f / %-9.1f   %7.2f / %-9.1f\n",
        "Exito",
        cBaja_lsobb_ex.promedio, cBaja_lsobb_ex.mayor,
        cBaja_lvo_ex.promedio,   cBaja_lvo_ex.mayor,
        cBaja_abb_ex.promedio,   cBaja_abb_ex.mayor);
    printf("  %-18s   %7.2f / %-9.1f   %7.2f / %-9.1f   %7.2f / %-9.1f\n\n",
        "Fracaso",
        cBaja_lsobb_fr.promedio, cBaja_lsobb_fr.mayor,
        cBaja_lvo_fr.promedio,   cBaja_lvo_fr.mayor,
        cBaja_abb_fr.promedio,   cBaja_abb_fr.mayor);

    printf("  -- EVOCACION --\n");
    printf("  %-18s   %7.2f / %-9.1f   %7.2f / %-9.1f   %7.2f / %-9.1f\n",
        "Exito",
        cEvocar_lsobb_ex.promedio, cEvocar_lsobb_ex.mayor,
        cEvocar_lvo_ex.promedio,   cEvocar_lvo_ex.mayor,
        cEvocar_abb_ex.promedio,   cEvocar_abb_ex.mayor);
    printf("  %-18s   %7.2f / %-9.1f   %7.2f / %-9.1f   %7.2f / %-9.1f\n",
        "Fracaso",
        cEvocar_lsobb_fr.promedio, cEvocar_lsobb_fr.mayor,
        cEvocar_lvo_fr.promedio,   cEvocar_lvo_fr.mayor,
        cEvocar_abb_fr.promedio,   cEvocar_abb_fr.mayor);

    printf("\n  ============================================================================\n");
    enter();
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
    vaciar_lvo(lista_lvo);
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
    printf("  ============================================================================\n");
    printf("                        Presionar \"enter\" para continuar\n");
    printf("  ============================================================================\n");
    getchar();
}

int preload(LSOBB *lsobb, ABB *abb){
    FILE *operaciones = fopen("Operaciones_Padron.txt", "r");
    if (operaciones == NULL) return -1; // archivo no encontrado

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
                // lso alta
                costo = altaLSO(lsobb, e_temp, &exito);
                if (exito){
                        acumular(&cAlta_lsobb_ex, costo);
                }else{
                    acumular(&cAlta_lsobb_fr, costo);
                }

                //lvo alta
                int ok_lvo = 0;
                float costo_lvo = altaLVO(&lista_lvo, e_temp, &ok_lvo);
                if (ok_lvo) {
                    acumular(&cAlta_lvo_ex, costo_lvo);
                } else {
                    acumular(&cAlta_lvo_fr, costo_lvo);
                }

                // abb alta
                costo = altaABB(abb, e_temp, &exito);
                if (exito){
                        acumular(&cAlta_abb_ex, costo);
                }else{
                    acumular(&cAlta_abb_fr, costo);
                }
                break;
            }
            case 2:{
                //lso baja
                costo = bajaLSO(lsobb, e_temp, &exito);
                if (exito){
                        acumular(&cBaja_lsobb_ex, costo);
                }else{
                    acumular(&cBaja_lsobb_fr, costo);
                }

                //lvo baja
                int ok_lvo = 0;
                float costo_lvo = bajaLVO(&lista_lvo, e_temp, &ok_lvo);
                if (ok_lvo) {
                    acumular(&cBaja_lvo_ex, costo_lvo);
                } else {
                    acumular(&cBaja_lvo_fr, costo_lvo);
                }


                //abb baja
                costo = bajaABB(abb, e_temp, &exito);
                if (exito){
                        acumular(&cBaja_abb_ex, costo);
                }else{
                    acumular(&cBaja_abb_fr, costo);
                }
                break;
            }
            case 3:{
                // lso evocar
                costo = evocarLSO(*lsobb, e_temp, &exito, &e_result);
                if (exito){
                        acumular(&cEvocar_lsobb_ex, costo);
                }else{
                    acumular(&cEvocar_lsobb_fr, costo);
                }

                //LVO evocar
                int ok_lvo = 0;
                elector res_lvo;
                float costo_lvo = evocarLVO(lista_lvo, e_temp.dni, &res_lvo, &ok_lvo);
                if (ok_lvo) {
                    acumular(&cEvocar_lvo_ex, costo_lvo);
                } else {
                    acumular(&cEvocar_lvo_fr, costo_lvo);
                }


                // lso evocar
                costo = evocarABB(abb, e_temp, &exito, &e_result);
                if (exito){
                        acumular(&cEvocar_abb_ex, costo);
                }else{
                    acumular(&cEvocar_abb_fr, costo);
                }
                break;
            }
        }
    }
    promedio(&cAlta_lsobb_ex);
    promedio(&cAlta_lvo_ex);
    promedio(&cAlta_abb_ex);
    promedio(&cBaja_lsobb_ex);
    promedio(&cBaja_lvo_ex);
    promedio(&cBaja_abb_ex);
    promedio(&cEvocar_lsobb_ex);
    promedio(&cEvocar_lvo_ex);
    promedio(&cEvocar_abb_ex);
    promedio(&cAlta_lsobb_fr);
    promedio(&cAlta_lvo_fr);
    promedio(&cAlta_abb_fr);
    promedio(&cBaja_lsobb_fr);
    promedio(&cBaja_lvo_fr);
    promedio(&cBaja_abb_fr);
    promedio(&cEvocar_lsobb_fr);
    promedio(&cEvocar_lvo_fr);
    promedio(&cEvocar_abb_fr);
    fclose(operaciones);
    return 0;
}

void mostrarABB(NodoABB *nodo, int *mostrados, int total, int *pagina){
    if (nodo == NULL) return;

    // nodo actual
    // valor
    printf("------------------------------------------------------------\n");
    printf("DNI:\t\t%d\n", nodo->root.dni);
    printf("Nombre:\t\t%s\n", nodo->root.nombreApellido);
    printf("Domicilio:\t%s\n", nodo->root.domicilio);
    printf("Codigo Postal:\t%d\n", nodo->root.cPostal);
    printf("Mesa:\t\t%d\n", nodo->root.mesa);
    printf("Circuito:\t%d\n", nodo->root.circuito);

    // print nodos
    if (nodo->izq == NULL && nodo->der == NULL) {
        printf("Hijos:\t\tno tiene hijos\n");
    } else {
        if (nodo->izq != NULL)
            printf("Hijo izquierdo:\tDNI %d\n", nodo->izq->root.dni);
        else
            printf("Hijo izquierdo:\tno tiene\n");

        if (nodo->der != NULL)
            printf("Hijo derecho:\tDNI %d\n", nodo->der->root.dni);
        else
            printf("Hijo derecho:\tno tiene\n");
    }
    (*mostrados)++;

    // cada pagina contiene 20 electores
    if ((*mostrados) % 20 == 0) {
        (*pagina)++;
        printf("------------------------------------------------------------\n");
        printf("Pagina %d | Mostrados: %d / %d\n", *pagina, *mostrados, total);
        enter();
        system("cls");
    }

    // preorden: valor(mostrado anteriormente) -> izquierdo -> derecho
    // avanzar
    mostrarABB(nodo->izq, mostrados, total, pagina);
    mostrarABB(nodo->der, mostrados, total, pagina);
}
