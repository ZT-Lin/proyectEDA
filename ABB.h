/*Alts o Lin agrega esto en el main que vayamos a usar
NodoABB *arbol_abb = NULL;
Costos costos_abb = {0};

Case 1: insertarABB(abb, e_temp, &cABB->costoAlta); 
Case 2: bajaABB(abb, e_temp, &cABB->costoBaja);
Case 3:
Elector res;
consultarABB(*abb, e_temp.dni, &res, &cABB->costoConsultas);

En el case 3 del menurdobich
case '3': {
    mostrarABB(arbol_abb);
    enter();
    break;
}

y al salir poner liberarABB(arbol_abb); para liberar anashe

.

*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOMBRE      51
#define MAX_DOM         81


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

//Aca empieza ABB. Lo hice recursivo porque asi me recomendo el Tansi y creo yo que es lo mas optimo y capaz lo mas limpio

typedef struct NodoABB {
    Elector dato;
    struct NodoABB *izq;
    struct NodoABB *der;
} NodoABB;

NodoABB *crearNodoABB(Elector e) {
    NodoABB *n = (NodoABB *)malloc(sizeof(NodoABB));
    n->dato = e;
    n->izq = NULL;
    n->der = NULL;
    return n;
}


int insertarABB(NodoABB **raiz, Elector e, double *costo) {
    if (*raiz == NULL) {
        *raiz = crearNodoABB(e);
        (*costo) += 0.5; //Enlace
        return 1;
    }
    if (e.dni == (*raiz)->dato.dni) {
        return 0; //Si esta duplicado significa que hubo un error y da 0
    } else if (e.dni < (*raiz)->dato.dni) {
        return insertarABB(&(*raiz)->izq, e, costo);
    } else {
        return insertarABB(&(*raiz)->der, e, costo);
    }
}


int bajaABB(NodoABB **raiz, Elector e, double *costo) {
    if (*raiz == NULL) {
        return 0; //No se encontro
    }

    if (e.dni < (*raiz)->dato.dni) {
        return bajaABB(&(*raiz)->izq, e, costo);
    } else if (e.dni > (*raiz)->dato.dni) {
        return bajaABB(&(*raiz)->der, e, costo);
    }

    if (!mismoElector(&(*raiz)->dato, &e)) {
        return 0;
    }

    NodoABB *aBorrar = *raiz;

    if ((*raiz)->izq == NULL && (*raiz)->der == NULL) {
        //Infertil (0 hijos)
        *raiz = NULL;
        (*costo) += 0.5;
        free(aBorrar);
    } else if ((*raiz)->izq == NULL) {
        // Familia con hijo ingeniero(Derecha)
        *raiz = (*raiz)->der;
        (*costo) += 0.5;
        free(aBorrar);
    } else if ((*raiz)->der == NULL) {
        // Familia con hijo de humanidades (zurdo)(Izquierda)
        *raiz = (*raiz)->izq;
        (*costo) += 0.5;
        free(aBorrar);
    } else {
        // Familia tipo
        NodoABB *padreSucesor = *raiz;
        NodoABB *sucesor = (*raiz)->der;

        while (sucesor->izq != NULL) {
            padreSucesor = sucesor;
            sucesor = sucesor->izq;
        }

        //Al ser una copia de datos, el costo es 1
        (*raiz)->dato = sucesor->dato;
        (*costo) += 1.0;

        //Dada en adopcion del nodo. Costo 0,5
        if (padreSucesor == *raiz) {
            padreSucesor->der = sucesor->der;
        } else {
            padreSucesor->izq = sucesor->der;
        }
        (*costo) += 0.5;

        free(sucesor);
    }

    return 1;
}

// Consulta por DNI, costo += 1 por cada nodo visto
int consultarABB(NodoABB *raiz, long dni, Elector *resultado, double *costo) {
    NodoABB *act = raiz;
    while (act != NULL) {
        (*costo) += 1;
        if (dni == act->dato.dni) {
            *resultado = act->dato;
            return 1;
        } else if (dni < act->dato.dni) {
            act = act->izq;
        } else {
            act = act->der;
        }
    }
    return 0;
}

// Hace recorrido pre orden difiniendo hijos derechos e izquierdos
void mostrarABBPreorden(NodoABB *raiz, int *contador) {
    if (raiz == NULL) return;

    imprimirElector(&raiz->dato);
    (*contador)++;

    if (raiz->izq == NULL && raiz->der == NULL) {
        printf("      -> No tiene hijos.\n");
    } else {
        if (raiz->izq != NULL) {
            printf("      -> Hijo izquierdo: DNI %ld\n", raiz->izq->dato.dni);
        } else {
            printf("      -> No tiene hijo izquierdo.\n");
        }

        if (raiz->der != NULL) {
            printf("      -> Hijo derecho: DNI %ld\n", raiz->der->dato.dni);
        } else {
            printf("      -> No tiene hijo derecho.\n");
        }
    }

    mostrarABBPreorden(raiz->izq, contador);
    mostrarABBPreorden(raiz->der, contador);
}

void mostrarABB(NodoABB *raiz) {
    printf("\n--- Padron - Arbol Binario de Busqueda (ABB) - Recorrido Preorden ---\n");
    int total = 0;
    mostrarABBPreorden(raiz, &total);
    printf("Total de electores en ABB: %d\n", total);
}

// Libera la memoria en postorden
void liberarABB(NodoABB *raiz) {
    if (raiz == NULL) return;
    liberarABB(raiz->izq);
    liberarABB(raiz->der);
    free(raiz);
}