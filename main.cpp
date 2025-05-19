#include <iostream>
#include <fstream>
#include <sstream>
#include "biblioteca.h"
#include "lista.h"

using namespace std;

int main() {
  ifstream archivo_bibliotecas("archivos/bibliotecas.txt");
  if (!archivo_bibliotecas.is_open()) {
    cout << "No se pudo abrir el archivo." << endl;
    return 1;
  }

  Lista lista_bibliotecas;
  string linea;

  while (getline(archivo_bibliotecas, linea)) {
    stringstream ss(linea);
    cout << "La linea que lee" << endl << linea << endl;
    string codigo, nombre, ciudad, superficie_str, cantidad_libros_str, cantidad_usuarios_str;

    if (getline(ss, codigo, '\t') &&
    getline(ss, nombre, '\t') &&
    getline(ss, ciudad, '\t') &&
    getline(ss, superficie_str, '\t') &&
    getline(ss, cantidad_libros_str, '\t') &&
    getline(ss, cantidad_usuarios_str)) {

    float superficie = stof(superficie_str);
    int cantidad_libros = stoi(cantidad_libros_str);
    int cantidad_usuarios = stoi(cantidad_usuarios_str);

    /*cout << "Campos parseados:" << endl;
    cout << "  codigo: [" << codigo << "]" << endl;
    cout << "  nombre: [" << nombre << "]" << endl;
    cout << "  ciudad: [" << ciudad << "]" << endl;
    cout << "  superficie: [" << superficie_str << "]" << endl;
    cout << "  libros: [" << cantidad_libros_str << "]" << endl;
    cout << "  usuarios: [" << cantidad_usuarios_str << "]" << endl;*/

    Biblioteca *b = new Biblioteca(codigo, nombre, ciudad, superficie, cantidad_libros, cantidad_usuarios);
    lista_bibliotecas.alta(*b, 1);
    }
  }
  
  archivo_bibliotecas.close();

  // Mostrar todas las bibliotecas
  lista_bibliotecas.mostrar();

  return 0;
}
