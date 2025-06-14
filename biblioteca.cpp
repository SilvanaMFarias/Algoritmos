#include "biblioteca.h"
#include <iostream>
#include <iomanip>

using namespace std;

Biblioteca::Biblioteca(string codigo_biblioteca, string nombre, string ciudad, float superficie, int cantidad_libros, int cantidad_usuarios)
  : codigoBiblioteca(codigo_biblioteca), nombre(nombre), ciudad(ciudad), superficie(superficie),
  cantidadLibros(cantidad_libros), cantidadUsuarios(cantidad_usuarios) {}

string Biblioteca::getCodigoBiblioteca() const {
  return codigoBiblioteca;
}

string Biblioteca::getNombre() const {
  return nombre;
}

string Biblioteca::getCiudad() const {
  return ciudad;
}

float Biblioteca::getSuperficie() const {
  return superficie;
}

int Biblioteca::getCantidadLibros() const {
  return cantidadLibros;
}

int Biblioteca::getCantidadUsuarios() const {
  return cantidadUsuarios;
}

void Biblioteca::mostrarInformacion() const {
  cout << endl << "Codigo biblioteca: " << codigoBiblioteca << endl;
  cout << "Nombre: " << nombre << endl;
  cout << "Ciudad: " << ciudad << endl;
  cout << "Superficie: " << fixed << setprecision(2) << superficie << " km cuadrados" << endl;
  cout << "Cantidad de libros: " << cantidadLibros << endl;
  cout << "Cantidad de usuarios: " << cantidadUsuarios << endl;
}
