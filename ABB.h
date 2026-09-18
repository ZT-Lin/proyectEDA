#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED

// nodo del arbol segun Vale
typedef struct NodoABB{
    Elector elector;
    struct NodoABB *izq;
    struct NodoABB *dere;
} NodoABB;


#endif // ABB_H_INCLUDED
