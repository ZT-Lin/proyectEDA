#include <stdio.h>
#include <stdlib.h>

void mostrar_menu(void);

int main(){
    //menu
    bool SISTEMA = true;
    char comando_user[100];

    while(SISTEMA){
        mostrar_menu();
        scanf("%s", comando_user);
        getchar();

        switch(comando_user){
            case '1':{break;} // mostrar estructura LSOBB
            case '2':{break;} // mostrar estructura LVO
            case '3':{break;} // mostrar estructura ABB
            case '4':{break;} // comparar estructuras
            case '0':{
                SISTEMA = false;
                break;
            }
            default:{
                break
            }
        }

    }

    return 0;
}

void mostrar_menu(void){
    FILE *menu = fopen("menu.txt", "r");
    if( menu == NULL) return ;

    char buffer[100];
    while( fgets(buffer, sizeof(buffer), menu) != NULL ){
        printf("%s",buffer);
    }
}
