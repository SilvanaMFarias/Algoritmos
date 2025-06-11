#include <iostream>
#include <stack>
#include "biblioteca.h"
#include "prestamo.h"
#include "ABB.h"
using namespace std;

template <typename T>
ABB<T>::ABB() {
  raiz = nullptr;
}

template <typename T>
ABB<T>::~ABB() {
  liberar(raiz);
}

template <typename T>
void ABB<T>::insertar(T dato) {
  insertarRecursivo(raiz, dato);
}
/*
template <typename T>
void ABB<T>::insertarRecursivo(NodoArbol<T>*& nodo, T dato) {
  if (nodo == nullptr) {
    nodo = new NodoArbol<T>(dato);
  } else if (dato < nodo->obtenerDato()) {
      insertarRecursivo(nodo->obtenerHijoIzquierdo(), dato);
  } else {
      insertarRecursivo(nodo->obtenerHijoDerecho(), dato);
  }
}
*/

template <typename T>
void ABB<T>::insertarRecursivo(NodoArbol<T>*& nodo, T dato) {
  if (nodo == nullptr) {
    nodo = new NodoArbol<T>(dato);
  } else if (dato.getCodigoBiblioteca() < nodo->obtenerDato().getCodigoBiblioteca()) {
    insertarRecursivo(nodo->obtenerHijoIzquierdo(), dato);
  } else {
    insertarRecursivo(nodo->obtenerHijoDerecho(), dato);
  }
}



template <typename T>
void ABB<T>::mostrarRecorridoPreorden() {
  preordenRecursivo(raiz);
  cout << endl;
}

template <typename T>
void ABB<T>::preordenRecursivo(NodoArbol<T>* nodo) {
  if (nodo != nullptr) {
    //cout << nodo->obtenerDato() << " ";
    nodo->obtenerDato().mostrarInformacion();
    preordenRecursivo(nodo->obtenerHijoIzquierdo());
    preordenRecursivo(nodo->obtenerHijoDerecho());
  }
}

template <typename T>
void ABB<T>::mostrarRecorridoPostorden() {
  postordenRecursivo(raiz);
  cout << endl;
}

template <typename T>
void ABB<T>::postordenRecursivo(NodoArbol<T>* nodo) {
  if (nodo != nullptr) {
    postordenRecursivo(nodo->obtenerHijoIzquierdo());
    postordenRecursivo(nodo->obtenerHijoDerecho());
    //cout << nodo->obtenerDato() << " ";
    nodo->obtenerDato().mostrarInformacion();
  }
}

template <typename T>
void ABB<T>::mostrarRecorridoInorden() {
  inordenRecursivo(raiz);
  cout << endl;
}

template <typename T>
void ABB<T>::inordenRecursivo(NodoArbol<T>* nodo) {
  if (nodo != nullptr) {
    inordenRecursivo(nodo->obtenerHijoIzquierdo());
    //cout << nodo->obtenerDato() << " ";
    nodo->obtenerDato().mostrarInformacion();
    inordenRecursivo(nodo->obtenerHijoDerecho());
  }
}

template <typename T>
void ABB<T>::liberar(NodoArbol<T>* nodo) {
  if (nodo != nullptr) {
    liberar(nodo->obtenerHijoIzquierdo());
    liberar(nodo->obtenerHijoDerecho());
    delete nodo;
  }
}

template <typename T>
int ABB<T>::contarNodos() {
  return contarNodosRecursivo(raiz);
}

template <typename T>
int ABB<T>::contarNodosRecursivo(NodoArbol<T>* nodo){
  if (nodo == nullptr)
    return 0;
  // Suma el nodo actual y los nodos de los árboles derecho e izquierdo
  return 1  + contarNodosRecursivo(nodo->obtenerHijoIzquierdo()) 
            + contarNodosRecursivo(nodo->obtenerHijoDerecho());
}

template <typename T>
int ABB<T>::obtenerAltura(){
    return calcularAltura(raiz);
}

template <typename T>
int ABB<T>::calcularAltura(NodoArbol<T>* nodo){
    if (nodo == nullptr) {
        return 0;
    }
    int alturaIzq = calcularAltura(nodo->obtenerHijoIzquierdo());
    int alturaDer = calcularAltura(nodo->obtenerHijoDerecho());
    return 1 + max(alturaIzq, alturaDer);
}

template <typename T>
void ABB<T>::mostrarRecorridoInordenIterativo() {
  stack<NodoArbol<T>*> pila;
  NodoArbol<T>* actual = raiz;

  while (actual != nullptr || !pila.empty()) {
      // Llega al nodo más a la izquierda
    while (actual != nullptr) {
      pila.push(actual);
      actual = actual->obtenerHijoIzquierdo();
  }

      // Procesa el nodo
      actual = pila.top();
      pila.pop();
      //cout << actual->obtenerDato() << " ";
      actual->obtenerDato().mostrarInformacion();

      // Va al subárbol derecho
      actual = actual->obtenerHijoDerecho();
    }
}




// Instanciaciones explícitas
template class ABB<Prestamo>;
template class ABB<Biblioteca>;

