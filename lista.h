#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <iostream>
#include "nodo.h"

using namespace std;

template <typename T>
class Lista
{
private:
    // atributos
    Nodo<T>* primero;
    int largo;

public:
    // constructor
    // pos: crea una cola vacia
    Lista()
    {
        primero = 0;
        largo = 0;
    }

    // pre: 0 < pos <= cantidad + 1
    // pos: inserta el dato d en la posicion pos, la 1 es la primera
    //        ademas incrementa cantidad en 1
    void alta(T d, int pos){
        Nodo<T>* nuevo = new Nodo(d);
        if (pos == 1)
        {
            nuevo->cambiar_siguiente(primero);
            primero = nuevo;
        }
        else
        {
            Nodo<T>* anterior = obtener_nodo(pos - 1);
            Nodo<T>* siguiente = anterior->obtener_siguiente();
            nuevo->cambiar_siguiente(siguiente);
            anterior->cambiar_siguiente(nuevo);
        }
        largo++;
    }

    // pre: 0 < pos <= cantidad
    // pos: saca el elemento que esta en pos
    void baja(int pos){
        Nodo<T>* borrar;
        if (pos == 1)
        {
            borrar = primero;
            primero = borrar->obtener_siguiente();
        }
        else
        {
            Nodo<T>* anterior = obtener_nodo(pos - 1);
            borrar = anterior->obtener_siguiente();
            Nodo<T>* siguiente = borrar->obtener_siguiente();
            anterior->cambiar_siguiente(siguiente);
        }
        delete borrar;
        largo--;
    }

    // pre: 0 < pos <= cantidad
    // pos: devuelve el elemento que esta en pos
    T consulta(int pos){
        Nodo<T>* aux = obtener_nodo(pos);
        return aux->obtener_dato();
    }

    bool vacia(){
        return (largo == 0);
    }

    // pos: libera la memoria
    virtual ~Lista(){
        while (! vacia())
            baja(1);
    }

    int obtener_largo(){
        return largo;
    }

    void mostrar(){
        T dato;
        cout<<"[";

        if(!vacia())
        {
            for (int i = 1; i <= largo; i++){
                dato = this->consulta(i);
                dato.mostrarInformacion();
            }
            //cout << this->consulta(largo);
        }

        cout<<"]"<< endl << endl;
    }


private:
    Nodo<T>* obtener_nodo(int pos){
        Nodo<T>* aux = primero;
        for(int i = 1; i < pos; i++)
            aux = aux->obtener_siguiente();
        return aux;
    }
};


//template class Lista<Biblioteca>;
//template class Lista<Prestamo>;


#endif // LISTA_H_INCLUDED
