#ifndef LISTA_DE_HPP
#define LISTA_DE_HPP

#include <exception>
#include <cstdlib>
#include "Nodo_de.hpp"
const size_t MITAD_LISTA = 2;
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
    Nodo_de<T>* primer_nodo;
    Nodo_de<T>* ultimo_nodo;
    Nodo_de<T>* cursor;
    int indice_cursor;
    size_t cantidad_datos;

    Nodo_de<T>*  obtener_nodo(size_t indice) {
        if (indice >= cantidad_datos || cantidad_datos == 0) {
            throw Lista_exception();
        }
        size_t mitad_lista = cantidad_datos / MITAD_LISTA;
        if (indice_cursor == -1 || indice < mitad_lista) {
            cursor = primer_nodo;
            indice_cursor = 0;
        } else {
            cursor = ultimo_nodo;
            indice_cursor = cantidad_datos - 1;
        }
        while (indice_cursor != indice) {
            if (indice_cursor < indice) {
                cursor = cursor->obtener_siguiente();
                indice_cursor++;
            } else {
                cursor = cursor->obtener_anterior();
                indice_cursor--;
            }
        }
        return cursor;
    }

public:
    // Constructor.
    Lista_de(){
        primer_nodo = nullptr;
        ultimo_nodo = nullptr;
        cursor = nullptr;
        indice_cursor = -1;
        cantidad_datos = 0;
    };

    // Pre: La lista no puede estar vacía.
    // Post: Devuelve el primer dato en la lista.
    T primero(){
        if(cantidad_datos != 0){
            return primer_nodo->obtener_dato();
        }else{
            throw Lista_exception();
        }
    };

    // Pre: La lista no puede estar vacía.
    // Post: Devuelve el último dato en la lista.
    T ultimo(){
        if(cantidad_datos != 0){
            return ultimo_nodo->obtener_dato();
        }else{
            throw Lista_exception();
        }
    };

    // Pre: El índice debe ser menor que la cantidad de datos.
    // Post: Devuelve el dato en la posición deseada.
    T elemento(size_t indice){
        if(indice < cantidad_datos){
            return obtener_nodo(indice)->obtener_dato();
        }else{
            throw Lista_exception();
        }
    };

    // Pre: -
    // Post: Devuelve true si se puede avanzar (esto es, que el cursor no sea nullptr).
    bool puede_avanzar(){
        return (cursor != 0);
    };

    // Pre: Se debe poder avanzar.
    // Post: Devuelve el dato del cursor actual y luego lo mueve una posición en la dirección deseada.
    T avanzar(bool siguiente){
        if(puede_avanzar()){
            T d = cursor->obtener_dato();
            cursor = cursor->obtener_siguiente();
            return d;
        }else if(vacio()){
            throw Lista_exception();
        }else{
            throw Lista_exception();
        }
    };

    // Pre: -
    // Post: Reinicia el cursor al principio o al final, según lo indicado.
    // Si la lista está vacía, se reinicia el cursor al estado inicial
    // (esto es, cursor = nullptr e indice_cursor = -1).
    void reiniciar_cursor(bool principio){
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
    };

    // Pre: -
    // Post: Devuelve la cantidad de datos de la lista.
    size_t tamanio(){
        return cantidad_datos;
    };

    // Pre: -
    // Post: Devuelve true si la lista esta vacía (es decir, si no hay datos).
    bool vacio(){
        return cantidad_datos == 0;
    };


    // Pre: -
    // Post: Agrega el dato al final de la lista.
    void alta(T dato) {
        Nodo_de<T>* nuevo = new Nodo_de<T>(dato);
        if (cantidad_datos == 0) {
            primer_nodo = nuevo;
            ultimo_nodo = nuevo;
        } else {
            nuevo->cambiar_anterior(ultimo_nodo);
            ultimo_nodo->cambiar_siguiente(nuevo);
            ultimo_nodo = nuevo;
        }
        cantidad_datos++;
    }

    // Pre: La lista no puede estar vacía.
    // Post: Elimina el último dato.
    // NOTA: Considerar que se puede dar de baja el nodo cursor.
    T baja() {
        T dato;
        if(cantidad_datos == 0 ){
            throw Lista_exception();
        }else if(cantidad_datos == 1){
            Nodo_de<T>* aux = ultimo_nodo;
            dato = aux->obtener_dato();
           primer_nodo = nullptr;
           ultimo_nodo = nullptr;
           cursor = nullptr;
           indice_cursor = -1;
           cantidad_datos = 0;
       }else{
           if(indice_cursor == cantidad_datos){
               reiniciar_cursor(true);
           }
           Nodo_de<T>* aux = ultimo_nodo;
           ultimo_nodo = ultimo_nodo->obtener_anterior();
           dato = aux->obtener_dato();
           cantidad_datos--;
       }

        return dato;
    }


    // Pre: El índice debe ser menor o igual que la cantidad de datos.
    // Post: Agrega el dato antes del dato en la posición indicada.
    // Si el índice es igual a la cantidad de datos, simplemente agrega al final.
    void alta(T dato, size_t indice) {
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
    };

    // Pre: El índice debe ser menor que la cantidad de datos.
    // Post: Elimina el dato en la posición indicada.
    // Si el índice es igual a la cantidad de datos - 1, simplemente
    // elimina el último dato.
    // NOTA: Considerar que se puede dar de baja el nodo cursor.
    T baja(size_t indice) {
        if (cantidad_datos == 0) {
            throw Lista_exception();
        } else if(indice > cantidad_datos) {
            throw Lista_exception();
        }else if (indice == cantidad_datos) {
                return baja();

        } else if (indice < cantidad_datos) {
            Nodo_de<T>* aux_baja = primer_nodo;
            T aux = aux_baja->obtener_dato();
            if (indice_cursor == static_cast<int>(cantidad_datos)) {
                if (indice == 0) {
                    reiniciar_cursor(true);
                } else {
                    reiniciar_cursor(false);
                }
            }
            Nodo_de<T>* anterior = obtener_nodo(indice - 1);
            aux_baja = anterior->obtener_siguiente();
            anterior->cambiar_siguiente(aux_baja->obtener_siguiente());
            delete aux_baja;
            cantidad_datos--;
            return aux;
        }
    };


    // El constructor de copia está deshabilitado.
    Lista_de(const Lista_de& l) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const Lista_de& l) = delete;

    // Destructor.
    ~Lista_de(){
        while (! vacio())
                baja(1);
    };
};

#endif