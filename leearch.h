#ifndef LEEARCH_H_INCLUDED
#define LEEARCH_H_INCLUDED

#include <stdio.h>

int cargar_struct(LSOBB *lso){
    // abre el archivo
    FILE *operaciones = fopen( "Operaciones_Padron.txt", "r");
    if (operaciones==NULL){ return -1; }


    padron elector_temp;
    int itemp=0;
    char nam[51], dom[81];

    // leer el comando: 1-alta, 2-baja, 3-evocacion
    int comando = 0;
    while( fscanf(operaciones, "%d", &comando) == 1 ){

            inicializarP(&elector_temp);

            switch(comando){
                case 1:{


                    break;
                }
                case 2:{
                    break;
                }
                case 3:{
                    fscanf(operaciones, "%d", &itemp);
                    setDNI(&elector_temp, itemp);
                    break;
                }
                default:{
                }
            }
    }
}



#endif // LEEARCH_H_INCLUDED
