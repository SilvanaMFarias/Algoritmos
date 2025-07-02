#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include <string>
using namespace std;

class Biblioteca {
private:
  string codigoBiblioteca;
  string nombre;
  string ciudad;
  float superficie;
  int cantidadLibros;
  int cantidadUsuarios;

public:
  //Constructor por defecto
  Biblioteca() = default;
  // Constructor con parámetros
  Biblioteca(string codigoBiblioteca, string nombre, string ciudad, float superficie, int cantidadLibros, int cantidadUsuarios);


  // Getters
  string getCodigoBiblioteca() const;
  string getNombre() const;
  string getCiudad() const;
  float getSuperficie() const;
  int getCantidadLibros() const;
  int getCantidadUsuarios() const;

  // Mostrar información
  void mostrarInformacion() const;

  // Comparaciones para ordenamiento
  static bool compararPorLibros(Biblioteca a, Biblioteca b);
  static bool compararPorSuperficie(Biblioteca a, Biblioteca b);
  static bool compararPorUsuarios(Biblioteca a, Biblioteca b);
};

#endif // BIBLIOTECA_H

