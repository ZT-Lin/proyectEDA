/*Consideraciones a tener en cuenta:
El número estimado de electores en el archivo es de 2000.
Las listas deber´an estar ordenadas de menor a mayor respecto del D.N.I..
Para la lista secuencial, en la b´usqueda binaria la consigna a utilizar ser´a bisecci´on, l´ımite inferior inclusivo, l´ımi-
te superior inclusivo, testigo a izquierda y segmento mas grande a la izquierda. Para ella no se utilizar´a ning´un
elemento ficticio para indicar inicio o fin de lista.
La confirmaci´on de la baja en la rutina de baja debe realizarse por c´odigo, es decir comparando toda la nupla (en
todas las estructuras) .
La politica de reemplazo en la baja de los ´Arboles cuando el nodo tiene dos hijos es el menor de los mayores y el
reemplazo deber´a realizarse con copia de datos.
El valor utilizado como +infinito en LVO es el n´umero 999.999.999.
El D.N.I. es un entero.
El campo Nombre y apellido es una secuencia de hasta 50 caracteres.
El campo domicilio es una secuencia de hasta 80 caracteres.
El C´odigo Postal es un entero.
El N´umero de mesa es un entero.
El Circuito es un entero.
El ingreso de datos no debe ser sensible a may ´usculas y min ´usculas, esto significa por ejemplo que SOSA = SoSa
= sosa.*/


#include <stdio.h>

#define EST_ELECTORES 2000 /*Electores estimados*/
#define INFINITO_LVO 999999999
typedef struct {
    long dni;
    char nombreApellido[51];
    char domicilio[81];
    int cp;
    int mesa;
    int circuito;
} Elector;

typedef struct {
    float costoIngreso;
    float costoBaja;
    float costoConsulta;
} Costos;

/*Lista Vinculada Ordenada con terminaci´on dada por contenido (+ infinito) (LVO)*/

typedef struct NodoLVO{
    Elector elector;
    struct NodoLVO *siguien;
} NodoLVO;

/*Lista Secuencial Ordenada con b´usqueda binaria (LSOBB)*/
typedef struct {
    Elector electores[EST_ELECTORES];
    int cant;
}

/*Arbol Binario de B´usqueda (ABB).*/
typedef struct NodoABB{
    Elector elector;
    struct NodoABB *izq; 
    struct NodoABB *dere;
} NodoABB;

 float costo_altas_lvo = 0, costo_bajas_lvo= 0, costo_consulta_lvo = 0;
 float costo_altas_lsobb = 0, costo_bajas_lsobb= 0, costo_consulta_lsobb = 0;
 float costo_altas_abb = 0, costo_bajas_abb= 0, costo_consulta_abb = 0;

 /*Hacer el coso para que no se repitan los dni. Acordate Valen o Lin*/

 void initLVO() {
    /*Buscar o preguntar a gemini como hacer el init xd*/
 }

 void altaLVO(Elector e) {
    NodoLVO *actual = lvo_first, *ant = null;
    while (actual->elector.dni < e.dni){
    
    }
    
 }