#include <string>
#include "biblioteca.h"
#include "gestorDeBibliotecas.h"
#include "gestorDePrestamos.h"
#include "lista.h"

using namespace std;

int main() {
  GestorDeBibliotecas gb;
  cout << "GESTOR DE BIBLIOTECAS" << endl;
  cout << "---------------------" << endl;

  gb.cargarDesdeArchivo("bibliotecas.txt");
  cout << endl << "Bibliotecas en lista" << endl;
  gb.mostrarTodasLista();
  cout << endl << "Bibliotecas en arbol" << endl;
  gb.mostrarTodasArbolIndorden();
  cout << "GESTOR DE PRESTAMOS" << endl;
  cout << "---------------------" << endl;
  GestorDePrestamos gp;
  gp.cargarDesdeArchivo("prestamos.txt");
  cout << endl << "Prestamos en lista" << endl;
  gp.mostrarTodosLista();
  cout << endl << "Prestamos en arbol" << endl;
  gp.mostrarTodosArbolIndorden();
  gb.~GestorDeBibliotecas();
  gp.~GestorDePrestamos();

  return 0;
}
