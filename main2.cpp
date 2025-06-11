#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "biblioteca.h"
#include "prestamo.h"
#include "lista.h"
#include "ABB.h"
#include "grafoDistBibliotecas.h"

int main() {
  GrafoDistBibliotecas g;
  g.cargarDesdeArchivo("archivos/distanciasEntreBibliotecas.txt");
  cout << "Carga inicial de la matriz desde el archivo" << endl << endl;
  g.mostrarMatricesDistanciasYRecorridos();
  cout << "Luego de aplicar Floyd Warshall" << endl << endl;
  g.calcularDistMinFloydWarshall();
  g.mostrarMatricesDistanciasYRecorridos();
  cout << "Consultando la distancia minima y el recorrido entre UNAHUR Y UNLAM, que tienen una distancia directa de 12.1" << endl << endl;
  g.consultarDistMin("UNAHUR","UNLAM");
  cout << "Consultando la distancia minima y el recorrido entre FADU Y UNAHUR" << endl << endl;
  g.consultarDistMin("FADU","UNAHUR");
  return 0;
}
