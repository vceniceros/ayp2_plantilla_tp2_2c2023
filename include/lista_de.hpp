#ifndef LISTA_DE_HPP
#define LISTA_DE_HPP

#include <exception>
#include <cstdlib>
#include "nodo_de.hpp"
const size_t DOS = 2;
class Lista_exception : public std::exception {
    // Excepcion especifica y exclusivamente para errores dentro de la lista.
    // Usar de la forma "throw lista_exception();" cuando una precondicion no se cumpla.

    // Ejemplo:
    //     if (condicion_de_error()){
    //         throw Lista_exception();
    //     }
};

template<typename T>
class Lista_de {
private:
    Nodo_de<T> *primer_nodo;
    Nodo_de<T> *ultimo_nodo;
    Nodo_de<T> *cursor;
    int indice_cursor;
    size_t cantidad_datos;

    // Pre: El índice debe ser menor que la cantidad de datos.
    // Post: Devuelve un puntero
    // al nodo asociado al índice deseado.
    Nodo_de<T> *obtener_nodo(size_t indice);

public:
    // Constructor.
    Lista_de();

    // Pre: La lista no puede estar vacía.
    // Post: Devuelve el primer dato en la lista.
    T primero();

    // Pre: La lista no puede estar vacía.
    // Post: Devuelve el último dato en la lista.
    T ultimo();

    // Pre: El índice debe ser menor que la cantidad de datos.
    // Post: Devuelve el dato en la posición deseada.
    T elemento(size_t indice);

    // Pre: -
    // Post: Devuelve true si se puede avanzar (esto es, que el cursor no sea nullptr).
    bool puede_avanzar();

    // Pre: Se debe poder avanzar.
    // Post: Devuelve el dato del cursor actual y luego lo mueve una posición en la dirección deseada.
    T avanzar(bool siguiente);

    // Pre: -
    // Post: Reinicia el cursor al principio o al final, según lo indicado.
    // Si la lista está vacía, se reinicia el cursor al estado inicial
    // (esto es, cursor = nullptr e indice_cursor = -1).
    void reiniciar_cursor(bool principio);

    // Pre: -
    // Post: Devuelve la cantidad de datos de la lista.
    size_t tamanio();

    // Pre: -
    // Post: Devuelve true si la lista esta vacía (es decir, si no hay datos).
    bool vacio();


    // Pre: -
    // Post: Agrega el dato al final de la lista.
    void alta(T dato);


    // Pre: El índice debe ser menor o igual que la cantidad de datos.
    // Post: Agrega el dato antes del dato en la posición indicada.
    // Si el índice es igual a la cantidad de datos, simplemente agrega al final.
    void alta(T dato, size_t indice);

    // Pre: La lista no puede estar vacía.
    // Post: Elimina el último dato.
    // NOTA: Considerar que se puede dar de baja el nodo cursor.
    T baja();

    // Pre: El índice debe ser menor que la cantidad de datos.
    // Post: Elimina el dato en la posición indicada.
    // Si el índice es igual a la cantidad de datos - 1, simplemente
    // elimina el último dato.
    // NOTA: Considerar que se puede dar de baja el nodo cursor.
    T baja(size_t indice);


    // El constructor de copia está deshabilitado.
    Lista_de(const Lista_de &l) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const Lista_de &l) = delete;

    // Destructor.
    ~Lista_de();
};
template<typename T>
T Lista_de<T>::baja(size_t indice) {
    T dato;
    if (vacio() || indice >= cantidad_datos) {
        throw Lista_exception();
    }else{
        if (indice == cantidad_datos-1) {
            dato = baja();
        }else{
            Nodo_de<T>* aux_baja = obtener_nodo(indice);
            Nodo_de<T>* siguiente = aux_baja->obtener_siguiente();
            Nodo_de<T>* anterior = aux_baja->obtener_anterior();
            siguiente->cambiar_anterior(anterior);
            if (indice == 0) {
                primer_nodo = siguiente;
            }else{
                anterior->cambiar_siguiente(siguiente);
            }
            dato = aux_baja->obtener_dato();
            if(cursor == aux_baja){
                reiniciar_cursor(true);
            }
            delete aux_baja;
            cantidad_datos--;
        }

    }
    return dato;
}

template<typename T>
T Lista_de<T>::baja() {
    T dato;
    if(cantidad_datos == 0 ){
        throw Lista_exception();
    }else{
        Nodo_de<T>* aux_baja = ultimo_nodo;
        ultimo_nodo = ultimo_nodo->obtener_anterior();
        if(cantidad_datos == 1){
            primer_nodo = nullptr;
        }
        if(indice_cursor == cantidad_datos){
            reiniciar_cursor(true);
        }

        dato = aux_baja->obtener_dato();
        cantidad_datos--;
        return dato;
    }
}

