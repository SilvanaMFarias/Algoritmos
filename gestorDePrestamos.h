#ifndef GESTORDEPRESTAMOS_H_INCLUDED
#define GESTORDEPRESTAMOS_H_INCLUDED
#include "lista.h"
#include "biblioteca.h"
#include "prestamo.h"
#include "ABB.h"
#include <string>
class GestorDePrestamos {
private:
  int cantidad;
  Lista<Prestamo> listaP;
  ABB<Prestamo> arbolP;

public:
  ~GestorDePrestamos();
  void cargarDesdeArchivo(string nombreArchivo);
  void mostrarTodosLista();
  void mostrarTodosArbolIndorden();

  void cantidadPrestamo(int fecha1, int fecha2);
  void buscarPrestamo(int userID);
};

#endif 
