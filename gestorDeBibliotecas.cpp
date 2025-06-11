#include "GestorDeBibliotecas.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

void GestorDeBibliotecas::cargarDesdeArchivo(string nombreArchivo) {
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
    int libros = stoi(librosStr);
    int usuarios = stoi(usuariosStr);

    Biblioteca b(codigo, nombre, ciudad, superficie, libros, usuarios);
    listaB.alta(b, 1);
    }
  }

  archivo.close();
}

void GestorDeBibliotecas::mostrarTodas(){
  listaB.mostrar();
}
