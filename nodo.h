#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED
//#include "biblioteca.h"

template <typename T>
class Nodo
{
private:
    // atributos
    T dato;
    Nodo<T>* siguiente;

public:
    // metodos
    // constructor
    // PRE:
    // POS: crea un nodo con dato = d y siguiente = 0
    Nodo(T d){
        dato = d;
        siguiente = 0;
    }

    void cambiar_dato(T d){
        dato = d;
    }

    void cambiar_siguiente(Nodo<T>* s){
        siguiente = s;
    }


    T obtener_dato(){
        return dato;
    }

    Nodo<T>* obtener_siguiente(){
        return siguiente;
    }

};

#endif // NODO_H_INCLUDED
