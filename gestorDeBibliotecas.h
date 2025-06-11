#pragma once
#include "lista.h"
#include "biblioteca.h"
#include <string>
using namespace std;

class GestorDeBibliotecas {
private:
  Lista<Biblioteca> listaB;

public:
    void cargarDesdeArchivo(string nombreArchivo);
    void mostrarTodas();
    /*Biblioteca* buscarPorCodigo(const string &codigo);
    void agregar(const Biblioteca &biblio);
    bool eliminar(const string &codigo);*/
};
