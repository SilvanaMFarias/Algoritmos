#ifndef GESTORDEPRESTAMOS_H_INCLUDED
#define GESTORDEPRESTAMOS_H_INCLUDED
#include "lista.h"
#include "biblioteca.h"
#include "prestamo.h"
#include "ABB.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>
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
  
  // Funciones de análisis de préstamos
  void mostrarComplejidadAlgoritmica(string operacion, string complejidad, string explicacion);
  int convertirFechaStringAInt(string fecha);
  string convertirFechaIntAString(int fecha);
  void totalPrestamosPorBibliotecaEnRangoDeFechas();
  void detectarBibliotecasConAltaCarga();
  void buscarPrestamosDeUsuarioPorISBN();
};

#endif 
