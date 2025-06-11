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
  Lista<Biblioteca> listaBibliotecas;
  /*Creo una lista de objetos prestamos*/
  Lista<Prestamo> listaPrestamos;
  /*Creo un árbol de objetos biblioteca*/
  ABB<Biblioteca> arbolBibliotecas;
  /*Creo una lista de objetos prestamos*/
  ABB<Prestamo> arbolPrestamos;
  string linea;

  /***********************************************************/
  /*               PROCESO ARCHIVO BIBLIOTECAS               */
  /***********************************************************/

  ifstream archivoBibliotecas("archivos/bibliotecas.txt");
  if (!archivoBibliotecas.is_open()) {
    cout << "No se pudo abrir el archivo bibliotecas." << endl;
    return 1;
  }

  while (getline(archivoBibliotecas, linea)) {
    stringstream ss(linea);
    string codigo, nombre, ciudad, superficieStr, cantidadLibrosStr, cantidadUsuariosStr;

    if (getline(ss, codigo, '\t') &&
    getline(ss, nombre, '\t') &&
    getline(ss, ciudad, '\t') &&
    getline(ss, superficieStr, '\t') &&
    getline(ss, cantidadLibrosStr, '\t') &&
    getline(ss, cantidadUsuariosStr)) {

    float superficie = stof(superficieStr); //Conversion a float
    int cantidadLibros = stoi(cantidadLibrosStr); //Conversion a int
    int cantidadUsuarios = stoi(cantidadUsuariosStr); //Conversion a int

    /*cout << "Campos parseados:" << endl;
    cout << "  codigo: [" << codigo << "]" << endl;
    cout << "  nombre: [" << nombre << "]" << endl;
    cout << "  ciudad: [" << ciudad << "]" << endl;
    cout << "  superficie: [" << superficie_str << "]" << endl;
    cout << "  libros: [" << cantidad_libros_str << "]" << endl;
    cout << "  usuarios: [" << cantidad_usuarios_str << "]" << endl;*/

    Biblioteca *b = new Biblioteca(codigo, nombre, ciudad, superficie, cantidadLibros, cantidadUsuarios);
    listaBibliotecas.alta(*b, 1);
    arbolBibliotecas.insertar(*b);
    }
  }
  
  archivoBibliotecas.close();

  // Mostrar todas las bibliotecas
  cout << endl << "Mostrando la lista de bibliotecas del archivo bibliotecas.txt:" << endl << endl;
  listaBibliotecas.mostrar();
  // Liberar memoria de la lista
  listaBibliotecas.~Lista();
  cout << endl << "Mostrando el arbol de bibliotecas del archivo bibliotecas.txt. Recorrido inorden" << endl;
  arbolBibliotecas.mostrarRecorridoInorden();
  arbolBibliotecas.~ABB();

  /***********************************************************/
  /*                  PROCESO ARCHIVO PRESTAMOS              */
  /***********************************************************/
  
  linea="";

  ifstream archivoPrestamos("archivos/prestamos.txt");
  if (!archivoPrestamos.is_open()) {
    cout << "No se pudo abrir el archivo prestamos.txt." << endl;
    return 1;
  }

  while (getline(archivoPrestamos, linea)) {
    stringstream ss(linea);
    string codigo_biblioteca, isbn, usuarioIdStr, fechaDiaStr;

    if (getline(ss, codigo_biblioteca, '\t') &&
      getline(ss, isbn, '\t') &&
      getline(ss, usuarioIdStr, '\t') &&
      getline(ss, fechaDiaStr)) {

    int usuario_id = stoi(usuarioIdStr);
    int fecha_dia = stoi(fechaDiaStr);

    Prestamo *p = new Prestamo(codigo_biblioteca, isbn, usuario_id, fecha_dia);
    listaPrestamos.alta(*p, 1);
    arbolPrestamos.insertar(*p);
    }
  }
  
  archivoPrestamos.close();

  cout << "Mostrando la lista de prestamos del archivo prestamos.txt:" << endl << endl;
  // Mostrar la lista de prestamos
  listaPrestamos.mostrar();
  // Liberar memoria de la lista
  listaPrestamos.~Lista();
  // Mostrar el árbol de préstamos
  cout << "Mostrando el arbol de prestamos del archivo prestamos.txt. Recorrido Inorden" << endl;
  arbolPrestamos.mostrarRecorridoInorden();
  // Liberar memoria del árbol
  arbolPrestamos.~ABB();
  return 0;
}
