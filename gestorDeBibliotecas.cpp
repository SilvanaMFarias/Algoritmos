#include "GestorDeBibliotecas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

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
        cantidad++;
      } catch (const std::invalid_argument& ia) {
        cerr << "Error de formato de número en la línea: " << linea << " - " << ia.what() << endl;
      } catch (const std::out_of_range& oor) {
        cerr << "Número fuera de rango en la línea: " << linea << " - " << oor.what() << endl;
      }
    }
  }
  archivo.close();
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
    cout << "No hay bibliotecas cargadas en el árbol." << endl;
  } else {
    arbolB.mostrarRecorridoInorden(); 
  }
}

GestorDeBibliotecas::~GestorDeBibliotecas(){
    listaB.~Lista();
  arbolB.~ABB();
}

Biblioteca* GestorDeBibliotecas::buscarPorCodigo(const string &codigo) {
    // Para buscar en la lista (puedes adaptar para buscar en el árbol si es más eficiente)
    // Esto asume que tu clase Lista tiene un iterador o un método para recorrerla.
    // Opcionalmente, podrías buscar directamente en el ABB si el ABB está indexado por código.
    // Para simplificar, buscamos en la lista:
    for (int i = 1; i <= listaB.getCantidad(); ++i) { 
        Biblioteca* b = listaB.buscar(i); 
        if (b && b->getCodigoBiblioteca() == codigo) {
            return b;
        }
    }
    return nullptr; 
}


void GestorDeBibliotecas::agregar(const Biblioteca &biblio) {
    if (buscarPorCodigo(biblio.getCodigoBiblioteca()) != nullptr) {
        cout << "Error: Ya existe una biblioteca con el codigo " << biblio.getCodigoBiblioteca() << endl;
        return;
    }
    listaB.alta(biblio, 1); // Agregamos a la lista
    arbolB.insertar(biblio); // Agregamos al árbol
    cantidad++;
    cout << "Biblioteca " << biblio.getNombre() << " agregada correctamente." << endl;
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


void GestorDeBibliotecas::guardarEnArchivo(string nombreArchivo) {
    string rutaArchivo = "archivos/" + nombreArchivo;
    ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo para escritura: " << rutaArchivo << endl;
        return;
    }

    // Recorrer la lista y escribir cada biblioteca en el archivo
    // Esto asume que tu clase Lista tiene una forma de iterar o un método para obtener todos los elementos.
    // Si tu Lista no tiene un iterador, tendrás que adaptar esto.

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