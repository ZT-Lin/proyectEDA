/*
====== GRUPO 41 =======
Correa Valentin, Lin Franco.
====================


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

============COMPARACION DE ESTRUCTURAS============
                            LSOBB                            LVO                               ABB
  Operacion  (Media / Maximo)       (Media / Maximo)       (Media / Maximo)
  ----------------------------------------------------------------------------

  -- ALTAS --
  Exito                 413.07 / 1932.0         1.00 / 1.0            0.50 / 0.5
  Fracaso                 0.00 / 0.0            0.00 / 0.0            0.00 / 0.0

  -- BAJAS --
  Exito                 502.61 / 1893.0         0.50 / 0.5            1.02 / 1.5
  Fracaso                 0.00 / 0.0            0.00 / 0.0            0.00 / 0.0

  -- EVOCACION --
  Exito                  10.14 / 11.0         566.80 / 1994.0        11.84 / 22.0
  Fracaso                 9.88 / 11.0         463.47 / 1206.0        12.03 / 21.0
====================ANALISIS====================
LSOBB - ALTA
    Una vez encontrada la posición a insertar, se realizan corrimientos
    de atrás hacia adelante. En el peor caso (insertar al inicio) se
    desplazan n elementos. El valor observado [1932] confirma esto.
    => Cota superior: O(n)

LVO - ALTA
    Solo se modifican punteros (nodo anterior y nodo nuevo).
    El costo es constante, no depende de n.
    => Cota superior: O(1)

ABB - ALTA
    Se enlaza el nuevo nodo como hoja, modificando un único puntero
    del padre.
    => Cota superior: O(1)


LSOBB - BAJA
    Similar al alta: en el peor caso (eliminar el primero) se deben
    desplazar n-1 elementos para compactar la lista.
    => Cota superior: O(n)

LVO - BAJA
    Solo se redirige el puntero del nodo anterior al siguiente.
    El costo es constante.
    => Cota superior: O(1)

ABB - BAJA
    Si el nodo tiene 0 o 1 hijo: solo se modifica un puntero (0.5).
    Si tiene 2 hijos: se usa el menor de los mayores con copia de
    datos, sumando 1 por la copia (total 1.5).
    => Cota superior: O(1) (el costo no depende de n)


LSOBB - EVOCACION
    Búsqueda binaria: en cada paso se reduce el intervalo a la mitad.
    Para n = 2000, log2(2000) ≈ 11. El máximo observado [11] coincide.
    => Cota superior: O(log n)

LVO - EVOCACION
    Búsqueda secuencial: en el peor caso se recorre toda la lista.
    El máximo observado [1994] confirma esto.
    => Cota superior: O(n)

ABB - EVOCACION
    En un árbol balanceado se desciende por un camino, comparando
    en cada nivel. Si el árbol degenera en lista, se recorre todo.
    El máximo observado [22] indica un árbol razonablemente balanceado.
    => Cota superior: O(log n) si está balanceado
    => Peor caso: O(n) en un arbol degenerado


====================CONCLUSION====================

    LSOBB: muy buena para consultas (O(log n)), pero muy costosa
    para altas y bajas (O(n)) por los corrimientos.

    LVO: muy buena para altas y bajas (O(1)), pero muy costosa
    para consultas (O(n)) por el recorrido secuencial.

    ABB: equilibrada. Altas y bajas en O(1), consultas en O(log n)
    si el árbol se mantiene balanceado. En el peor caso (árbol
    degenerado) las consultas pueden llegar a O(n).

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

int preload(LSOBB*, ABB*, NodoLVO**); // esperando mas estructuras @Alts
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
    bool datos_cargados = false;
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
    /*if( preload(&lista_secuencial_ordenada,&arbol_binario_busqueda) ==-1 ){
        printf("============================================================\n");
        printf("\tError: archivo \"Operaciones_Padron.txt\" no encontrado.\n");
        enter();
        return -1;
    }
    enter();*/

    //Deberia ir dentro de la opcion 4

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

                if (total == 0) {
                    printf("============================================================\n");
                    printf("\tLSOBB se encuentra vacia (0 electores).\n");
                    printf("============================================================\n");
                    enter();
                    break;
                }

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

                if (aux == NULL || aux->persona.dni == VALOR_INFINITO) {
                    printf("============================================================\n");
                    printf("\tLVO se encuentra vacia (0 electores).\n");
                    printf("============================================================\n");
                    enter();
                    break;
                }

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

                if (total == 0) {
                    printf("============================================================\n");
                    printf("\tABB se encuentra vacio (0 electores).\n");
                    printf("============================================================\n");
                    enter();
                    break;
                }

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
                //carga una sola vez los datos
                if (!datos_cargados) {
                    //Resets de structuras y costos
                    //Resets de structuras y costos
                    initLSOBB(&lista_secuencial_ordenada);
                    vaciar_lvo(lista_lvo);
                    lista_lvo = inicializar_lvo();
                    initABB(&arbol_binario_busqueda);
                    //costitos
                    initCosto(&cAlta_lsobb_ex);   initCosto(&cAlta_lsobb_fr);
                    initCosto(&cBaja_lsobb_ex);   initCosto(&cBaja_lsobb_fr);
                    initCosto(&cEvocar_lsobb_ex); initCosto(&cEvocar_lsobb_fr);
                    initCosto(&cAlta_lvo_ex);     initCosto(&cAlta_lvo_fr);
                    initCosto(&cBaja_lvo_ex);     initCosto(&cBaja_lvo_fr);
                    initCosto(&cEvocar_lvo_ex);   initCosto(&cEvocar_lvo_fr);
                    initCosto(&cAlta_abb_ex);     initCosto(&cAlta_abb_fr);
                    initCosto(&cBaja_abb_ex);     initCosto(&cBaja_abb_fr);
                    initCosto(&cEvocar_abb_ex);   initCosto(&cEvocar_abb_fr);
                    printf("Procesando 'Operaciones_Padron.txt' en las tres estructuras...\n");
                    if (preload(&lista_secuencial_ordenada, &arbol_binario_busqueda, &lista_lvo) == -1) {
                        printf("============================================================\n");
                        printf("\tError: archivo \"Operaciones_Padron.txt\" no encontrado.\n");
                        enter();
                        break;
                    }
                    datos_cargados = true;
                    system("cls");
                }

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
                    acumular(&cAlta_lsobb_ex, costo);
                } else {
                    acumular(&cAlta_lsobb_fr, costo);
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
                    acumular(&cBaja_lsobb_ex, costo);
                } else {
                    acumular(&cBaja_lsobb_fr, costo);
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
                    acumular(&cEvocar_lsobb_ex, costo);
                } else {
                    acumular(&cEvocar_lsobb_fr, costo);
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
