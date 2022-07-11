#include "Lista.h"
using namespace std;


template<class T>
Lista<T>::Nodo::Nodo(const T &elem) : valor(elem) , siguiente(NULL), anterior(NULL) {}

//cosas para lista

//CONSTRUCTORES********************
template <typename T>
Lista<T>::Lista() : tamano(0) , primero(NULL) , fin(NULL)  {}

template <typename T>
Lista<T>::Lista(const Lista<T>& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

//DESTRUCTOR*************************
template <typename T>
Lista<T>::~Lista() {
    destruir();
    // Completar
}

template<typename T>
void Lista<T>::destruir() {
    while (primero != NULL) {
        sacarPrimero();
        tamano--;
    }
}

template<typename T>
void Lista<T>::sacarPrimero(){
    Nodo* p = primero;
    if( tamano == 1){
        fin = NULL;
    }
    primero = primero->siguiente;
    delete p;
}


//ASIGNACION************************


template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& aCopiar) {
    destruir();


    for (int i = 0; i < aCopiar.tamano; i++) {
        agregarAtras(aCopiar.iesimo(i));


    }

    return *this;
}



//AGREGAR*********
template <typename T>
void Lista<T>::agregarAdelante(const T& elem) {
Nodo *nuevo = new Nodo(elem);
nuevo->siguiente = primero;
nuevo->anterior = NULL;
if (primero !=NULL){ //si el primero no es vacio, le agrego el nuevo
    primero->anterior = nuevo;
}
primero = nuevo; //si primero era vacio, le manda el nuevo como primero
tamano++;
}

template <typename T>
void Lista<T>::agregarAtras(const T& elem) {
Nodo *nuevo = new Nodo(elem); //creo quel nodo con elem
nuevo->siguiente = NULL;     //le asigno siguiente y anterior null
nuevo->anterior = NULL;

if (!primero){ //si no hay un inicio, el nuevo es el primero
    primero = nuevo;
    tamano++;

}else //si hay primero
    {
    Nodo *final = primero;
    while (final->siguiente != NULL){ //recorre hasta el anteultimo
        final = final->siguiente;
    }
    final->siguiente = nuevo;
    nuevo->anterior = final;
    tamano++;
}
}



template <typename T>
void Lista<T>::eliminar(Nat i) {
    Nodo* inicio = primero;

    if(inicio != NULL){
        if (i == 0){
            Nodo* actual = inicio;
            inicio = inicio->siguiente;
            actual->siguiente = NULL;
            delete actual;
            primero = inicio;
            tamano--;
        }else{
            Nodo* actual = inicio;
            Nodo* aux1;
            Nodo* aux2;
            for (int j = 0; j < i-1 ; j++){
                actual = actual->siguiente;
            }
            aux1 = actual;
            aux2 = actual->siguiente->siguiente;

            actual = actual->siguiente;
            actual->siguiente = NULL;
            delete actual;
            aux1->siguiente = aux2;
            tamano--;

        }
    }



}



template <typename T>
int Lista<T>::longitud() const {

    return tamano;
}

template <typename T>
const T& Lista<T>::iesimo(Nat i) const {
    Nodo* mirandoEste = primero;
    for (int k = 0; k < i; k++){
        mirandoEste = mirandoEste->siguiente;
    }
    return mirandoEste->valor;

}

template <typename T>
T& Lista<T>::iesimo(Nat i) {
    Nodo *mirandoEste = primero;
    for (int k = 0; k < i; k++){
        mirandoEste = mirandoEste->siguiente;
    }
    return mirandoEste->valor;
    // Completar (hint: es igual a la anterior...)

}

template <typename T>
void Lista<T>::mostrar(ostream& o) {
    // Completar
}