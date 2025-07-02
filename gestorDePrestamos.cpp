#include "GestorDePrestamos.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <iomanip>
#include <limits>
using namespace std;

void GestorDePrestamos::cargarDesdeArchivo(string nombreArchivo) {
  cantidad = 0;
  string linea;
  ifstream archivoPrestamos("archivos/" + nombreArchivo);
  if (!archivoPrestamos.is_open()) {
    cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
    return;
  }

  while (getline(archivoPrestamos, linea)) {
    stringstream ss(linea);
    string codigoBiblioteca, isbn, usuarioIdStr, fechaDiaStr;

    if (getline(ss, codigoBiblioteca, '\t') &&
      getline(ss, isbn, '\t') &&
      getline(ss, usuarioIdStr, '\t') &&
      getline(ss, fechaDiaStr)) {

    int usuarioId = stoi(usuarioIdStr);
    int fechaDia = stoi(fechaDiaStr);

    Prestamo *p = new Prestamo(codigoBiblioteca, isbn, usuarioId, fechaDia);
    listaP.alta(*p, 1);
    arbolP.insertar(*p);
    cantidad++;
    }
  }
  archivoPrestamos.close();
  cout << "Prestamos cargados: " << cantidad << endl;
}

void GestorDePrestamos::mostrarTodosLista(){
  cout << "Mostrando lista: " << endl;
  listaP.mostrar();
}

void GestorDePrestamos::mostrarTodosArbolIndorden(){
  cout << "Mostrando arbol inorden: " << endl;
  arbolP.mostrarRecorridoInorden();
}

map<string,int> GestorDePrestamos::prestamos(int fecha1,int fecha2)
{//complejidad de lineal de 1N
  map<string, int> diccionarioBiblioteca;

  for(int i=1; i<=listaP.obtener_largo();i++)
  {
    
    if((listaP.consulta(i).getFechaDia()>=fecha1) && (listaP.consulta(i).getFechaDia()<=fecha2))
    {
      if(diccionarioBiblioteca.count(listaP.consulta(i).getCodigoBiblioteca()))
      {
        diccionarioBiblioteca.at(listaP.consulta(i).getCodigoBiblioteca())++;
      }
      else
      {
        diccionarioBiblioteca.insert({listaP.consulta(i).getCodigoBiblioteca(),1});
      }
    }
  }
  return diccionarioBiblioteca;
}

void GestorDePrestamos::cantidadPrestamo(int fecha1, int fecha2)
{//la complejidad es lineal 2*N, y se puede mejorar
  
  for(auto elem:this->prestamos(fecha1,fecha2))
  {
    cout<<"codigo biblioteca: "<< elem.first <<" cantidad de prestamo: "<<elem.second << "\n";
  }
}

void GestorDePrestamos::cargaDePrestamo(int carga, int yyyymmdd)
{
  int day = yyyymmdd % 100;
  int month = (yyyymmdd / 100) % 100;
  int year = yyyymmdd / 10000;

  tm timeinfo = {}; // Initialize to all zeros
  timeinfo.tm_year = year - 1900; // tm_year is years since 1900
  timeinfo.tm_mon = month - 1;   // tm_mon is 0-indexed (0-11)
  timeinfo.tm_mday = day;
  timeinfo.tm_mday -=7;

  int semana = (timeinfo.tm_year+1900)*1000+timeinfo.tm_mon*100+timeinfo.tm_mday;

  for(auto elem:this->prestamos(semana,yyyymmdd))
  {
    if(elem.second>=carga)
    {
      cout<<"codigo biblioteca: "<< elem.first <<" cantidad de prestamo: "<<elem.second << "\n";
    }
  }
}

void GestorDePrestamos::buscarPrestamo(string isbn)
{//complejidad lineal de N 
  for(int i=1; i<=listaP.obtener_largo();i++)
  {
    if(listaP.consulta(i).getIsbn()==isbn)
    {
      listaP.consulta(i).mostrarInformacion();
    }
  }
}

// ========== FUNCIONALIDADES DE ANALISIS DE PRESTAMOS ==========

void GestorDePrestamos::mostrarComplejidadAlgoritmica(string operacion, string complejidad, string explicacion) {
    cout << "\n📊 ANALISIS DE COMPLEJIDAD ALGORITMICA" << endl;
    cout << "Operacion: " << operacion << endl;
    cout << "Complejidad: " << complejidad << endl;
    cout << "Explicacion: " << explicacion << endl;
    cout << "=========================================" << endl;
}

