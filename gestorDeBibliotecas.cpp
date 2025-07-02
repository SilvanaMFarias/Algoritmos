#include "GestorDeBibliotecas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <chrono>
#include <iomanip>

using namespace std;

void GestorDeBibliotecas::cargarDesdeArchivo(string nombreArchivo) {
  cantidad = 0;
  string rutaArchivo = "archivos/" + nombreArchivo;
  ifstream archivo(rutaArchivo);
  if (!archivo.is_open()) {
    cout << "No se pudo abrir el archivo: " << rutaArchivo << endl;
    return;
  }

  string linea;
  while (getline(archivo, linea)) {
    stringstream ss(linea);
    string codigo, nombre, ciudad, superficieStr, librosStr, usuariosStr;

    if (getline(ss, codigo, '\t') &&
        getline(ss, nombre, '\t') &&
        getline(ss, ciudad, '\t') &&
        getline(ss, superficieStr, '\t') &&
        getline(ss, librosStr, '\t') &&
        getline(ss, usuariosStr)) {

      try {
        float superficie = stof(superficieStr);
        int cantidadLibros = stoi(librosStr);
        int cantidadUsuarios = stoi(usuariosStr);

        Biblioteca *b = new Biblioteca(codigo, nombre, ciudad, superficie, cantidadLibros, cantidadUsuarios);
        listaB.alta(*b, 1); 
        arbolB.insertar(*b);
        tablaHash.insertar(codigo, *b); // Agregar a la tabla hash
        cantidad++;
      } catch (const std::invalid_argument& ia) {
        cerr << "Error de formato de número en la línea: " << linea << " - " << ia.what() << endl;
      } catch (const std::out_of_range& oor) {
        cerr << "Número fuera de rango en la línea: " << linea << " - " << oor.what() << endl;
      }
    }
  }
  archivo.close();
  cout << "Bibliotecas cargadas en lista, arbol y tabla hash." << endl;
}

void GestorDeBibliotecas::mostrarTodasLista(){
  cout << "--- Mostrando bibliotecas en lista ---" << endl;
  if (cantidad == 0) {
    cout << "No hay bibliotecas cargadas en la lista." << endl;
  } else {
    listaB.mostrar();
  }
}

void GestorDeBibliotecas::mostrarTodasArbolIndorden(){
  cout << "--- Mostrando bibliotecas en arbol (inorden) ---" << endl;
  if (cantidad == 0) {
    cout << "No hay bibliotecas cargadas en el arbol." << endl;
  } else {
    arbolB.mostrarRecorridoInorden(); 
  }
}

GestorDeBibliotecas::~GestorDeBibliotecas(){
    // Los destructores se llaman automáticamente
    // No es necesario llamarlos explícitamente
}

Biblioteca* GestorDeBibliotecas::buscarPorCodigo(const string &codigo) {
    // Búsqueda usando tabla hash - O(1) promedio
    Biblioteca resultado = tablaHash.buscar(codigo);
    if (resultado.getCodigoBiblioteca() == codigo) {
        return new Biblioteca(resultado);
    }
    return nullptr; 
}

// Búsqueda usando lista - O(n) para comparación
Biblioteca* GestorDeBibliotecas::buscarPorCodigoLista(const string &codigo) {
    for (int i = 1; i <= listaB.obtener_largo(); ++i) { 
        Biblioteca* b = listaB.buscar(i); 
        if (b && b->getCodigoBiblioteca() == codigo) {
            return b;
        }
    }
    return nullptr; 
}

// Búsqueda usando árbol ABB - O(log n) promedio
Biblioteca* GestorDeBibliotecas::buscarPorCodigoArbol(const string &codigo) {
    return arbolB.buscar(codigo);
}

