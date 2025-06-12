#include "GestorDePrestamos.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

void GestorDePrestamos::cargarDesdeArchivo(string nombreArchivo) {
  string linea;
  ifstream archivoPrestamos("archivos/" + nombreArchivo);
  if (!archivoPrestamos.is_open()) {
    cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
    return;
  }

  while (getline(archivoPrestamos, linea)) {
    stringstream ss(linea);
    string codigoBiblioteca, isbn, usuarioIdStr, fechaDiaStr;

    if (getline(ss, codigoBiblioteca, '\t') &&
      getline(ss, isbn, '\t') &&
      getline(ss, usuarioIdStr, '\t') &&
      getline(ss, fechaDiaStr)) {

    int usuarioId = stoi(usuarioIdStr);
    int fechaDia = stoi(fechaDiaStr);

    Prestamo *p = new Prestamo(codigoBiblioteca, isbn, usuarioId, fechaDia);
    listaP.alta(*p, 1);
    arbolP.insertar(*p);
    }
  }
  archivoPrestamos.close();
}

void GestorDePrestamos::mostrarTodosLista(){
  cout << "Mostrando lista: " << endl;
  listaP.mostrar();
}

void GestorDePrestamos::mostrarTodosArbolIndorden(){
  cout << "Mostrando arbol inorden: " << endl;
  arbolP.mostrarRecorridoInorden();
}

GestorDePrestamos::~GestorDePrestamos(){
  listaP.~Lista();
  arbolP.~ABB();
}