#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <string>

using namespace std;

class Prestamo {
private:
  string codigoBiblioteca;
  string isbn;
  int usuarioId;
  int fechaDia;

public:
  //Constructor por defecto
  Prestamo()=default;
  // Constructor con parámetros
  Prestamo(string codigoBiblioteca, string isbn, int usuarioId, int fechaDia);


  // Getters
  string getCodigoBiblioteca() const;
  string getIsbn() const;
  int getUsuarioId() const;
  int getFechaDia() const;

  // Mostrar información
  void mostrarInformacion() const;
};

#endif // PRESTAMO_H
