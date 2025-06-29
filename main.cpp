#include <iostream>
#include <string>
#include "biblioteca.h"
#include "gestorDeBibliotecas.h"
#include "gestorDePrestamos.h"
#include "lista.h"

using namespace std;

void mostrarMenu() {
    cout << "\n========= MENU PRINCIPAL =========" << endl;
    cout << "1. Cargar bibliotecas desde archivo" << endl;
    cout << "2. Mostrar bibliotecas (lista)" << endl;
    cout << "3. Mostrar bibliotecas (arbol inorden)" << endl;
    cout << "4. Cargar prestamos desde archivo" << endl;
    cout << "5. Mostrar prestamos (lista)" << endl;
    cout << "6. Mostrar prestamos (arbol inorden)" << endl;
    cout << "7. Agregar nueva biblioteca" << endl;
    cout << "8. Eliminar biblioteca por codigo" << endl;
    cout << "9. Consultar camino minimo entre bibliotecas" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    GestorDeBibliotecas gb;
    GestorDePrestamos gp;

    int opcion;
    bool cargadasBibliotecas = false;
    bool cargadosPrestamos = false;
    string nombreArchivoBibliotecas = "bibliotecas.txt";
    string nombreArchivoPrestamos = "prestamos.txt";

    do {
        mostrarMenu();
        cin >> opcion;

        switch(opcion) {
            case 1:
                gb.cargarDesdeArchivo(nombreArchivoBibliotecas);
                cout << "Bibliotecas cargadas correctamente.\n";
                cargadasBibliotecas = true;
                break;

            case 2:
                if (cargadasBibliotecas) {
                    gb.mostrarTodasLista();
                } else {
                    cout << "Primero debe cargar las bibliotecas (opcion 1).\n";
                }
                break;

            case 3:
                if (cargadasBibliotecas) {
                    gb.mostrarTodasArbolIndorden();
                } else {
                    cout << "Primero debe cargar las bibliotecas (opcion 1).\n";
                }
                break;

            case 4:
                gp.cargarDesdeArchivo(nombreArchivoPrestamos);
                cout << "Prestamos cargados correctamente.\n";
                cargadosPrestamos = true;
                break;

            case 5:
                if (cargadosPrestamos) {
                    gp.mostrarTodosLista();
                } else {
                    cout << "Primero debe cargar los prestamos (opcion 4).\n";
                }
                break;

            case 6:
                if (cargadosPrestamos) {
                    gp.mostrarTodosArbolIndorden();
                } else {
                    cout << "Primero debe cargar los prestamos (opcion 4).\n";
                }
                break;

            case 7:
                gb.agregarNuevaBiblioteca(nombreArchivoBibliotecas);
                if (!cargadasBibliotecas) {
                    cargadasBibliotecas = true;
                }
                break;

            case 8: 
                if (cargadasBibliotecas) {
                    gb.eliminarBibliotecaPorCodigo(nombreArchivoBibliotecas);
                } else {
                    cout << "Primero debe cargar las bibliotecas (opcion 1).\n";
                }
                break;

            case 9:
                if (cargadasBibliotecas) {
                    gb.consultarCaminoMinimo();
                } else {
                    cout << "Primero debe cargar las bibliotecas (opcion 1).\n";
                }
                break;

            case 0:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "Opcion invalida. Intente nuevamente.\n";
        }

    } while(opcion != 0);

    return 0;
}