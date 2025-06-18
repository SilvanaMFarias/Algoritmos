#include "GestorDePrestamos.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <bits/stdc++.h>
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

void GestorDePrestamos::cantidadPrestamo(int fecha1, int fecha2)
{//la complejidad es lineal 2*N, y se puede mejorar
  map<string, int> diccionarioBiblioteca;

  for(int i=1; i<listaP.obtener_largo();i++)
  {
    
    if((listaP.consulta(i).getFechaDia()>=fecha1) && (listaP.consulta(i).getFechaDia()<=fecha2))
    {
      if(diccionarioBiblioteca.count(listaP.consulta(i).getCodigoBiblioteca()))
      {
        diccionarioBiblioteca.at(listaP.consulta(i).getCodigoBiblioteca())++;
      }
      else
      {
        diccionarioBiblioteca.insert({listaP.consulta(i).getCodigoBiblioteca(),1});
      }
    }
  }
  for(auto elem:diccionarioBiblioteca)
  {
    cout<<"codigo biblioteca: "<< elem.first <<" cantidad de prestamo: "<<elem.second << "\n";
  }
}

void GestorDePrestamos::buscarPrestamo(int userID)
{
  for(int i=1; i<listaP.obtener_largo();i++)
  {
    if(listaP.consulta(i).getUsuarioId()==userID)
    {
      listaP.consulta(i).mostrarInformacion();
    }
  }
}

GestorDePrestamos::~GestorDePrestamos(){
  listaP.~Lista();
  arbolP.~ABB();
}