int GestorDePrestamos::convertirFechaStringAInt(string fecha) {
    // Formato esperado: "YYYY-MM-DD" o "YYYYMMDD"
    string fechaLimpia = "";
    for (char c : fecha) {
        if (isdigit(c)) {
            fechaLimpia += c;
        }
    }
    return stoi(fechaLimpia);
}

string GestorDePrestamos::convertirFechaIntAString(int fecha) {
    int year = fecha / 10000;
    int month = (fecha / 100) % 100;
    int day = fecha % 100;
    
    stringstream ss;
    ss << setfill('0') << setw(4) << year << "-" 
       << setfill('0') << setw(2) << month << "-" 
       << setfill('0') << setw(2) << day;
    return ss.str();
}

// 1. Calcular el total de préstamos por biblioteca en un rango de fechas dado
void GestorDePrestamos::totalPrestamosPorBibliotecaEnRangoDeFechas() {
    if (listaP.obtener_largo() == 0) {
        cout << "❌ No hay préstamos cargados. Primero debe cargar los préstamos (opción 4)." << endl;
        return;
    }
    
    cout << "\n=== TOTAL DE PRESTAMOS POR BIBLIOTECA EN RANGO DE FECHAS ===" << endl;
    
    string fechaInicio, fechaFin;
    cout << "Ingrese fecha de inicio (formato: YYYY-MM-DD o YYYYMMDD): ";
    cin >> fechaInicio;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Ingrese fecha de fin (formato: YYYY-MM-DD o YYYYMMDD): ";
    cin >> fechaFin;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    int fecha1 = convertirFechaStringAInt(fechaInicio);
    int fecha2 = convertirFechaStringAInt(fechaFin);
    
    cout << "\nBuscando préstamos entre " << convertirFechaIntAString(fecha1) 
         << " y " << convertirFechaIntAString(fecha2) << endl;
    
    map<string, int> prestamosPorBiblioteca = prestamos(fecha1, fecha2);
    
    if (prestamosPorBiblioteca.empty()) {
        cout << "No se encontraron préstamos en el rango de fechas especificado." << endl;
    } else {
        cout << "\n📚 RESULTADOS:" << endl;
        cout << setw(15) << left << "Biblioteca" << setw(10) << "Préstamos" << endl;
        cout << string(25, '-') << endl;
        
        int totalPrestamos = 0;
        for (auto& elem : prestamosPorBiblioteca) {
            cout << setw(15) << left << elem.first << setw(10) << elem.second << endl;
            totalPrestamos += elem.second;
        }
        cout << string(25, '-') << endl;
        cout << setw(15) << left << "TOTAL" << setw(10) << totalPrestamos << endl;
    }
    
    mostrarComplejidadAlgoritmica(
        "Total de préstamos por biblioteca en rango de fechas",
        "O(n)",
        "Se recorre toda la lista de préstamos una vez para filtrar por fechas y contar por biblioteca"
    );
}

