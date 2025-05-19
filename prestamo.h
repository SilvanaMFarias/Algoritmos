#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <string>

using namespace std;

class Prestamo {
private:
  string codigo_biblioteca;
  string isbn;
  int usuario_id;
  int fecha_dia;

public:
  //Constructor por defecto
  Prestamo()=default;
  // Constructor con parámetros
  Prestamo(string codigo_biblioteca, string isbn, int usuario_id, int fecha_dia);


  // Getters
  string get_codigo_biblioteca() const;
  string get_isbn() const;
  int get_usuario_id() const;
  int get_fecha_dia() const;

  // Mostrar información
  void mostrar_informacion() const;
};

#endif // PRESTAMO_H
