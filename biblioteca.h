#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include <string>

using namespace std;

class Biblioteca {
private:
  string codigo;
  string nombre;
  string ciudad;
  float superficie;
  int cantidad_libros;
  int cantidad_usuarios;

public:
  //Constructor por defecto
  Biblioteca() = default;
  // Constructor con parámetros
  Biblioteca(string codigo, string nombre, string ciudad, float superficie, int cantidad_libros, int cantidad_usuarios);


  // Getters
  string get_codigo() const;
  string get_nombre() const;
  string get_ciudad() const;
  float get_superficie() const;
  int get_cantidad_libros() const;
  int get_cantidad_usuarios() const;

  // Mostrar información
  void mostrar_informacion() const;
};

#endif // BIBLIOTECA_H

