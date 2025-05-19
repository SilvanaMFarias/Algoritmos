#include "prestamo.h"
#include <iostream>

using namespace std;

Prestamo::Prestamo(string codigo_biblioteca, string isbn, string usuario_id, int fecha_dia)
  : codigo_biblioteca(codigo_biblioteca), isbn(isbn), usuario_id(usuario_id), fecha_dia(fecha_dia) {}

string Prestamo::get_codigo_biblioteca() const {
  return codigo_biblioteca;
}

string Prestamo::get_isbn() const {
  return isbn;
}

string Prestamo::get_usuario_id() const {
  return usuario_id;
}

int Prestamo::get_fecha_dia() const {
  return fecha_dia;
}



// Convierte fecha de int en formato YYYYMMDD a string dd/mm/aaaa
string formatear_fecha(int fecha) {
    string f = to_string(fecha); 
    string anio = f.substr(0, 4);
    string mes = f.substr(4, 2);
    string dia = f.substr(6, 2);
    return dia + "/" + mes + "/" + anio;
}

void Prestamo::mostrar_informacion() const {
  cout << endl << "Código Biblioteca: " << codigo_biblioteca << endl;
  cout << "ISBN: " << isbn << endl;
  cout << "ID Usuario: " << usuario_id << endl;
  cout << "Fecha: " << formatear_fecha(fecha_dia) << endl << endl;
}
