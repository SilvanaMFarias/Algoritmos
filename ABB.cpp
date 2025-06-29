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
  cout << "Eliminando arbol...";
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

// Implementación de métodos de eliminación
template <typename T>
bool ABB<T>::eliminar(const string& codigo) {
    NodoArbol<T>* nodoOriginal = raiz;
    raiz = eliminarRecursivo(raiz, codigo);
    return raiz != nodoOriginal; // Retorna true si se eliminó algo
}

template <typename T>
NodoArbol<T>* ABB<T>::eliminarRecursivo(NodoArbol<T>* nodo, const string& codigo) {
    if (nodo == nullptr) {
        return nullptr; // No se encontró el nodo
    }
    
    // Buscar el nodo a eliminar
    if (codigo < nodo->obtenerDato().getCodigoBiblioteca()) {
        nodo->cambiarHijoIzquierdo(eliminarRecursivo(nodo->obtenerHijoIzquierdo(), codigo));
    } else if (codigo > nodo->obtenerDato().getCodigoBiblioteca()) {
        nodo->cambiarHijoDerecho(eliminarRecursivo(nodo->obtenerHijoDerecho(), codigo));
    } else {
        // Nodo encontrado - proceder con la eliminación
        
        // Caso 1: Nodo hoja
        if (nodo->obtenerHijoIzquierdo() == nullptr && nodo->obtenerHijoDerecho() == nullptr) {
            delete nodo;
            return nullptr;
        }
        // Caso 2: Nodo con un solo hijo
        else if (nodo->obtenerHijoIzquierdo() == nullptr) {
            NodoArbol<T>* temp = nodo->obtenerHijoDerecho();
            delete nodo;
            return temp;
        }
        else if (nodo->obtenerHijoDerecho() == nullptr) {
            NodoArbol<T>* temp = nodo->obtenerHijoIzquierdo();
            delete nodo;
            return temp;
        }
        // Caso 3: Nodo con dos hijos
        else {
            // Encontrar el sucesor inorden (mínimo del subárbol derecho)
            NodoArbol<T>* sucesor = encontrarMinimo(nodo->obtenerHijoDerecho());
            
            // Copiar el dato del sucesor al nodo actual
            nodo->cambiarDato(sucesor->obtenerDato());
            
            // Eliminar el sucesor
            nodo->cambiarHijoDerecho(eliminarRecursivo(nodo->obtenerHijoDerecho(), 
                                                      sucesor->obtenerDato().getCodigoBiblioteca()));
        }
    }
    
    return nodo;
}

template <typename T>
NodoArbol<T>* ABB<T>::encontrarMinimo(NodoArbol<T>* nodo) {
    if (nodo == nullptr) {
        return nullptr;
    }
    
    // El mínimo es el nodo más a la izquierda
    while (nodo->obtenerHijoIzquierdo() != nullptr) {
        nodo = nodo->obtenerHijoIzquierdo();
    }
    
    return nodo;
}

// Implementación del método buscar
template <typename T>
T* ABB<T>::buscar(const string& codigo) {
    NodoArbol<T>* nodo = buscarRecursivo(raiz, codigo);
    if (nodo != nullptr) {
        return new T(nodo->obtenerDato());
    }
    return nullptr;
}

template <typename T>
NodoArbol<T>* ABB<T>::buscarRecursivo(NodoArbol<T>* nodo, const string& codigo) {
    if (nodo == nullptr || nodo->obtenerDato().getCodigoBiblioteca() == codigo) {
        return nodo;
    }
    
    if (codigo < nodo->obtenerDato().getCodigoBiblioteca()) {
        return buscarRecursivo(nodo->obtenerHijoIzquierdo(), codigo);
    } else {
        return buscarRecursivo(nodo->obtenerHijoDerecho(), codigo);
    }
}

// Instanciaciones explícitas
template class ABB<Prestamo>;
template class ABB<Biblioteca>;

