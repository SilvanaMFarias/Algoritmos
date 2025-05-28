#include "biblioteca.h"
#include <iostream>
#include <iomanip>

using namespace std;

Biblioteca::Biblioteca(string codigo_biblioteca, string nombre, string ciudad, float superficie, int cantidad_libros, int cantidad_usuarios)
  : codigo_biblioteca(codigo_biblioteca), nombre(nombre), ciudad(ciudad), superficie(superficie),
  cantidad_libros(cantidad_libros), cantidad_usuarios(cantidad_usuarios) {}

string Biblioteca::get_codigo_biblioteca() const {
  return codigo_biblioteca;
}

string Biblioteca::get_nombre() const {
  return nombre;
}

string Biblioteca::get_ciudad() const {
  return ciudad;
}

float Biblioteca::get_superficie() const {
  return superficie;
}

int Biblioteca::get_cantidad_libros() const {
  return cantidad_libros;
}

int Biblioteca::get_cantidad_usuarios() const {
  return cantidad_usuarios;
}

void Biblioteca::mostrar_informacion() const {
  cout << endl << "Codigo biblioteca: " << codigo_biblioteca << endl;
  cout << "Nombre: " << nombre << endl;
  cout << "Ciudad: " << ciudad << endl;
  cout << "Superficie: " << fixed << setprecision(2) << superficie << " km cuadrados" << endl;
  cout << "Cantidad de libros: " << cantidad_libros << endl;
  cout << "Cantidad de usuarios: " << cantidad_usuarios << endl;
}
