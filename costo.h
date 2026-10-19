#ifndef COSTO_H_INCLUDED
#define COSTO_H_INCLUDED


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

/*==========impresion de tabla de costos==========*/
/* linea de separacion: n caracteres c + salto de linea */
void lineaTabla(char c, int n){
    for(int i = 0; i < n; i++) putchar(c);
    putchar('\n');
}

/* fila con valores (%.4f => maximo cuatro decimales) */
void filaTabla(const char *etiqueta, float ral, float rac, float rs){
    printf("| %-22s | %20.4f | %20.4f | %20.4f |\n",
           etiqueta, ral, rac, rs);
}

/* fila de titulo de bloque, sin valores */
void filaTitulo(const char *etiqueta){
    printf("| %-22s | %20s | %20s | %20s |\n",
           etiqueta, "", "", "");
}

/* bloque = 1 titulo + 4 subfilas (realizado / acumulado / mayor / promedio) */
void bloqueCostos(const char *titulo, Costo *ral, Costo *rac, Costo *rs){
    filaTitulo(titulo);
    filaTabla("  Total realizado", ral->realizado, rac->realizado, rs->realizado);
    filaTabla("  Total costo",     ral->acumulado, rac->acumulado, rs->acumulado);
    filaTabla("  Maximo",          ral->mayor,     rac->mayor,     rs->mayor);
    filaTabla("  Promedio",        ral->promedio,  rac->promedio,  rs->promedio);
}


#endif // COSTO_H_INCLUDED
