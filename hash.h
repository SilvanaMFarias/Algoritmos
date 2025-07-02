#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class NodoHash{
private:
	string clave;
	T valor;
    bool borrado;
    template <typename U>
    friend class Hash;
public:
    
	NodoHash(string clave, T valor) {
		this->clave = clave;
		this->valor = valor;
		this->borrado = false;
	}
	string obtenerClave() {
		return this->clave;
	}

	T obtenerValor() {
		return this->valor;
	}
    void marcarComoBorrado() { 
        borrado = true; 
        clave = "";
        valor = T{}; 
    }
    bool fueBorrado() {
        return this->borrado;
    }

};
template <typename T>

class Hash {
private:
    int capacidad, elementos;
    NodoHash<T>** arreglo;
    vector<int> primos = { 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229};

    int folding(string clave) {
	    int parte1 = 0, parte2 = 0;
	    int mitad = (int)clave.length() / 2;

	    for (int i = 0; i < (int)clave.length(); i++) {
		    if (i < mitad ) {
			    parte1 += (int)clave[i];
		    }
		    else {
			    parte2 += (int)clave[i];
		    }
	    }
	    return abs( (128 * parte1) ^ parte2);
    }
    int funcionHash(string clave) {
	    return this->folding(clave) % this->capacidad;
    }
    int siguientePrimo(int numero) {
        for(int i = 0; i < (int)this->primos.size(); i++) {
            if(this->primos[i] >= numero) {
                return this->primos[i];
            }
        }
        return numero;
    }
    void rehash(int nuevaCapacidad){
        NodoHash<T>** viejo = this->arreglo;
        int copia_capacidad = this->capacidad;

        this->capacidad = nuevaCapacidad;
        this->elementos = 0;
        this->arreglo = new NodoHash<T>*[nuevaCapacidad];
        for (int i = 0; i < nuevaCapacidad; i++) {
            this->arreglo[i] = nullptr;
        }

        for (int i = 0; i < copia_capacidad; i++) {
            if (viejo[i] != nullptr && !viejo[i]->fueBorrado()) {
                this->insertar(viejo[i]->obtenerClave(), viejo[i]->obtenerValor());
            }

            if (viejo[i] != nullptr) {
                delete viejo[i];
            }
        }
        delete[] viejo;
    }

public:
    Hash(int elementos = 3) {
        int tamanio = std::round(elementos / 0.75);
        this->capacidad = this->siguientePrimo(tamanio);
        this->elementos = 0;
        this->arreglo = new NodoHash<T>*[this->capacidad];
        for (int i = 0; i < this->capacidad; i++) {
            this->arreglo[i] = nullptr;
        }
    }

    ~Hash() {
	    for (int i = 0; i < capacidad; i++) {
		    if (arreglo[i] != nullptr) {
                delete arreglo[i];
            }
	    }
	    delete[] arreglo;
    }
    int obtenerCapacidad() {
        return this->capacidad;
    }
    int obtenerElementos() {
        return this->elementos;
    }
    void insertar(string clave, T valor) {
        int indice = this->funcionHash(clave);
        int aux = indice;
        if((double)(this->elementos + 1)/(double)this->capacidad >= 0.75) {

            this->rehash(this->siguientePrimo(this->elementos * 2));
        }
        while(this->arreglo[indice] != nullptr && !this->arreglo[indice]->fueBorrado()) {
            if(this->arreglo[indice]->obtenerClave() == clave) {
                delete this->arreglo[indice];
                this->arreglo[indice] = new NodoHash<T>(clave, valor);
                
                return;
            }
            indice = (indice + 1) % this->capacidad;

            if(aux == indice) {
                return;
            }
            
        }
        if(this->arreglo[indice] != nullptr && this->arreglo[indice]->fueBorrado()) {
            delete this->arreglo[indice];
        }
        this->arreglo[indice] = new NodoHash<T>(clave, valor);
        this->elementos++;
    }
    T buscar(string clave) {
        int indice = this->funcionHash(clave);
        int aux = indice;
        while(this->arreglo[indice] != nullptr){
            if (!this->arreglo[indice]->fueBorrado() && this->arreglo[indice]->obtenerClave() == clave) {
                return this->arreglo[indice]->obtenerValor();
            }
            indice = (indice + 1) % this->capacidad;

            if (indice == aux) {
                
                return {};
            }
        }
        
        return {};
    }

    void borrar(string clave) {
        int indice = this->funcionHash(clave);
        int aux = indice;
        while(this->arreglo[indice] != nullptr){
            if (!this->arreglo[indice]->fueBorrado() && this->arreglo[indice]->obtenerClave() == clave) {
                this->arreglo[indice]->marcarComoBorrado();
                this->elementos--;
                return;
            }
            indice = (indice + 1) % this->capacidad;

            if (indice == aux) {
            break;
            }
        }
    }
    double factor_carga() {
        return (double)this->elementos / (double)this->capacidad;
    } 

    int obtenerIndice(string clave) {
        int indice = this->funcionHash(clave);
        int aux = indice;
        while(this->arreglo[indice] != nullptr){
            if (!this->arreglo[indice]->fueBorrado() && this->arreglo[indice]->obtenerClave() == clave) {
                return indice;
            }
            indice = (indice + 1) % this->capacidad;

            if (indice == aux) {
            break;
            }
        }
        return {};
    }
    void mostrar() {
        cout << "(Elementos: " << this->elementos << " | Capacidad: " << this->capacidad << "| Factor Carga: " << this->factor_carga() << ")" << endl;
        for (int i = 0; i < this->capacidad; i++) {
            if (this->arreglo[i] == nullptr) {
                cout << "[  Libre  ]" << endl;
                } else if (this->arreglo[i]->fueBorrado()) {
                cout << "[ Borrado ]" << endl;
                } else {
                cout << "(  " << this->arreglo[i]->obtenerClave() << "  )" << endl;
            }
        }
        cout << endl; 
    }
};
#endif // HASH_H_INCLUDED