// Comparar rendimiento entre búsqueda hash, lista y árbol
void GestorDeBibliotecas::compararRendimientoBusqueda(const string &codigo) {
    cout << "\n--- Comparacion de Rendimiento de Busqueda ---" << endl;
    cout << "Buscando biblioteca con codigo: " << codigo << endl;
    
    // Búsqueda en tabla hash
    auto inicioHash = chrono::high_resolution_clock::now();
    Biblioteca* resultadoHash = buscarPorCodigo(codigo);
    auto finHash = chrono::high_resolution_clock::now();
    auto duracionHash = chrono::duration_cast<chrono::nanoseconds>(finHash - inicioHash);
    
    // Búsqueda en lista
    auto inicioLista = chrono::high_resolution_clock::now();
    Biblioteca* resultadoLista = buscarPorCodigoLista(codigo);
    auto finLista = chrono::high_resolution_clock::now();
    auto duracionLista = chrono::duration_cast<chrono::nanoseconds>(finLista - inicioLista);
    
    // Búsqueda en árbol ABB
    auto inicioArbol = chrono::high_resolution_clock::now();
    Biblioteca* resultadoArbol = buscarPorCodigoArbol(codigo);
    auto finArbol = chrono::high_resolution_clock::now();
    auto duracionArbol = chrono::duration_cast<chrono::nanoseconds>(finArbol - inicioArbol);
    
    cout << "\nResultados:" << endl;
    if (resultadoHash) {
        cout << "✓ Encontrada en tabla hash en " << duracionHash.count() << " nanosegundos" << endl;
        cout << "  Biblioteca: " << resultadoHash->getNombre() << endl;
    } else {
        cout << "✗ No encontrada en tabla hash" << endl;
    }
    
    if (resultadoLista) {
        cout << "✓ Encontrada en lista en " << duracionLista.count() << " nanosegundos" << endl;
        cout << "  Biblioteca: " << resultadoLista->getNombre() << endl;
    } else {
        cout << "✗ No encontrada en lista" << endl;
    }
    
    if (resultadoArbol) {
        cout << "✓ Encontrada en arbol ABB en " << duracionArbol.count() << " nanosegundos" << endl;
        cout << "  Biblioteca: " << resultadoArbol->getNombre() << endl;
    } else {
        cout << "✗ No encontrada en arbol ABB" << endl;
    }
    
    if (resultadoHash && resultadoLista && resultadoArbol) {
        cout << "\n--- Analisis de Rendimiento ---" << endl;
        
        // Encontrar el más rapido
        long long tiempoMin = min({duracionHash.count(), duracionLista.count(), duracionArbol.count()});
        string masRapido;
        
        if (tiempoMin == duracionHash.count()) {
            masRapido = "tabla hash";
            cout << "🏆 MAS RAPIDO: Tabla Hash (" << duracionHash.count() << " ns)" << endl;
            cout << "   vs Lista: " << fixed << setprecision(2) << (double)duracionLista.count() / duracionHash.count() << "x mas lenta" << endl;
            cout << "   vs Arbol: " << fixed << setprecision(2) << (double)duracionArbol.count() / duracionHash.count() << "x mas lento" << endl;
        } else if (tiempoMin == duracionArbol.count()) {
            masRapido = "arbol ABB";
            cout << "🏆 MAS RAPIDO: Arbol ABB (" << duracionArbol.count() << " ns)" << endl;
            cout << "   vs Hash: " << fixed << setprecision(2) << (double)duracionHash.count() / duracionArbol.count() << "x mas lento" << endl;
            cout << "   vs Lista: " << fixed << setprecision(2) << (double)duracionLista.count() / duracionArbol.count() << "x mas lenta" << endl;
        } else {
            masRapido = "lista";
            cout << "🏆 MAS RAPIDO: Lista (" << duracionLista.count() << " ns)" << endl;
            cout << "   vs Hash: " << fixed << setprecision(2) << (double)duracionHash.count() / duracionLista.count() << "x mas lento" << endl;
            cout << "   vs Arbol: " << fixed << setprecision(2) << (double)duracionArbol.count() / duracionLista.count() << "x mas lento" << endl;
        }
        
        cout << "\nComplejidad teorica:" << endl;
        cout << "• Tabla Hash: O(1) promedio" << endl;
        cout << "• Arbol ABB: O(log n) promedio" << endl;
        cout << "• Lista: O(n)" << endl;
        
        if (masRapido == "lista") {
            cout << "\nNota: Con pocos elementos, la lista puede ser mas rapida debido a la sobrecarga de las estructuras complejas." << endl;
        }
    }
    
    delete resultadoHash;
    delete resultadoArbol;
}

