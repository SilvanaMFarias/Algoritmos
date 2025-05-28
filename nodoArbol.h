#ifndef NODO_ARBOL_H_INCLUDED
#define NODO_ARBOL_H_INCLUDED
#include <string>

template <typename T>
class NodoArbol {
private:
    T dato;
    NodoArbol<T>* hijoIzquierdo;
    NodoArbol<T>* hijoDerecho;

public:
    NodoArbol(T d) {
        dato = d;
        hijoIzquierdo = nullptr;
        hijoDerecho = nullptr;
    }

    void cambiarDato(T d) { dato = d; }
    void cambiarHijoIzquierdo(NodoArbol<T>* izq) { hijoIzquierdo = izq; }
    void cambiarHijoDerecho(NodoArbol<T>* der) { hijoDerecho = der; }

    T obtenerDato() { return dato; }
    NodoArbol<T>*& obtenerHijoIzquierdo() { return hijoIzquierdo; }
    NodoArbol<T>*& obtenerHijoDerecho() { return hijoDerecho; }
};

#endif // NODO_ARBOL_H_INCLUDED
