#include "GestorDePrestamos.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
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

map<string,int> GestorDePrestamos::prestamos(int fecha1,int fecha2)
{//complejidad de lineal de 1N
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
  return diccionarioBiblioteca;
}

void GestorDePrestamos::cantidadPrestamo(int fecha1, int fecha2)
{//la complejidad es lineal 2*N, y se puede mejorar
  
  for(auto elem:this->prestamos(fecha1,fecha2))
  {
    cout<<"codigo biblioteca: "<< elem.first <<" cantidad de prestamo: "<<elem.second << "\n";
  }
}

void GestorDePrestamos::cargaDePrestamo(int carga, int yyyymmdd)
{
  int day = yyyymmdd % 100;
  int month = (yyyymmdd / 100) % 100;
  int year = yyyymmdd / 10000;

  tm timeinfo = {}; // Initialize to all zeros
  timeinfo.tm_year = year - 1900; // tm_year is years since 1900
  timeinfo.tm_mon = month - 1;   // tm_mon is 0-indexed (0-11)
  timeinfo.tm_mday = day;
  timeinfo.tm_mday -=7;

  int semana = (timeinfo.tm_year+1900)*1000+timeinfo.tm_mon*100+timeinfo.tm_mday;

  for(auto elem:this->prestamos(semana,yyyymmdd))
  {
    if(elem.second>=carga)
    {
      cout<<"codigo biblioteca: "<< elem.first <<" cantidad de prestamo: "<<elem.second << "\n";
    }
  }
}

void GestorDePrestamos::buscarPrestamo(int userID)
{//complejidad lineal de N 
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