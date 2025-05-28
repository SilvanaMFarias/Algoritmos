#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "biblioteca.h"
#include "prestamo.h"
#include "lista.h"
#include "ABB.h"

using namespace std;

int main() {
  /*Creo una lista de objetos biblioteca*/
  Lista<Biblioteca> lista_bibliotecas;
  /*Creo una lista de objetos prestamos*/
  Lista<Prestamo> lista_prestamos;
  /*Creo un árbol de objetos biblioteca*/
  ABB<Biblioteca> arbol_bibliotecas;
  /*Creo una lista de objetos prestamos*/
  ABB<Prestamo> arbol_prestamos;
  string linea;

  /***********************************************************/
  /*               PROCESO ARCHIVO BIBLIOTECAS               */
  /***********************************************************/

  ifstream archivo_bibliotecas("archivos/bibliotecas.txt");
  if (!archivo_bibliotecas.is_open()) {
    cout << "No se pudo abrir el archivo bibliotecas." << endl;
    return 1;
  }

  while (getline(archivo_bibliotecas, linea)) {
    stringstream ss(linea);
    string codigo, nombre, ciudad, superficie_str, cantidad_libros_str, cantidad_usuarios_str;

    if (getline(ss, codigo, '\t') &&
    getline(ss, nombre, '\t') &&
    getline(ss, ciudad, '\t') &&
    getline(ss, superficie_str, '\t') &&
    getline(ss, cantidad_libros_str, '\t') &&
    getline(ss, cantidad_usuarios_str)) {

    float superficie = stof(superficie_str); //Conversion a float
    int cantidad_libros = stoi(cantidad_libros_str); //Conversion a int
    int cantidad_usuarios = stoi(cantidad_usuarios_str); //Conversion a int

    /*cout << "Campos parseados:" << endl;
    cout << "  codigo: [" << codigo << "]" << endl;
    cout << "  nombre: [" << nombre << "]" << endl;
    cout << "  ciudad: [" << ciudad << "]" << endl;
    cout << "  superficie: [" << superficie_str << "]" << endl;
    cout << "  libros: [" << cantidad_libros_str << "]" << endl;
    cout << "  usuarios: [" << cantidad_usuarios_str << "]" << endl;*/

    Biblioteca *b = new Biblioteca(codigo, nombre, ciudad, superficie, cantidad_libros, cantidad_usuarios);
    lista_bibliotecas.alta(*b, 1);
    arbol_bibliotecas.insertar(*b);
    }
  }
  
  archivo_bibliotecas.close();

  // Mostrar todas las bibliotecas
  cout << endl << "Mostrando la lista de bibliotecas del archivo bibliotecas.txt:" << endl << endl;
  lista_bibliotecas.mostrar();
  // Liberar memoria de la lista
  lista_bibliotecas.~Lista();
  cout << endl << "Mostrando el arbol de bibliotecas del archivo bibliotecas.txt. Recorrido inorden" << endl;
  arbol_bibliotecas.mostrarRecorridoInorden();
  arbol_bibliotecas.~ABB();

  /***********************************************************/
  /*                  PROCESO ARCHIVO PRESTAMOS              */
  /***********************************************************/
  
  linea="";

  ifstream archivo_prestamos("archivos/prestamos.txt");
  if (!archivo_prestamos.is_open()) {
    cout << "No se pudo abrir el archivo prestamos.txt." << endl;
    return 1;
  }

  while (getline(archivo_prestamos, linea)) {
    stringstream ss(linea);
    string codigo_biblioteca, isbn, usuario_id_str, fecha_dia_str;

    if (getline(ss, codigo_biblioteca, '\t') &&
      getline(ss, isbn, '\t') &&
      getline(ss, usuario_id_str, '\t') &&
      getline(ss, fecha_dia_str)) {

    int usuario_id = stoi(usuario_id_str);
    int fecha_dia = stoi(fecha_dia_str);

    Prestamo *p = new Prestamo(codigo_biblioteca, isbn, usuario_id, fecha_dia);
    lista_prestamos.alta(*p, 1);
    arbol_prestamos.insertar(*p);
    }
  }
  
  archivo_prestamos.close();

  cout << "Mostrando la lista de prestamos del archivo prestamos.txt:" << endl << endl;
  // Mostrar la lista de prestamos
  lista_prestamos.mostrar();
  // Liberar memoria de la lista
  lista_prestamos.~Lista();
  // Mostrar el árbol de préstamos
  cout << "Mostrando el arbol de prestamos del archivo prestamos.txt. Recorrido Inorden" << endl;
  arbol_prestamos.mostrarRecorridoInorden();
  // Liberar memoria del árbol
  arbol_prestamos.~ABB();
  return 0;
}
