# 📚 Sistema de Gestión de Bibliotecas Universitarias

## Descripción del Proyecto

Este es un sistema completo de gestión de bibliotecas universitarias desarrollado en C++ que implementa múltiples estructuras de datos para optimizar diferentes tipos de operaciones:

- **Listas enlazadas** para recorridos secuenciales
- **Árboles binarios de búsqueda (ABB)** para búsquedas ordenadas
- **Tabla hash** para búsquedas O(1) por código de biblioteca
- **Grafos** para calcular caminos mínimos entre bibliotecas usando Floyd-Warshall

## 🏗️ Estructura del Proyecto

```
Algoritmos/
├── archivos/                          # Archivos de datos
│   ├── bibliotecas.txt               # Datos de bibliotecas
│   ├── prestamos.txt                 # Datos de préstamos
│   ├── distanciasEntreBibliotecas.txt # Matriz de distancias
│   └── bibliotecas-rendimiento.txt   # Datos para pruebas de rendimiento
├── *.cpp                             # Archivos fuente
├── *.h                               # Archivos de cabecera
├── main.cpp                          # Programa principal
└── README.md                         # Este archivo
```

## 📋 Requisitos del Sistema

- **Compilador**: g++ (GNU C++ Compiler) versión 7.0 o superior
- **Estándar C++**: C++17
- **Sistema Operativo**: Linux, macOS, o Windows con WSL
- **Memoria**: Mínimo 512MB RAM

## 🔧 Compilación

### Compilación Principal (Recomendada)
```bash
g++ -Wall -Wextra -std=c++17 biblioteca.cpp gestorDeBibliotecas.cpp grafoDistBibliotecas.cpp prestamo.cpp ABB.cpp GestorDePrestamos.cpp main.cpp -o programa
```

### Compilación de Pruebas del Grafo
```bash
g++ -Wall -Wextra -std=c++17 grafoDistBibliotecas.cpp main2.cpp -o programa
```

### Opciones de Compilación
- `-Wall -Wextra`: Habilita todas las advertencias del compilador
- `-std=c++17`: Usa el estándar C++17
- `-o programa`: Nombre del ejecutable resultante

## 🚀 Ejecución

```bash
./programa
```

## 📊 Funcionalidades del Sistema

### Gestión de Bibliotecas
1. **Cargar bibliotecas desde archivo** - Carga datos desde `archivos/bibliotecas.txt`
2. **Mostrar bibliotecas (lista)** - Muestra todas las bibliotecas en formato lista
3. **Mostrar bibliotecas (árbol inorden)** - Muestra bibliotecas ordenadas por código
4. **Agregar nueva biblioteca** - Permite agregar una biblioteca manualmente
5. **Eliminar biblioteca por código** - Elimina una biblioteca del sistema
6. **Buscar biblioteca por código (HASH)** - Búsqueda O(1) usando tabla hash
7. **Comparar rendimiento de búsqueda** - Compara hash vs lista vs árbol
8. **Mostrar estadísticas de tabla hash** - Información sobre la tabla hash

### Gestión de Préstamos
9. **Cargar préstamos desde archivo** - Carga desde `archivos/prestamos.txt`
10. **Mostrar préstamos (lista)** - Muestra todos los préstamos
11. **Mostrar préstamos (árbol inorden)** - Muestra préstamos ordenados

### Análisis Avanzado
12. **Consultar camino mínimo entre bibliotecas** - Usa Floyd-Warshall
13. **Total de préstamos por biblioteca en rango de fechas**
14. **Detectar bibliotecas con alta carga (semana)**
15. **Buscar préstamos de usuario por ISBN**

### Ordenamiento
16. **Ordenar bibliotecas por cantidad de libros**
17. **Ordenar bibliotecas por superficie**
18. **Ordenar bibliotecas por cantidad de usuarios**

## 📁 Formato de Archivos

### bibliotecas.txt
```
CODIGO_BIBLIOTECA	NOMBRE	CIUDAD	SUPERFICIE	CANT_LIBROS	CANT_USUARIOS
```
**Ejemplo:**
```
UNAHUR	Biblioteca Miguel Cervantes	VILLA TESEI	0.35	17800	950
FCE	Biblioteca Economicas	CABA	0.85	24500	1200
```

### prestamos.txt
```
CODIGO_BIBLIOTECA	ISBN	ID_USUARIO	FECHA_YYYYMMDD
```
**Ejemplo:**
```
UNAHUR	9780131103525	44	20250311
FCE	9780131103627	56	20250412
```

### distanciasEntreBibliotecas.txt
```
BIBLIOTECA_ORIGEN	BIBLIOTECA_DESTINO	DISTANCIA_KM
```
**Ejemplo:**
```
UNAHUR	FCE	1
FADU	UNLAM	5.5
```

## 🔍 Estructuras de Datos Implementadas

### Para Bibliotecas
- **Lista enlazada**: Recorridos secuenciales y operaciones básicas
- **Árbol binario de búsqueda (ABB)**: Búsquedas ordenadas por código
- **Tabla hash**: Búsquedas O(1) por código de biblioteca
- **Grafo**: Cálculo de caminos mínimos entre bibliotecas

### Para Préstamos
- **Lista enlazada**: Recorridos y búsquedas lineales
- **Árbol binario de búsqueda (ABB)**: Recorridos ordenados

## 📈 Análisis de Complejidad

| Operación | Complejidad | Estructura |
|-----------|-------------|------------|
| Búsqueda por código | O(1) | Tabla hash |
| Búsqueda por código | O(log n) | Árbol ABB |
| Búsqueda por código | O(n) | Lista |
| Búsqueda de préstamos | O(n) | Lista |
| Camino mínimo | O(n³) | Floyd-Warshall |
| Inserción | O(1) | Lista |
| Inserción | O(log n) | Árbol ABB |

## 🛠️ Solución de Problemas

### Error de Compilación
```bash
# Si hay errores de compilación, verifica:
g++ --version  # Debe ser 7.0 o superior
```

### Error de Archivos
- Asegúrate de que los archivos estén en la carpeta `archivos/`
- Verifica que los archivos tengan permisos de lectura
- Comprueba el formato de los archivos (tabulaciones como separadores)

### Bucle Infinito en Búsquedas
- El sistema incluye validación robusta de entrada
- Si persiste, verifica que los archivos de datos no estén corruptos

## 🧪 Pruebas Recomendadas

1. **Cargar bibliotecas** (opción 1) → **Mostrar lista** (opción 2)
2. **Cargar préstamos** (opción 4) → **Mostrar lista** (opción 5)
3. **Buscar biblioteca por código** (opción 10) - Prueba con "UNAHUR"
4. **Comparar rendimiento** (opción 11) - Ver diferencias de velocidad
5. **Camino mínimo** (opción 9) - Prueba con "UNAHUR" y "UNLAM"
6. **Análisis de préstamos** (opciones 16-18)

## 📝 Notas Importantes

- **Siempre carga los datos** (opciones 1 y 4) antes de usar otras funcionalidades
- **Las fechas** deben estar en formato YYYYMMDD (ej: 20250311)
- **Los códigos de biblioteca** son sensibles a mayúsculas/minúsculas
- **La tabla hash** se inicializa automáticamente con un tamaño primo optimizado

## 🤝 Contribuciones

Para reportar bugs o sugerir mejoras:
1. Verifica que el problema no esté en la documentación
2. Proporciona información sobre tu sistema operativo y versión de g++
3. Incluye el mensaje de error exacto si aplica

---

**Desarrollado para el Trabajo Práctico Integrador de Algoritmos**  
*Sistema completo de gestión de bibliotecas con múltiples estructuras de datos*