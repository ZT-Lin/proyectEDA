#ifndef FUNCIONHASHING_H_INCLUDED
#define FUNCIONHASHING_H_INCLUDED

// estados de la celda
#define VIRGEN 0
#define OCUPADA 1
#define LIBRE 2

// funcion hashing
int hashing(int dni, int M){
        char x[10];
        int longitud, i;
        int contador = 0;
        sprintf(x, "%d", dni);
        longitud = strlen(x);
        for( i=0; i<longitud; i++){
            contador+=((int)x[i]) * (i+1);
        }
        return (contador % M);
}

#endif // FUNCIONHASHING_H_INCLUDED
