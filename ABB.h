#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include "nodoArbol.h"

template <typename T>
class ABB {
private:
  NodoArbol<T>* raiz;
  void insertarRecursivo(NodoArbol<T>*& nodo, T dato);
  void preordenRecursivo(NodoArbol<T>* nodo);
  void postordenRecursivo(NodoArbol<T>* nodo);
  void inordenRecursivo(NodoArbol<T>* nodo);
  void inordenNoRecursivo(NodoArbol<T>* nodo);
  void liberar(NodoArbol<T>* nodo);
  int contarNodosRecursivo(NodoArbol<T>* nodo);
  int calcularAltura(NodoArbol<T>* nodo);

public:
  ABB();
  ~ABB();

  void insertar(T dato);
  void mostrarRecorridoPreorden();
  void mostrarRecorridoPostorden();
  void mostrarRecorridoInorden();
  void mostrarRecorridoInordenIterativo();
  int contarNodos();
  int obtenerAltura();
};

#endif // ABB_H_INCLUDED
