#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;
#define archivo "./archivo.txt"

/* Definir el nodo de la lista de saltos */
template<typename K, typename V>
class nodo {
private:
    int level;  // El más alto aparece en las primeras capas (varios niveles de índice)
    K key;
    V value;
public:
    nodo() = default;
    nodo(const K&, const V&, int);
    K obtenerKey() const;
    V obtenerValue() const;
    void el_val(const V&);

    /*
     * Indica que el nodo actual es el siguiente nodo de todas las capas, el cambio de la capa superior a la capa inferior es el subíndice de matriz -1,
      */
    vector<nodo<K, V>* > sigui_;
};

template<typename K, typename V>
class SLiist {
private:
    int nivel_max;  // Nivel más alto disponible (nivel de índice máximo)
    int nivel_skip;// Nivel de índice más alto actual
    int num_nodos;   
    nodo<K, V>* header;   // nodo principal
    
    // el file
    ofstream file_writer;     
    ifstream file_reader;  

public:
    SLiist(int);
    ~SLiist();

    int obtenerNivel_ran();   // Determina el índice en qué nivel se insertará el elemento.
    nodo<K, V>* crear_nodo(const K&, const V&, int);
    void mostrarSkip();
    void file();
    void cargar_file();
    bool buscar(const K&);
    bool borrar(const K&);
    bool insertar_elemento(const K&, const V&);/* Agrega un elemento, devuelve verdadero en caso de éxito, devuelve falso en caso de falso xd */
    int size();

private:
    void obtenerKeyValue(const string&, string*, string*);
    bool verificar_string(const string&);

public:
    string limite = ":";
};

void error_print(const string&);

template<typename K, typename V>
nodo<K, V>::nodo(const K& k, const V& v, int _level) : key(k), value(v), level(_level) {
    this->sigui_.resize(level + 1, nullptr);
}

template<typename K, typename V>
K nodo<K, V>::obtenerKey() const {
    return key;
}

template<typename K, typename V>
V nodo<K, V>::obtenerValue() const {
    return value;
}

template<typename K, typename V>
void nodo<K, V>::el_val(const V& val) {
    this->value = val;
}

template<typename K, typename V>
SLiist<K, V>::SLiist(int nivel_max) {
    this->nivel_max = nivel_max;
    num_nodos = 0;
    nivel_skip = 0;
    K k;
    V v;
    header = new nodo<K, V>(k, v, nivel_max);
};

template<typename K, typename V>
SLiist<K, V>::~SLiist() {
    if(file_writer.is_open())
        file_writer.close();
    if(file_reader.is_open())
        file_reader.close();
    delete header;
}

template<typename K, typename V>
nodo<K, V>* SLiist<K, V>::crear_nodo(const K& k, const V& v, int level) {
    nodo<K, V>* t = new nodo<K, V>(k, v, level);
    return t;
}

template<typename K, typename V>
bool SLiist<K, V>::insertar_elemento(const K& key, const V& val) {
    nodo<K, V>* actual = header;

    vector<nodo<K, V>* > actualiza(nivel_max + 1, nullptr);
    for(int i = nivel_skip; i >= 0; --i) {// encontrar la posición de inserción
        while(actual->sigui_[i] && actual->sigui_[i]->obtenerKey() < key) {
            actual = actual->sigui_[i];
        }
        actualiza[i] = actual;  // se puede insertar después de la actualización
    }  
    actual = actual->sigui_[0];
    if(actual && actual->obtenerKey() == key) {// el key ya existe
        error_print("Key ya exite!!!.");
        return false;
    }

    // actual == nullptr //llegar al final de la lista enlazada
    // actual != nullptr && actual->obtenerValue() != (>) key //insertar entre actualiza[0] y actual
    if(actual == nullptr || actual->obtenerKey() != key) {
        int random_level = obtenerNivel_ran();
        if(random_level > nivel_skip) {
            for(int i = nivel_skip + 1; i <= random_level; ++i) {
                actualiza[i] = header;  // índice de nuevo nivel
            }
            nivel_skip = random_level;
        }
        // El nodo a insertar // en nivel más alto que existe
        nodo<K, V>* nuevoNodo = crear_nodo(key, val, random_level);
        // insertar nodo
        for(int i = 0; i <= random_level; ++i) {
            nuevoNodo->sigui_[i] = actualiza[i]->sigui_[i];
            actualiza[i]->sigui_[i] = nuevoNodo;
        }
        cout << "Se insertó correctamente!." << endl;
        ++num_nodos;
      }
    return true;
}

