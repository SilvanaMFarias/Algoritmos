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
    cout << "0. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    GestorDeBibliotecas gb;
    GestorDePrestamos gp;

    int opcion;
    bool cargadasBibliotecas = false;
    bool cargadosPrestamos = false;

    do {
        mostrarMenu();
        cin >> opcion;

        switch(opcion) {
            case 1:
                gb.cargarDesdeArchivo("bibliotecas.txt");
                cout << "Bibliotecas cargadas correctamente.\n";
                cargadasBibliotecas = true;
                break;

            case 2:
                if (cargadasBibliotecas) {
                    cout << "\n--- Bibliotecas en lista ---\n";
                    gb.mostrarTodasLista();
                } else {
                    cout << "Primero debe cargar las bibliotecas.\n";
                }
                break;

            case 3:
                if (cargadasBibliotecas) {
                    cout << "\n--- Bibliotecas en arbol (inorden) ---\n";
                    gb.mostrarTodasArbolIndorden();
                } else {
                    cout << "Primero debe cargar las bibliotecas.\n";
                }
                break;

            case 4:
                gp.cargarDesdeArchivo("prestamos.txt");
                cout << "Prestamos cargados correctamente.\n";
                cargadosPrestamos = true;
                break;

            case 5:
                if (cargadosPrestamos) {
                    cout << "\n--- Prestamos en lista ---\n";
                    gp.mostrarTodosLista();
                } else {
                    cout << "Primero debe cargar los prestamos.\n";
                }
                break;

            case 6:
                if (cargadosPrestamos) {
                    cout << "\n--- Prestamos en arbol (inorden) ---\n";
                    gp.mostrarTodosArbolIndorden();
                } else {
                    cout << "Primero debe cargar los prestamos.\n";
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
