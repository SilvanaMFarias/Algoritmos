## Algoritmos - Trabajo práctico integrador


### Compilación con advertencias

# Prueba gestor bibliotecas y préstamos. Solo carga en lista y ABB los archivos

g++ -Wall -Wextra -std=c++17 biblioteca.cpp gestorDeBibliotecas.cpp grafoDistBibliotecas.cpp prestamo.cpp ABB.cpp GestorDePrestamos.cpp main.cpp -o programa

# Prueba carga a archivo distancias entre bibliotecas en grafo. Distancias min  y recorrido

 g++ -Wall -Wextra -std=c++17 grafoDistBibliotecas.cpp main2.cpp -o programa

### Ejecución

./programa