void GestorDeBibliotecas::mostrarEstadisticasHash() {
    cout << "\n--- Estadisticas de la Tabla Hash ---" << endl;
    cout << "Elementos almacenados: " << tablaHash.obtenerElementos() << endl;
    cout << "Capacidad total: " << tablaHash.obtenerCapacidad() << endl;
    cout << "Factor de carga: " << fixed << setprecision(3) << tablaHash.factor_carga() << endl;
    
    if (tablaHash.factor_carga() > 0.75) {
        cout << "⚠️  Factor de carga alto - se recomienda rehashing" << endl;
    } else if (tablaHash.factor_carga() < 0.25) {
        cout << "ℹ️  Factor de carga bajo - tabla poco utilizada" << endl;
    } else {
        cout << "✅ Factor de carga optimo" << endl;
    }
    cout << endl;
    cout << "\n--- Mostrando la tabla  ---" << endl;
    tablaHash.mostrar();
}

void GestorDeBibliotecas::agregar(const Biblioteca &biblio) {
    if (buscarPorCodigo(biblio.getCodigoBiblioteca()) != nullptr) {
        cout << "Error: Ya existe una biblioteca con el codigo " << biblio.getCodigoBiblioteca() << endl;
        return;
    }
    listaB.alta(biblio, 1); // Agregamos a la lista
    arbolB.insertar(biblio); // Agregamos al árbol
    tablaHash.insertar(biblio.getCodigoBiblioteca(), biblio); // Agregamos a la tabla hash
    cantidad++;
    cout << "Biblioteca " << biblio.getNombre() << " agregada correctamente." << endl;
}

bool GestorDeBibliotecas::eliminar(const string &codigo) {
    // 1. Buscar en la lista para obtener la posición y el objeto
    int posicionEnLista = -1;
    string nombreBiblioEliminar = ""; 

    for (int i = 1; i <= listaB.obtener_largo(); ++i) {
        Biblioteca* b = listaB.buscar(i);
        if (b && b->getCodigoBiblioteca() == codigo) {
            posicionEnLista = i;
            nombreBiblioEliminar = b->getNombre(); 
            break;
        }
    }

    if (posicionEnLista == -1) {
        cout << "No se encontro ninguna biblioteca con el codigo: " << codigo << endl;
        return false;
    }

    // 2. Eliminar de todas las estructuras
    listaB.baja(posicionEnLista); 
    cout << "Biblioteca '" << nombreBiblioEliminar << "' eliminada de la lista." << endl;

    // 3. Eliminar del Árbol
    if (arbolB.eliminar(codigo)) {
        cout << "Biblioteca '" << nombreBiblioEliminar << "' eliminada del arbol." << endl;
    } else {
        cout << "Advertencia: No se pudo eliminar la biblioteca del arbol." << endl;
    }

    // 4. Eliminar de la tabla hash
    tablaHash.borrar(codigo);
    cout << "Biblioteca '" << nombreBiblioEliminar << "' eliminada de la tabla hash." << endl;

    cantidad--; // Decrementar el contador de bibliotecas
    return true;
}

