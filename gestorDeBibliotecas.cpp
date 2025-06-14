#include "GestorDeBibliotecas.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

void GestorDeBibliotecas::cargarDesdeArchivo(string nombreArchivo) {
  cantidad = 0;
  string rutaArchivo = "archivos/" + nombreArchivo;
  ifstream archivo(rutaArchivo);
  if (!archivo.is_open()) {
    cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    return;
  }

  string linea;
  while (getline(archivo, linea)) {
    stringstream ss(linea);
    string codigo, nombre, ciudad, superficieStr, librosStr, usuariosStr;

    if (getline(ss, codigo, '\t') &&
    getline(ss, nombre, '\t') &&
    getline(ss, ciudad, '\t') &&
    getline(ss, superficieStr, '\t') &&
    getline(ss, librosStr, '\t') &&
    getline(ss, usuariosStr)) {

    float superficie = stof(superficieStr);
    int cantidadLibros = stoi(librosStr);
    int cantidadUsuarios = stoi(usuariosStr);
    
    Biblioteca *b = new Biblioteca(codigo, nombre, ciudad, superficie, cantidadLibros, cantidadUsuarios);
    listaB.alta(*b, 1);
    arbolB.insertar(*b);
    cantidad++;
    }
  }
  archivo.close();
}

void GestorDeBibliotecas::mostrarTodasLista(){
  cout << "Mostrando lista: " << endl;
  listaB.mostrar();
}

void GestorDeBibliotecas::mostrarTodasArbolIndorden(){
  cout << "Mostrando arbol inorden: " << endl;
  arbolB.mostrarRecorridoInorden();
}

GestorDeBibliotecas::~GestorDeBibliotecas(){
  listaB.~Lista();
  arbolB.~ABB();
}