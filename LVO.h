/*Alts o Lin agrega esto en el .main que vayamos a usar
NodoLVO *lista_lvo = crearLVO();
Costos costos_lvo = {0};
Eso en el main
Esto en el pre load
case 1 altaLVO(lvo, e_temp, &cLVO->costoAlta);
case 2 bajaLVO(lvo, e_temp, &cLVO->costoBaja);
case 3:  
Elector res;
consultarLVO(*lvo, e_temp.dni, &res, &cLVO->costoConsultas);

case 0 liberarLVO(lista_lvo);
.
*/





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOMBRE      51
#define MAX_DOM         81
#define INFINITO_LVO    999999999L

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
    int altasBien, altasMal;
    int bajasBien, bajasMal;
    int consultasBien, consultasMal;
} Costos;

//Utilidades utiles, cositas cositosas y funciones funcionales 
int miStrcasecmp(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0') {
        int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);
        if (ca != cb) {
            return ca - cb;
        }
        a++;
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

int mismoElector(const Elector *a, const Elector *b) {
    return a->dni == b->dni &&
           miStrcasecmp(a->nombreApellido, b->nombreApellido) == 0 &&
           miStrcasecmp(a->domicilio, b->domicilio) == 0 &&
           a->cp == b->cp &&
           a->mesa == b->mesa &&
           a->circuito == b->circuito;
}

void imprimirElector(const Elector *e) {
    printf("DNI: %-9ld | %-30s | %-30s | CP: %-5d | Mesa: %-4d | Circuito: %-4d\n",
           e->dni, e->nombreApellido, e->domicilio, e->cp, e->mesa, e->circuito);
}

//Aca empieza lo de LVO

typedef struct NodoLVO {
    Elector dato;
    struct NodoLVO *sig;
} NodoLVO;

NodoLVO *crearLVO(void) {
    NodoLVO *centinela = (NodoLVO *)malloc(sizeof(NodoLVO));
    centinela->dato.dni = INFINITO_LVO;
    centinela->dato.nombreApellido[0] = '\0';
    centinela->dato.domicilio[0] = '\0';
    centinela->dato.cp = 0;
    centinela->dato.mesa = 0;
    centinela->dato.circuito = 0;
    centinela->sig = NULL;
    return centinela;
}


int altaLVO(NodoLVO **lista, Elector e, double *costo) {
    NodoLVO *ant = NULL;
    NodoLVO *act = *lista;

    while (act->dato.dni < e.dni) {
        ant = act;
        act = act->sig;
    }

    if (act->dato.dni == e.dni) {
        return 0; //Dni dupeado
    }

    NodoLVO *nuevo = (NodoLVO *)malloc(sizeof(NodoLVO));
    nuevo->dato = e;
    nuevo->sig = act;

    if (ant == NULL) {
        *lista = nuevo;
    } else {
        ant->sig = nuevo;
    }
    (*costo) += 0.5;

    return 1;
}


int bajaLVO(NodoLVO **lista, Elector e, double *costo) {
    NodoLVO *ant = NULL;
    NodoLVO *act = *lista;

    while (act->dato.dni < e.dni) {
        ant = act;
        act = act->sig;
    }

    if (act->dato.dni != e.dni || !mismoElector(&act->dato, &e)) {
        return 0; // DNI(o dupla) incorrecto/a
    }

    if (ant == NULL) {
        *lista = act->sig;
    } else {
        ant->sig = act->sig;
    }
    (*costo) += 0.5;

    free(act);
    return 1;
}

int consultarLVO(NodoLVO *lista, long dni, Elector *resultado, double *costo) {
    NodoLVO *act = lista;
    while (act != NULL) {
        (*costo) += 1;
        if (act->dato.dni == dni) {
            *resultado = act->dato;
            return 1;
        }
        if (act->dato.dni > dni) {
            return 0; 
        }
        act = act->sig;
    }
    return 0;
}


void mostrarLVO(NodoLVO *lista) {
    printf("\n-- Padron - Lista Vinculada Ordenada (LVO)---\n");
    NodoLVO *act = lista;
    int cont = 0;
    while (act != NULL && act->dato.dni != INFINITO_LVO) {
        imprimirElector(&act->dato);
        act = act->sig;
        cont++;
    }
    printf("Total de electores en LVO: %d\n", cont);
}


void liberarLVO(NodoLVO *lista) {
    while (lista != NULL) {
        NodoLVO *tmp = lista;
        lista = lista->sig;
        free(tmp);
    }
}