void GestorDeBibliotecas::agregarNuevaBiblioteca(string nombreArchivo) {
    cout << "\n--- Agregar Nueva Biblioteca ---" << endl;
    string codigo, nombre, ciudad;
    float superficie;
    int cantidadLibros, cantidadUsuarios;

    cout << "Ingrese codigo de la biblioteca: ";
    cin >> codigo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada

    // Verificar si el código ya existe
    if (buscarPorCodigo(codigo) != nullptr) {
        cout << "Error: Ya existe una biblioteca con el codigo '" << codigo << "'." << endl;
        return;
    }

    cout << "Ingrese nombre: ";
    getline(cin, nombre);

    cout << "Ingrese ciudad: ";
    getline(cin, ciudad);

    cout << "Ingrese superficie (ej. 0.55): ";
    while (!(cin >> superficie)) {
        cout << "Entrada invalida. Por favor, ingrese un numero para la superficie: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer

    cout << "Ingrese cantidad de libros: ";
    while (!(cin >> cantidadLibros)) {
        cout << "Entrada invalida. Por favor, ingrese un numero entero para la cantidad de libros: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer

    cout << "Ingrese cantidad de usuarios: ";
    while (!(cin >> cantidadUsuarios)) {
        cout << "Entrada invalida. Por favor, ingrese un numero entero para la cantidad de usuarios: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer

    Biblioteca nuevaBiblio(codigo, nombre, ciudad, superficie, cantidadLibros, cantidadUsuarios);
    agregar(nuevaBiblio); // Usamos el método 'agregar' para insertarla en la lista y el árbol.

    // Guardar los datos actualizados en el archivo
    guardarEnArchivo(nombreArchivo);
}

void GestorDeBibliotecas::eliminarBibliotecaPorCodigo(string nombreArchivo) {
    cout << "\n--- Eliminar Biblioteca ---" << endl;
    string codigoAEliminar;
    cout << "Ingrese el codigo de la biblioteca a eliminar: ";
    cin >> codigoAEliminar;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (eliminar(codigoAEliminar)) { // Llama al método eliminar principal
        cout << "Biblioteca eliminada exitosamente." << endl;
        // Si se eliminó de las estructuras en memoria, guardar en archivo
        guardarEnArchivo(nombreArchivo);
    } else {
        cout << "No se pudo eliminar la biblioteca (revisar el codigo ingresado)." << endl;
    }
}

void GestorDeBibliotecas::guardarEnArchivo(string nombreArchivo) {
    string rutaArchivo = "archivos/" + nombreArchivo;
    ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo para escritura: " << rutaArchivo << endl;
        return;
    }

    for (int i = 1; i <= listaB.getCantidad(); ++i) {
        Biblioteca* b = listaB.buscar(i);
        if (b) {
            archivo << b->getCodigoBiblioteca() << "\t"
                    << b->getNombre() << "\t"
                    << b->getCiudad() << "\t"
                    << fixed << setprecision(2) << b->getSuperficie() << "\t"
                    << b->getCantidadLibros() << "\t"
                    << b->getCantidadUsuarios() << endl;
        }
    }
    archivo.close();
    cout << "Datos de bibliotecas guardados en " << rutaArchivo << endl;
}

void GestorDeBibliotecas::consultarCaminoMinimo() {
    cout << "\n--- Consultar Camino Mínimo entre Bibliotecas ---" << endl;
    
    // Primero cargar el grafo si no está cargado
    string archivoDistancias = "archivos/distanciasEntreBibliotecas.txt";
    gDb.cargarDesdeArchivo(archivoDistancias);
    
    // Calcular las distancias mínimas usando Floyd-Warshall
    gDb.calcularDistMinFloydWarshall();
    
    // Mostrar las matrices de distancias y recorridos
    cout << "\n--- MATRICES DE DISTANCIAS Y RECORRIDOS ---" << endl;
    gDb.mostrarMatricesDistanciasYRecorridos();
    
    string bibliotecaOrigen, bibliotecaDestino;
    
    cout << "Ingrese el codigo de la biblioteca de origen: ";
    cin >> bibliotecaOrigen;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Ingrese el codigo de la biblioteca de destino: ";
    cin >> bibliotecaDestino;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // Verificar que ambas bibliotecas existan en el sistema
    Biblioteca* origen = buscarPorCodigo(bibliotecaOrigen);
    Biblioteca* destino = buscarPorCodigo(bibliotecaDestino);
    
    if (!origen) {
        cout << "Error: No se encontro la biblioteca de origen '" << bibliotecaOrigen << "'" << endl;
        return;
    }
    
    if (!destino) {
        cout << "Error: No se encontro la biblioteca de destino '" << bibliotecaDestino << "'" << endl;
        return;
    }
    
    cout << "\n--- Informacion del Camino ---" << endl;
    cout << "Origen: " << origen->getNombre() << " (" << origen->getCiudad() << ")" << endl;
    cout << "Destino: " << destino->getNombre() << " (" << destino->getCiudad() << ")" << endl;
    cout << endl;
    
    // Consultar el camino mínimo usando el grafo
    gDb.consultarDistMin(bibliotecaOrigen, bibliotecaDestino);
    
    cout << "\n--- Recomendacion ---" << endl;
    cout << "Este es el camino optimo para devolver el libro desde " << origen->getNombre();
    cout << " hasta " << destino->getNombre() << "." << endl;
}


void GestorDeBibliotecas::ordenarBibliotecasPorLibros() {
    listaB.ordenarPorSeleccion(Biblioteca::compararPorLibros);
}

void GestorDeBibliotecas::ordenarBibliotecasPorSuperficie() {
    listaB.ordenarPorSeleccion(Biblioteca::compararPorSuperficie);
}

void GestorDeBibliotecas::ordenarBibliotecasPorUsuarios() {
    listaB.ordenarPorSeleccion(Biblioteca::compararPorUsuarios);
}