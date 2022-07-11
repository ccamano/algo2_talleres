#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <string>
#include <iostream>

using namespace std;

template <class T>
class Conjunto
{
    public:

        // Constructor. Genera un conjunto vacío.
        Conjunto();

        // Destructor. Debe dejar limpia la memoria.
        ~Conjunto();

        // Inserta un elemento en el conjunto. Si este ya existe,
        // el conjunto no se modifica.
        void insertar(const T&);

        // Decide si un elemento pertenece al conjunto o no.
        bool pertenece(const T&) const;

        // Borra un elemento del conjunto. Si este no existe,
        // el conjunto no se modifica.
        void remover(const T& );

        // Siguiente elemento al recibido por párametro, en orden.
        //el sucesor del elemento
        const T& siguiente(const T& elem);

        // Devuelve el mínimo elemento del conjunto según <.
        const T& minimo() const;

        // Devuelve el máximo elemento del conjunto según <.
        const T& maximo() const;

        // Devuelve la cantidad de elementos que tiene el conjunto.
        unsigned int cardinal() const;

        // Muestra el conjunto.
        void mostrar(std::ostream&) const;




    private:


        /**
         * Completar con lo que sea necesario...
         **/

        struct Nodo
        {
            // El constructor, toma el elemento al que representa el nodo.
            Nodo(const T& v);
            // El elemento al que representa el nodo.
            T valor;
            // Puntero a la raíz del subárbol izquierdo.
            Nodo* izq;
            // Puntero a la raíz del subárbol derecho.
            Nodo* der;

        };

        bool perteneceDesde(Nodo *n, const T& clave) const;
        void insertarDesde(Nodo *n, const T& clave);
        void removerDesde(Nodo *n, const T& clave, Nodo* padre);
        const T& succAux(Nodo *n, const T& clave);
        const  T& izquierdoActual(const T& clave);
        const T& minimoDesde(Nodo *n) const;
        const T& maximoDesde(Nodo *n) const;
        void destruir(Nodo *n);
        Nodo* Padre(const T& clave);

        Nodo* _raiz;
        int _cardinal;

};

template<class T>
std::ostream& operator<<(std::ostream& os, const Conjunto<T>& c) {
	 c.mostrar(os);
	 return os;
}

#include "Conjunto.hpp"

#endif // CONJUNTO_H_
