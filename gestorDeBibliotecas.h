#ifndef GESTORDEBIBLIOTECAS_H_INCLUDED
#define GESTORDEBIBLIOTECAS_H_INCLUDED

#include "lista.h"
#include "biblioteca.h"
#include "ABB.h"
#include "grafoDistBibliotecas.h"
#include "hash.h"
#include <string>
using namespace std;

class GestorDeBibliotecas {
private:
  int cantidad;
  Lista<Biblioteca> listaB;
  ABB<Biblioteca> arbolB;
  GrafoDistBibliotecas gDb;
  Hash<Biblioteca> tablaHash; // Nueva tabla hash para búsquedas O(1)

public:
  ~GestorDeBibliotecas();
  void cargarDesdeArchivo(string nombreArchivo);
  void mostrarTodasLista();
  void mostrarTodasArbolIndorden();
  void consultarCaminoMinimo();
  
  // Métodos de búsqueda usando tabla hash
  Biblioteca* buscarPorCodigo(const string &codigo); // Usa hash O(1)
  Biblioteca* buscarPorCodigoLista(const string &codigo); // Para comparación O(n)
  Biblioteca* buscarPorCodigoArbol(const string &codigo); // Para comparación O(log n)
  void compararRendimientoBusqueda(const string &codigo);
  void mostrarEstadisticasHash();
  
  // Métodos de gestión
  void agregar(const Biblioteca &biblio);
  bool eliminar(const string &codigo); 
  void agregarNuevaBiblioteca(string nombreArchivo);
  void guardarEnArchivo(string nombreArchivo);
  void eliminarBibliotecaPorCodigo(string nombreArchivo);
};

#endif