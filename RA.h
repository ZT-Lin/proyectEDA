#ifndef RA_H_INCLUDED
#define RA_H_INCLUDED

#include "elector.h"

#define ITEMPORPAGINA 10

typedef struct{
        elector datos;// un solo ranura
        int estado;
}RA;

void initRA( RA ra[] ,int RAmax){
    int i;
    for(i=0; i < RAmax ; i++){
            initElector(&ra[i].datos);
            ra[i].estado = VIRGEN;
    }
}


void mostrarRA(RA ra[], int RAmax){
    int i;
    int contador = 0;
    const char *simbolo;

    for (i = 0; i < RAmax; i++){
        switch (ra[i].estado){
            case OCUPADA: simbolo = "OCUPADA (o)"; break;
            case LIBRE:   simbolo = "LIBRE (+)";   break;
            default:      simbolo = "VIRGEN (*)";  break;
        }

        printf("------------------------------------------------------------\n");
        printf("[%d] estado: %s\n", (i+1), simbolo);


        /* solo cuando OCUPADA mostramos el elector */
        if (ra[i].estado == OCUPADA){
            elector_mostrar(ra[i].datos);
        }

        /* cada ITEMPORPAGINA celdas, pausar */
        contador++;
        if (contador == ITEMPORPAGINA){
            contador = 0;
            printf("------------------------------------------------------------\n");
            printf("  Enter = seguir    q = salir\n  usuario ->\t");
            int c = getchar();
            if (c == 'q' || c == 'Q'){
                while (getchar() != '\n');
                printf("  ... cancelado\n");
                break;
            }
            while (c != '\n' && c != EOF) c = getchar();
            system("cls");
        }
    }

    printf("============================================================\n");
    printf(" \tFin del recorrido\n");
    printf("============================================================\n");
}


#endif // RA_H_INCLUDED
