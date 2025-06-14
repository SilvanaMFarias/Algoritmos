#ifndef GESTORDEBIBLIOTECAS_H_INCLUDED
#define GESTORDEBIBLIOTECAS_H_INCLUDED

#include "lista.h"
#include "biblioteca.h"
#include "ABB.h"
#include "grafoDistBibliotecas.h"
#include <string>
using namespace std;

class GestorDeBibliotecas {
private:
  int cantidad;
  Lista<Biblioteca> listaB;
  ABB<Biblioteca> arbolB;
  GrafoDistBibliotecas gDb;

public:
  ~GestorDeBibliotecas();
  void cargarDesdeArchivo(string nombreArchivo);
  void mostrarTodasLista();
  void mostrarTodasArbolIndorden();
  void consultarCaminoMinimo();
  /*Biblioteca* buscarPorCodigo(const string &codigo);
  void agregar(const Biblioteca &biblio);
  bool eliminar(const string &codigo);*/
};


#endif