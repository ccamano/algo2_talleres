#include "Conjunto.h"

class Nodo;

template<class T>
Conjunto<T>::Nodo::Nodo(const T &v) : valor(v) , izq(NULL), der(NULL) {}

template <class T>
Conjunto<T>::Conjunto() : _raiz(NULL) , _cardinal(0) {

}
//--------------
template <class T>
void Conjunto<T>::destruir(Nodo *n){
    if (n){
        destruir(n->izq);
        destruir(n->der);
        delete n;
        _cardinal--;
    }
}

template <class T>
Conjunto<T>::~Conjunto() {
    destruir(_raiz);
}

//------------------
template <class T>
bool Conjunto<T>::perteneceDesde(Nodo *n, const T& clave) const{
    bool pertenencia = false;
    if (n == NULL){
        pertenencia= false;
    }else if (n->valor == clave){
        pertenencia =  true;
    }else if(n->valor > clave){
        pertenencia= perteneceDesde(n->izq, clave);
    }else{
        pertenencia = perteneceDesde(n->der, clave);
    }
    return pertenencia;
}


template <class T>
bool Conjunto<T>::pertenece(const T& clave) const { //raiz siempre se inicia en null

    return perteneceDesde(_raiz,clave);
}

//------------------
template <class T>
void Conjunto<T>::insertarDesde(Nodo *n, const T& clave) {
    if( clave < n->valor){
        if (n->izq != NULL){
            insertarDesde(n->izq, clave);
        }else{
            n->izq = new Nodo(clave);
            _cardinal++;
        }
    } else if( clave > n->valor){
        if (n->der != NULL){
            insertarDesde(n->der, clave);
        }else {
            n->der = new Nodo(clave);
            _cardinal++;
        }
    }
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if (pertenece(clave)) {
        return;
    } else {
        if (_raiz == NULL) {
            _raiz = new Nodo(clave);
            _cardinal++;
        } else {
            insertarDesde(_raiz, clave);
        }
    }
}
//-------------------
template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::Padre(const T& clave){
    Nodo *padre = _raiz;
    Nodo *hijo = _raiz;
    while(hijo->valor != clave){
        if(clave > hijo->valor){
            padre = hijo;
            hijo = hijo->der;
        }else if(clave < hijo->valor){
            padre = hijo;
            hijo = hijo->izq;
        }
    }
    return padre;
}


template <class T>
void Conjunto<T>::removerDesde(Nodo *n, const T &clave, Nodo *padre) {
    if (clave < n->valor) {
        removerDesde(n->izq, clave, n);
        return;
    }
    if (clave > n->valor) {
        removerDesde(n->der, clave, n);
        return;
    }
    if (n->izq != NULL and n->der != NULL) { //caso tiene dos hijos
        n->valor = minimoDesde(n->der);
        removerDesde(n->der, n->valor, n);
        return;
    }

    Nodo *p = padre;
    if (n->izq != NULL) { //caso n tiene un solo hijo izquierdo
        if (p->izq == n) {
            p->izq = n->izq;
        } else {
            p->der = n->izq;
        }
        delete n;
        _cardinal--;

    } else if (n->der != NULL) { //caso b tiene un solo hijo derecho
        if (p->izq == n) {
            p->izq = n->der;
        } else {
            p->der = n->der;
        }
        delete n;
        _cardinal--;

    } else if (n->der == NULL and n->izq == NULL) { //caso es una hoja
        if (p->izq == n) {
            p->izq = NULL;
        } else {
            p->der = NULL;
        }
        delete n;
        _cardinal--;
    }

}

template <class T>
void Conjunto<T>::remover(const T &clave) {
    if (!pertenece(clave)) {
        return;
    }
    if (_raiz == NULL) {
        return;
    }
    if (_cardinal == 1) {
        delete _raiz;
        _raiz = NULL;
        _cardinal--;
        return;
    }
    if (_raiz->valor == clave){
        if(_raiz->der != NULL) {
            _raiz->valor = minimoDesde(_raiz->der);
            removerDesde(_raiz->der, _raiz->valor, _raiz);
        } else {
            Nodo* borrar = _raiz;
            _raiz = _raiz->izq;
            delete borrar;
        }
        return;
    }
    removerDesde(_raiz, clave, NULL);
}



template <class T>
const T& Conjunto<T>::izquierdoActual(const T& clave){ //solo lo puedo usar cuando se que hay nodos hijos izq, que existe la clave y que la raiz no es vacia
    Nodo *recorredor = _raiz;
    Nodo *dameEste = _raiz;
    while( recorredor->valor != clave){
        if (clave > recorredor->valor){
            recorredor = recorredor->der;
        }else{
            dameEste = recorredor;
            recorredor = recorredor->izq;
        }
    }
    return dameEste->valor;
}


 template <class T>
const T& Conjunto<T>::succAux(Nodo *n, const T& clave){
    if (n == NULL){
        return NULL;
    }else{
        if(clave == n->valor){
            if(n->der != NULL){
                return minimoDesde(n->der);
            }else{
                return izquierdoActual(clave);
            }
        }
        if (clave > n->valor){
            return succAux(n->der, clave);
        }else{
            return succAux(n->izq, clave);
        }
    }
}




template <class T>
const T& Conjunto<T>::siguiente(const T& clave) { //si como precondicion me dicen que existe el elemento en el conjunto, tmb existe una raiz

return  succAux(_raiz, clave);
}

//------------------

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo *recorriendo = _raiz;
    Nodo *rec1 = _raiz->izq;
    while (rec1 != NULL) {
        recorriendo = rec1;
        rec1 = rec1->izq;
    }
    return recorriendo->valor;
}

template <class T>
const T& Conjunto<T>::minimoDesde(Nodo *n) const {
    Nodo *recorriendo = n;
    Nodo *rec1 = n->izq;
    while (rec1 != NULL) {
        recorriendo = rec1;
        rec1 = rec1->izq;
    }
    return recorriendo->valor;
}

template <class T>
const T& Conjunto<T>::maximoDesde(Nodo *n) const {
    Nodo *recorriendo = n;
    Nodo *rec1 = n->der;
    while (rec1 != NULL) {
        recorriendo = rec1;
        rec1 = rec1->der;
    }
    return recorriendo->valor;
}


//--------------



template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo *recorriendo = _raiz;
    Nodo *rec1 = _raiz->der;
    while (rec1 != NULL) {
        recorriendo = rec1;
        rec1 = rec1->der;
    }
    return recorriendo->valor;
}

//-------------------------
template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _cardinal;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

