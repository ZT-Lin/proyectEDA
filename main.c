#include <stdio.h>
#include <stdlib.h>

void mostrar_menu(FILE*);

int main(){
    // mostrar menu
    FILE *menu = fopen("menu.txt", "r");
    if( menu == NULL) return -1 ;

    mostrar_menu(menu);
}

void mostrar_menu(FILE *f){
    char buffer[100];
    while( fgets(buffer, sizeof(buffer), f) != NULL ){
        printf("%s",buffer);
    }
}
