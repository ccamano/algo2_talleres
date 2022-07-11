#include <vector>

template<typename T>
string_map<T>::string_map() : _raiz(NULL), _size(0), _claves({}) {
}

template<typename T>
string_map<T>::string_map(const string_map<T> &aCopiar) : string_map() {
    *this = aCopiar;
}

template<typename T>
string_map<T> &string_map<T>::operator=(const string_map<T> &d) {
    delete _raiz;
    Nodo *nodoActual = d._raiz;
    Nodo *nodoAgregar = _raiz;
    for (int i = 0; i < d._claves.size(); ++i) {
        nodoActual = d._raiz;
        for (int j = 0; j < d._claves[i].size(); ++j) {
            nodoActual = nodoActual->siguientes[int(d._claves[i][j])];
        }
        nodoAgregar = nodoActual;
        pair<string, T> nuevo;
        nuevo.first = d._claves[i];
        nuevo.second = *nodoAgregar->definicion;
        insert(nuevo);
        this->_claves.push_back((nuevo.first));
    }
}


template<typename T>
string_map<T>::~string_map() {
    if (_raiz != NULL) {
        delete _raiz;
    }
    _raiz = NULL;
    _size = 0;
    _claves = {};
}


template<typename T>
void string_map<T>::insert(const pair<string, T> &insertar) {
    if (_raiz == NULL) {
        Nodo *nuevo = new Nodo;
        _raiz = nuevo;
    }
    T *def = new T(insertar.second);
    Nodo *nodoActual = _raiz;
    if (count(insertar.first) == 1) {
        for (int i = 0; i < insertar.first.length(); ++i) {
            nodoActual = nodoActual->siguientes[int(insertar.first[i])];
        }
        if (nodoActual->definicion != NULL) {
            delete nodoActual->definicion;
        }
        nodoActual->definicion = def;
        return;
    }
    for (int i = 0; i < insertar.first.length(); ++i) {
        if (nodoActual->siguientes[int(insertar.first[i])] == NULL) {
            Nodo *siguiente = new Nodo;
            nodoActual->siguientes[int(insertar.first[i])] = siguiente;
            nodoActual = siguiente;
        } else {
            nodoActual = nodoActual->siguientes[int(insertar.first[i])];
        }
    }
    _size++;
    if (nodoActual->definicion != NULL) {
        delete nodoActual->definicion;
    }
    nodoActual->definicion = def;
    _claves.push_back(insertar.first);
}


template<typename T>
int string_map<T>::count(const string &clave) const {

    Nodo *nodoActual = _raiz;
    if (_raiz == NULL) {
        return 0;
    }
    int posicion = 0;
    for (int i = 0; i < clave.length(); ++i) {
        posicion = int(clave[i]);
        if (nodoActual->siguientes[posicion] == NULL) {
            return 0;
        } else {
            nodoActual = nodoActual->siguientes[posicion];
        }
    }
    if (nodoActual->definicion != NULL) {
        return 1;
    } else {
        return 0;
    }
}

template<typename T>
const T &string_map<T>::at(const string &clave) const {
    Nodo *nodoActual = _raiz;
    for (int i = 0; i < clave.length(); ++i) {
        nodoActual = nodoActual->siguientes[int(clave[i])];
    }
    return nodoActual->definicion;
}

template<typename T>
T &string_map<T>::at(const string &clave) {
    // COMPLETAR
    Nodo *nodoActual = _raiz;
    for (int i = 0; i < clave.length(); ++i) {
        nodoActual = nodoActual->siguientes[int(clave[i])];
    }
    return *nodoActual->definicion;
}

template<typename T>
void string_map<T>::erase(const string &clave) {
    _size--;
    if (_size == 0) {
        delete _raiz;
        _raiz = NULL;
        return;
    }

    for (int k = 0; k < _claves.size(); ++k) {
        if (clave == _claves[k]) {
            _claves.erase(_claves.begin() + k);
        }
    }

    Nodo *nodoActual = _raiz;
    Nodo *ultimoNodo = _raiz;
    int ind = 0;

    for (int i = 0; i < clave.size(); ++i) {
        if (nodoActual->definicion != NULL) {
            ultimoNodo = nodoActual;
            ind = i;
        }
        for (int j = 0; j < 256; ++j) {
            if (nodoActual->siguientes[j] != NULL && j != int(clave[i])) {
                ultimoNodo = nodoActual;
                ind = i;
            }
        }
        nodoActual = nodoActual->siguientes[int(clave[i])];
    }

    if (nodoActual->definicion != NULL) {
        delete nodoActual->definicion;
    }
    nodoActual->definicion = NULL;

    for (int l = 0; l < 256; ++l) {
        if (nodoActual->siguientes[l] != NULL) {
            return;
        }
    }

    delete ultimoNodo->siguientes[int(clave[ind])];
    ultimoNodo->siguientes[int(clave[ind])] = nullptr;


}

template<typename T>
int string_map<T>::size() const {
    return _size;
}

template<typename T>
bool string_map<T>::empty() const {
    return _size == 0;
}

template<typename T>
T &string_map<T>::operator[](const string &clave) {
    if (count(clave) == 1) {
        return at(clave);
    } else {
        insert(make_pair(clave, T()));
        return at(clave);
    }
}