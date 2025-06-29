#ifndef GESTORDEPRESTAMOS_H_INCLUDED
#define GESTORDEPRESTAMOS_H_INCLUDED
#include "lista.h"
#include "biblioteca.h"
#include "prestamo.h"
#include "ABB.h"
#include <bits/stdc++.h>
#include <string>
using namespace std;

class GestorDePrestamos {
private:
  int cantidad;
  Lista<Prestamo> listaP;
  ABB<Prestamo> arbolP;
  std::map<std::string, int> prestamos(int fecha1, int fecha2);

public:
  ~GestorDePrestamos();
  void cargarDesdeArchivo(string nombreArchivo);
  void mostrarTodosLista();
  void mostrarTodosArbolIndorden();

  void cantidadPrestamo(int fecha1, int fecha2);
  void cargaDePrestamo(int carga, int partida);
  void buscarPrestamo(string isbn);
};

#endif 