// 2. Detectar bibliotecas con alta carga (más de X préstamos en una semana)
void GestorDePrestamos::detectarBibliotecasConAltaCarga() {
    if (listaP.obtener_largo() == 0) {
        cout << "❌ No hay préstamos cargados. Primero debe cargar los préstamos (opción 4)." << endl;
        return;
    }
    
    cout << "\n=== DETECTAR BIBLIOTECAS CON ALTA CARGA ===" << endl;
    
    int umbralCarga;
    string fechaReferencia;
    
    cout << "Ingrese el umbral de préstamos para considerar alta carga: ";
    cin >> umbralCarga;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Ingrese fecha de referencia (formato: YYYY-MM-DD o YYYYMMDD): ";
    cin >> fechaReferencia;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    int fechaRef = convertirFechaStringAInt(fechaReferencia);
    
    // Calcular fecha de inicio de la semana (7 días antes)
    int day = fechaRef % 100;
    int month = (fechaRef / 100) % 100;
    int year = fechaRef / 10000;
    
    // Calcular fecha de 7 días antes de manera simple
    day -= 7;
    if (day <= 0) {
        month--;
        if (month <= 0) {
            year--;
            month = 12;
        }
        // Ajustar día según el mes
        if (month == 2) {
            day += 28; // Simplificado, no considera años bisiestos
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            day += 30;
        } else {
            day += 31;
        }
    }
    
    int fechaInicioSemana = year * 10000 + month * 100 + day;
    
    cout << "\nAnalizando semana del " << convertirFechaIntAString(fechaInicioSemana) 
         << " al " << convertirFechaIntAString(fechaRef) << endl;
    cout << "Umbral de alta carga: " << umbralCarga << " préstamos" << endl;
    
    map<string, int> prestamosSemana = prestamos(fechaInicioSemana, fechaRef);
    
    cout << "\n🚨 BIBLIOTECAS CON ALTA CARGA:" << endl;
    cout << setw(15) << left << "Biblioteca" << setw(10) << "Préstamos" << setw(15) << "Estado" << endl;
    cout << string(40, '-') << endl;
    
    bool hayAltaCarga = false;
    for (auto& elem : prestamosSemana) {
        if (elem.second >= umbralCarga) {
            cout << setw(15) << left << elem.first 
                 << setw(10) << elem.second 
                 << setw(15) << "⚠️ ALTA CARGA" << endl;
            hayAltaCarga = true;
        }
    }
    
    if (!hayAltaCarga) {
        cout << "✅ Ninguna biblioteca supera el umbral de alta carga." << endl;
    }
    
    mostrarComplejidadAlgoritmica(
        "Detectar bibliotecas con alta carga",
        "O(n)",
        "Se recorre la lista de préstamos una vez para filtrar por rango de fechas y comparar con umbral"
    );
}

// 3. Buscar todos los préstamos de un usuario por ISBN
void GestorDePrestamos::buscarPrestamosDeUsuarioPorISBN() {
    if (listaP.getCantidad() == 0) {
        cout << "❌ No hay préstamos cargados. Primero debe cargar los préstamos (opción 4)." << endl;
        return;
    }
    
    cout << "\n=== BUSCAR PRESTAMOS DE USUARIO POR ISBN ===" << endl;
    
    int usuarioId;
    string isbn;
    
    cout << "Ingrese el ID del usuario: ";
    while (!(cin >> usuarioId)) {
        cout << "Entrada inválida. Ingrese un número de usuario válido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "Ingrese el ISBN del libro: ";
    getline(cin, isbn);
    while (isbn.empty()) {
        cout << "ISBN vacío. Ingrese el ISBN del libro: ";
        getline(cin, isbn);
    }
    
    cout << "\n🔍 Buscando préstamos del usuario " << usuarioId << " con ISBN " << isbn << endl;
    
    vector<Prestamo> prestamosEncontrados;
    int cantidadPrestamos = listaP.getCantidad();
    if (cantidadPrestamos <= 0) {
        cout << "[DEBUG] La lista de préstamos está vacía o corrupta." << endl;
        return;
    }
    for (int i = 1; i <= cantidadPrestamos; i++) {
        Prestamo prestamo = listaP.consulta(i);
        if (prestamo.getUsuarioId() == usuarioId && prestamo.getIsbn() == isbn) {
            prestamosEncontrados.push_back(prestamo);
        }
    }
    
    if (prestamosEncontrados.empty()) {
        cout << "❌ No se encontraron préstamos para el usuario " << usuarioId 
             << " con ISBN " << isbn << endl;
    } else {
        cout << "\n📖 PRESTAMOS ENCONTRADOS (" << prestamosEncontrados.size() << "):" << endl;
        cout << setw(15) << left << "Biblioteca" << setw(15) << "ISBN" 
             << setw(10) << "Usuario" << setw(12) << "Fecha" << endl;
        cout << string(52, '-') << endl;
        
        for (const Prestamo& prestamo : prestamosEncontrados) {
            cout << setw(15) << left << prestamo.getCodigoBiblioteca()
                 << setw(15) << prestamo.getIsbn()
                 << setw(10) << prestamo.getUsuarioId()
                 << setw(12) << convertirFechaIntAString(prestamo.getFechaDia()) << endl;
        }
    }
    
    mostrarComplejidadAlgoritmica(
        "Buscar préstamos de usuario por ISBN",
        "O(n)",
        "Se recorre toda la lista de préstamos una vez para filtrar por usuario e ISBN"
    );
}

GestorDePrestamos::~GestorDePrestamos(){
  // Los destructores se llaman automáticamente
  // No es necesario llamarlos explícitamente
}