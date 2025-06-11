#include <string>
#include "biblioteca.h"
#include "gestorDeBibliotecas.h"

#include "lista.h"

using namespace std;

int main() {
  GestorDeBibliotecas gestor;
  gestor.cargarDesdeArchivo("bibliotecas.txt");
  gestor.mostrarTodas();
  return 0;
}