template<typename T>
void Lista_de<T>::alta(T dato, size_t indice) {
    if (indice > cantidad_datos) {
        throw Lista_exception();
    } else if (indice == cantidad_datos) {
        alta(dato);
    } else {
        Nodo_de<T> *nodo_alta = new Nodo_de<T>(dato);
        if (indice == 0) {
            nodo_alta->cambiar_siguiente(primer_nodo);
            primer_nodo->cambiar_anterior(nodo_alta);
            primer_nodo = nodo_alta;
        } else {
            Nodo_de<T> *anterior = obtener_nodo(indice)->obtener_anterior();
            Nodo_de<T> *siguiente = anterior->obtener_siguiente();

            nodo_alta->cambiar_anterior(anterior);
            nodo_alta->cambiar_siguiente(siguiente);

            anterior->cambiar_siguiente(nodo_alta);
            siguiente->cambiar_anterior(nodo_alta);
        }
        cantidad_datos++;
    }
}

template<typename T>
void Lista_de<T>::alta(T dato) {
    Nodo_de<T>* nuevo = new Nodo_de<T>(dato);
    if (cantidad_datos == 0) {
        primer_nodo = nuevo;
    } else {
        nuevo->cambiar_anterior(ultimo_nodo);
        ultimo_nodo->cambiar_siguiente(nuevo);
    }
    ultimo_nodo = nuevo;
    cantidad_datos++;
}

template<typename T>
bool Lista_de<T>::vacio() {
    return cantidad_datos == 0;
}

template<typename T>
size_t Lista_de<T>::tamanio() {
    return cantidad_datos;
}

template<typename T>
void Lista_de<T>::reiniciar_cursor(bool principio) {
    if(vacio()){
        cursor = nullptr;
        indice_cursor = -1;
    }else if(principio){
        cursor = primer_nodo;
        indice_cursor = 1;
    }else{
        cursor = ultimo_nodo;
        indice_cursor = static_cast<int>(cantidad_datos) ;
    }
}

template<typename T>
T Lista_de<T>::avanzar(bool siguiente) {
    if(!puede_avanzar()){
        throw Lista_exception();
    }
    T dato;
    if(siguiente){
        dato = cursor->obtener_dato();
        cursor = cursor->obtener_siguiente();
    }else{
        dato = cursor->obtener_dato();
        cursor = cursor->obtener_anterior();
    }
    return dato;
}

template<typename T>
bool Lista_de<T>::puede_avanzar() {
    return (cursor != 0);
}

template<typename T>
T Lista_de<T>::elemento(size_t indice) {
    if(indice < cantidad_datos){
        return obtener_nodo(indice)->obtener_dato();
    }else{
        throw Lista_exception();
    }
}

template<typename T>
T Lista_de<T>::ultimo() {
    if(cantidad_datos != 0){
        return ultimo_nodo->obtener_dato();
    }else{
        throw Lista_exception();
    }
}

template<typename T>
Lista_de<T>::Lista_de() {
    primer_nodo = nullptr;
    ultimo_nodo = nullptr;
    cursor = nullptr;
    indice_cursor = -1;
    cantidad_datos = 0;
}

template<typename T>
Nodo_de<T> *Lista_de<T>::obtener_nodo(size_t indice) {
    if (indice >= cantidad_datos) {
        throw Lista_exception();
    }else if(cantidad_datos == 0){
        throw Lista_exception();
    }else{
        Nodo_de<T>* aux;
        size_t indice_aux;
        size_t mitad_lista = cantidad_datos / DOS;
        if (indice <= mitad_lista) {
            aux = primer_nodo;
            indice_aux = 0;
        } else {
            aux = ultimo_nodo;
            indice_aux = cantidad_datos - 1;
        }
        while (indice_aux != indice) {
            if (indice_aux <= indice) {
                aux = aux->obtener_siguiente();
                indice_aux++;
            } else {
                aux = aux->obtener_anterior();
                indice_aux--;
            }
        }
        return aux;
    }
}

template<typename T>
T Lista_de<T>::primero() {
    if(cantidad_datos != 0){
        return primer_nodo->obtener_dato();
    }else{
        throw Lista_exception();
    }
}

template<typename T>
Lista_de<T>::~Lista_de() {
    while (!vacio()) {
        baja();
    }
}

#endif