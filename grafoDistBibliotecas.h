#ifndef GRAFODISTBIBLIOTECAS_H
#define GRAFODISTBIBLIOTECAS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <algorithm>
using namespace std;

struct Arista {
  string origen;
  string destino;
  double distancia;
};

class GrafoDistBibliotecas {
private:
  unordered_map<string, int> nombreAIndice;
  vector<string> indiceANombre;
  vector<vector<double> > matrizDistancias;
  vector<vector<int> > matrizRecorridos;
  int cantidadNodos;

public:
  GrafoDistBibliotecas();
  void cargarDesdeArchivo(string nombreArchivo);
  void mostrarMatricesDistanciasYRecorridos();
  void calcularDistMinFloydWarshall();
  void consultarDistMin(string origen, string destino);
};

#endif