template<typename K, typename V>
bool SLiist<K, V>::buscar(const K& key) {
    nodo<K, V>* actual = header;

    // Comience a buscar desde la capa más grande, encuentre el nodo anterior, pase --i, moviendome a la capa inferior y comienzo a buscar
    for(int i = nivel_skip; i >= 0; --i) {
        while(actual->sigui_[i] && actual->sigui_[i]->obtenerKey() < key) {
            actual = actual->sigui_[i];
        }
    }
    actual = actual->sigui_[0];
    if(actual && actual->obtenerKey() == key) {
        cout << "Se encontró: (Key = " << key << ", Value = " << actual->obtenerValue() << ").";
        return true;
    } else {
        error_print("No se encontró el key.");
        return false;
    }
}

// Mostrar el skipList
template<typename K, typename V>
void SLiist<K, V>::mostrarSkip() {
    cout << "\n ///////////////// Skip List: /////////////\n";
    for(int i = nivel_skip; i >= 0; --i) {
        nodo<K, V>* t = header->sigui_[i];
        cout << "NIVEL " << i << ": ";
        while(t) {
            cout << "(" << t->obtenerKey() << ", " << t->obtenerValue() << ") ";
            t = t->sigui_[i];
        }
        cout << endl;
    }
}

//Borrar
template<typename K, typename V> 
bool SLiist<K, V>::borrar(const K& key) {
    nodo<K, V>* actual = header;
    vector<nodo<K, V>* > actualiza(nivel_max + 1, nullptr);

    // Eliminar del índice de nivel más alto
    for(int i = nivel_skip; i >= 0; --i) {
        while (actual->sigui_[i] !=NULL && actual->sigui_[i]->obtenerKey() < key) {
            actual = actual->sigui_[i];
        }
        actualiza[i] = actual;
    }
    actual = actual->sigui_[0];
    
    if(actual && actual->obtenerKey() == key) {
        // eliminar de abajo hacia arriba
        for(int i = 0; i <= nivel_skip; ++i) {
            if(actualiza[i]->sigui_[i] != actual) break;
            actualiza[i]->sigui_[i] = actual->sigui_[i];  // actualiza[i]->sigui_[i]->sigui_[i]
        }// Puede reducir el número de capas de índice
        while(nivel_skip > 0 && header->sigui_[nivel_skip] == nullptr) {//Eliminar niveles que no tienen elementos
            --nivel_skip;
        }
        cout << "Borrado correctamente (" << key << ", " << actual->obtenerValue() << ")" << endl;
        delete actual;
        --num_nodos;
        return true;
    } else {
        error_print("No se encontró el key.");
        return false;
    }
}

// el dump datos en memoria a archivo
template<typename K, typename V>
void SLiist<K, V>::file() {
    file_writer.open(archivo);
    nodo<K, V>* t = header->sigui_[0];
    while(t) {
        file_writer << t->obtenerKey() << ":" << t->obtenerValue() << "\n";
        t = t->sigui_[0];
    }
    file_writer.flush();
    file_writer.close();
}

// Cargar datos 
template<typename K, typename V>
void SLiist<K, V>::cargar_file() {
    file_reader.open(archivo);
    cout << "Cargando File ...\n";
    string line;
    string* key = new string();
    string* value = new string();
    cout << "open_right.\n";
    while(getline(file_reader, line)) {
        obtenerKeyValue(line, key, value);
        if(key->empty() || value->empty()) { continue;}
        
        cout << "load (" << *key << ", " << *value << ")" << endl;//cargamos el key y value con *.punt.
        insertar_elemento(stoi(*key), *value);
    }
    file_reader.close();
}

template<typename K, typename V>
int SLiist<K, V>::size() {
    return num_nodos;
}

template<typename K, typename V>
void SLiist<K, V>::obtenerKeyValue(const string& str, string* key, string* value) {
    if(!verificar_string(str)) return ;
    *key = str.substr(0, str.find(limite));
    *value = str.substr(str.find(limite) + 1, str.length());//limite ":"
}

template<typename K, typename V>
bool SLiist<K, V>::verificar_string(const string& str) {//vacio y pos igual al limite para tener todo el archivo correcto
    if(str.empty()) {
        return false;
    }
    if(str.find(limite) == string::npos) {
        return false;
    }
    return true;
}

template<typename K, typename V>
/*
    El método randomLevel generará aleatoriamente un número entre 1 y nivel_max, y:
        1/2 probabilidad devuelve 0 => No
        1/4 de probabilidad devuelve 1 => índice de primer nivel
        1/8 de probabilidad devuelve 2 y así sucesivamente
 */
int SLiist<K, V>::obtenerNivel_ran() {
    int level = 0;
    while(rand() % 2 && level < nivel_max) {
        ++level;
    }
    return level;
}

void error_print(const string& arg) {//print arg cuando tenga un elemento invalido o similar
    int len = arg.size();
    string cutoffLine('*', len + 5);
    cout << cutoffLine << endl;
    cout << arg << endl;
    cout << cutoffLine << endl;
}





