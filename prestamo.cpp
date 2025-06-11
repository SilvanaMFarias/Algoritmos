#include "prestamo.h"
#include <iostream>

using namespace std;

Prestamo::Prestamo(string codigoBiblioteca, string isbn, int usuarioId, int fechaDia)
  : codigoBiblioteca(codigoBiblioteca), isbn(isbn), usuarioId(usuarioId), fechaDia(fechaDia) {}

string Prestamo::getCodigoBiblioteca() const {
  return codigoBiblioteca;
}

string Prestamo::getIsbn() const {
  return isbn;
}

int Prestamo::getUsuarioId() const {
  return usuarioId;
}

int Prestamo::getFechaDia() const {
  return fechaDia;
}

// Convierte fecha de int en formato YYYYMMDD a string dd/mm/aaaa
string formatearFecha(int fecha) {
    string f = to_string(fecha); 
    string anio = f.substr(0, 4);
    string mes = f.substr(4, 2);
    string dia = f.substr(6, 2);
    return dia + "/" + mes + "/" + anio;
}

void Prestamo::mostrarInformacion() const {
  cout << endl << "Codigo Biblioteca: " << codigoBiblioteca << endl;
  cout << "ISBN: " << isbn << endl;
  cout << "ID Usuario: " << usuarioId << endl;
  cout << "Fecha: " << formatearFecha(fechaDia) << endl;
}
