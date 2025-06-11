#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include "GrafoDistBibliotecas.h"
using namespace std;

GrafoDistBibliotecas::GrafoDistBibliotecas() {
  cantidadNodos = 0;
}

void GrafoDistBibliotecas::cargarDesdeArchivo(string nombreArchivo) {
  ifstream archivo(nombreArchivo);
  if (!archivo) {
    cout << "Error al abrir el archivo: " << nombreArchivo << endl;
    return;
  }

  vector<Arista> aristas;
  unordered_set<string> nombres;

  string linea;
  while (getline(archivo, linea)) {
    stringstream ss(linea);
    //Biblioteca1 Biblioteca2 DistKm
    string b1, b2, d_str;
    double dist;

    // Se lee cada campo separado por tab
    if(getline(ss, b1, '\t') &&
    getline(ss, b2, '\t') &&
    getline(ss, d_str)){

    // Se convierte la distancia en string a double
    dist = stod(d_str);

    aristas.push_back({b1, b2, dist});
    nombres.insert(b1);
    nombres.insert(b2);
    }
  }

  // Se mapean bibliotecas a índices
  int i = 0;
  for (const string &nombre : nombres) {
    // Se asigna un índice a cada nombre
    nombreAIndice[nombre] = i++;
    // Se guarda el nombre en un vector en el mismo orden
    indiceANombre.push_back(nombre);
  }

  // La cantidad de nodos será la cantidad de filas y columnas que debe tener la matriz
  cantidadNodos = nombres.size();
  
  // Se asigna valor al atributo cantidad nodos
  cantidadNodos = nombres.size();

  // Se redimensionan las matrices para que sean una matriz cuadrada de tamaño cantidadNodos x cantidadNodos
  // Cada fila es un vector de 'cantidadNodos' elementos
  
  // Inicialización por defecto con valor infinito
  matrizDistancias.assign(cantidadNodos, vector<double>(cantidadNodos, numeric_limits<double>::infinity()));
  // Inicialización por defecto con valor -1
  matrizRecorridos.assign(cantidadNodos, vector<int>(cantidadNodos, -1));

  // Se inicializa la matriz distancias con 0 en la diagonal principal
  for (int i = 0; i < cantidadNodos; i++) {
    for (int j = 0; j < cantidadNodos; j++) {
      if (i == j) {
        matrizDistancias[i][j] = 0.0;
      }
    }
  }
  // Se cargan distancias directas desde cada nodo a otro
  for (size_t j = 0; j < aristas.size(); j++) {
    int origen = nombreAIndice[aristas[j].origen];
    int destino = nombreAIndice[aristas[j].destino];
    double dist = aristas[j].distancia;

    matrizDistancias[origen][destino] = dist;
    // Si es un digrafo se agrega distancia origen destino - destino origen
    matrizDistancias[destino][origen] = dist; 
  }

  // Se carga cada columna de la matriz recorrido con el valor del encabezado de la columna, a excepción de la diagonal
  for (int j = 0; j < cantidadNodos; j++) {
    for (int i = 0; i < cantidadNodos; i++) {
      if (i != j) {
        matrizRecorridos[i][j] = j;
      }
    }
  }

  cout << "Archivo cargado correctamente con " << cantidadNodos << " bibliotecas." << endl;
}


void GrafoDistBibliotecas::mostrarMatricesDistanciasYRecorridos(){
  cout << "Matriz Distancias" << endl << endl;
  // Encabezado
  cout << "\t";
  for (int j = 0; j < cantidadNodos; j++) {
    cout << indiceANombre[j] << "\t";
  }
  cout << endl;
  // Filas
  for (int i = 0; i < cantidadNodos; i++) {
    // Nombre de la fila
    cout << indiceANombre[i] << "\t"; 
    for (int j = 0; j < cantidadNodos; j++) {
      if (matrizDistancias[i][j] == numeric_limits<double>::infinity()) {
        cout << "INF\t";
      } else {
        cout << matrizDistancias[i][j] << "\t";
      }
    }
    cout << endl;
  }
  cout << endl;
  cout << "Matriz Recorridos" << endl << endl;
  // Encabezado
  cout << "\t";
  for (int j = 0; j < cantidadNodos; j++) {
    cout << indiceANombre[j] << "\t";
  }
  cout << endl;
  // Filas
  for (int i = 0; i < cantidadNodos; i++) {
    // Nombre de la fila
    cout << indiceANombre[i] << "\t"; 
    for (int j = 0; j < cantidadNodos; j++) {
      if (matrizRecorridos[i][j] == -1) {
        cout << "-\t";
      } else {
        cout << indiceANombre[matrizRecorridos[i][j]] << "\t";
      }
    }
    cout << endl;
  }
  cout << endl;
}

  void GrafoDistBibliotecas::calcularDistMinFloydWarshall(){
    /* Tres bucles anidados:
    El índice k representa un nodo intermedio potencial. i es el nodo de origen. j es el nodo de destino.
    En cada iteración, el algoritmo intenta mejorar la distancia de i a j revisando si pasar por el nodo intermedio k
    ofrece un camino más corto. De serlo, reemplaza el valor.
    */
    for(int k = 0; k < cantidadNodos; k++)
      for(int i = 0; i < cantidadNodos; i++)
        for(int j = 0; j < cantidadNodos; j++){
          // Verifico si la posicion es diferente a -1 que es el que actua como infinito
          if (matrizDistancias[i][k] != numeric_limits<double>::infinity()){
            if (matrizDistancias[k][j] != numeric_limits<double>::infinity())
            {
              float dt = matrizDistancias[i][k] + matrizDistancias[k][j];
              cout << "valor de dt" << dt << endl;
              cout << "valor de matriz distancias [i][j]" << matrizDistancias[i][j] << endl;
              if(dt < matrizDistancias[i][j]){
                cout << "Esta entrando aca???? " << endl;
                matrizDistancias[i][j] = dt;
                matrizRecorridos[i][j] = matrizRecorridos[i][k];
              }
            }
          }
        }
}

void GrafoDistBibliotecas::consultarDistMin(string origen, string destino){
  int indiceOrigen;
  int indiceDestino;
  vector<int> camino;

  // Se verifica que el origen corresponda a un nodo
  if (find(indiceANombre.begin(), indiceANombre.end(), origen) == indiceANombre.end()){
    cout << origen << " no es un nodo valido." << endl;
    return;
  }
  if (find(indiceANombre.begin(), indiceANombre.end(), destino) == indiceANombre.end()){
    cout << destino << " no es un nodo valido." << endl;
    return;
  }
  indiceOrigen = nombreAIndice[origen];
  indiceDestino = nombreAIndice[destino];

  if (matrizDistancias[indiceOrigen][indiceDestino] == numeric_limits<double>::infinity()){
    // En el caso de digrafo nunca va a ocurrir
    cout << "No existe camino entre " << origen << " y " << destino;
  } 
  else {
    cout << "La distancia minima entre " << origen << " y " << destino << " es de " << matrizDistancias[indiceOrigen][indiceDestino] << " km.";
    // Creando el recorrido
    camino.push_back(indiceOrigen);
    while (indiceOrigen != indiceDestino) {
        indiceOrigen = matrizRecorridos[indiceOrigen][indiceDestino];
        camino.push_back(indiceOrigen);
    }
    cout << endl << "El camino recorrido es: [ ";
    for (size_t i = 0; i < camino.size(); i++) {
      cout << indiceANombre[camino[i]];
      if (i < camino.size() - 1) cout << ", ";
    }
    cout << " ] " << endl << endl;
  }
}