#ifndef NOMBREAPELLIDO_H_INCLUDED
#define NOMBREAPELLIDO_H_INCLUDED

typedef struct{
    char nombre[20], apellido[20];
}fullName;

char* getName(fullName N){
    return N.nombre
}

char* getApellido(fullName N){
    return N.apellido
}

void setName(fullName N, string nombre){
    N.nombre = nombre;
}

void setApellido(fullName N, string apellido){
    N.apellido = apellido;
}

#endif // NOMBREAPELLIDO_H_INCLUDED
