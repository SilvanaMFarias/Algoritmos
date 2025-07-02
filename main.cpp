#include <iostream>
#include <string>
#include "biblioteca.h"
#include "gestorDeBibliotecas.h"
#include "gestorDePrestamos.h"
#include "lista.h"

using namespace std;

void mostrarMenu() {
    cout << "\n========= GESTION DE BIBLIOTECAS =========" << endl << endl;
    cout << "1. Cargar bibliotecas desde archivo" << endl;
    cout << "2. Mostrar bibliotecas (lista)" << endl;
    cout << "3. Mostrar bibliotecas (arbol inorden)" << endl;
    cout << "4. Cargar prestamos desde archivo" << endl;
    cout << "5. Mostrar prestamos (lista)" << endl;
    cout << "6. Mostrar prestamos (arbol inorden)" << endl;
    cout << "7. Agregar nueva biblioteca" << endl;
    cout << "8. Eliminar biblioteca por codigo" << endl;
    cout << "9. Consultar camino minimo entre bibliotecas" << endl;
    cout << "10. Buscar biblioteca por codigo (HASH)" << endl;
    cout << "11. Comparar rendimiento de busqueda (con muchas bibliotecas)" << endl;
    cout << "12. Mostrar estadisticas de tabla hash" << endl;
    cout << "13. Mostrar lista bibliotecas ordenadas por cantidad de libros (orden ascendente)" << endl;
    cout << "14. Mostrar lista bibliotecas ordenadas por superficie (orden ascendente)" << endl;
    cout << "15. Mostrar lista bibliotecas ordenadas por cantidad de usuarios (orden ascendente)" << endl;
    cout << "\n========= ANALISIS DE PRESTAMOS =========" << endl << endl;
    cout << "16. Total de prestamos por biblioteca en rango de fechas" << endl;
    cout << "17. Detectar bibliotecas con alta carga (semana)" << endl;
    cout << "18. Buscar prestamos de usuario por ISBN" << endl;
    cout << "0. Salir" << endl;
    cout << endl << "Seleccione una opcion: ";
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
        cout << endl;

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

            case 10:
                if (cargadasBibliotecas) {
                    string codigo;
                    cout << "Ingrese el codigo de la biblioteca a buscar: ";
                    cin >> codigo;
                    Biblioteca* resultado = gb.buscarPorCodigo(codigo);
                    if (resultado) {
                        cout << "\n✓ Biblioteca encontrada:" << endl;
                        resultado->mostrarInformacion();
                        delete resultado;
                    } else {
                        cout << "\n✗ No se encontro la biblioteca con codigo: " << codigo << endl;
                    }
                } else {
                    cout << "Primero debe cargar las bibliotecas (opcion 1).\n";
                }
                break;

            case 11:
                {
                    cout << "\n--- Comparacion de Rendimiento con Muchas Bibliotecas ---" << endl;
                    cout << "Cargando archivo con muchas bibliotecas para la comparacion..." << endl;
                    
                    // Crear un gestor temporal para la comparación
                    GestorDeBibliotecas gbRendimiento;
                    gbRendimiento.cargarDesdeArchivo("bibliotecas-rendimiento.txt");
                    
                    string codigo;
                    cout << "Ingrese el codigo de la biblioteca para comparar rendimiento: ";
                    cin >> codigo;
                    gbRendimiento.compararRendimientoBusqueda(codigo);
                    
                    cout << "\nNota: Esta comparacion se realizo con " << 100 << " bibliotecas para demostrar mejor las diferencias de rendimiento." << endl;
                }
                break;

            case 12:
                if (cargadasBibliotecas) {
                    gb.mostrarEstadisticasHash();
                } else {
                    cout << "Primero debe cargar las bibliotecas (opcion 1).\n";
                }
                break;

            case 13:
                if (cargadasBibliotecas) {
                    gb.ordenarBibliotecasPorLibros();
                    gb.mostrarTodasLista();
                } else {
                    cout << "Primero debe cargar las bibliotecas (opcion 1).\n";
                }
                break;

            case 14:
                if (cargadasBibliotecas) {
                    gb.ordenarBibliotecasPorSuperficie();
                    gb.mostrarTodasLista();
                } else {
                    cout << "Primero debe cargar las bibliotecas (opcion 1).\n";
                }
                break;

            case 15:
                if (cargadasBibliotecas) {
                    gb.ordenarBibliotecasPorUsuarios();
                    gb.mostrarTodasLista();
                } else {
                    cout << "Primero debe cargar las bibliotecas (opcion 1).\n";
                }
                break;

            case 16:
                if (cargadosPrestamos) {
                    gp.totalPrestamosPorBibliotecaEnRangoDeFechas();
                } else {
                    cout << "Primero debe cargar los prestamos (opcion 4).\n";
                }
                break;

            case 17:
                if (cargadosPrestamos) {
                    gp.detectarBibliotecasConAltaCarga();
                } else {
                    cout << "Primero debe cargar los prestamos (opcion 4).\n";
                }
                break;

            case 18:
                if (cargadosPrestamos) {
                    gp.buscarPrestamosDeUsuarioPorISBN();
                } else {
                    cout << "Primero debe cargar los prestamos (opcion 4).\n";
                }
                break;

            case 0:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "Opcion invalida. Intente nuevamente.\n";
        }
        cout << endl << "Presione Enter para continuar...";
        cin.ignore(); // descarta cualquier entrada previa
        cin.get();    // espera que el usuario presione Enter

    } while(opcion != 0);

    return 0;
}