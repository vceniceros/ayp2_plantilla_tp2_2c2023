#ifndef COLA_HPP
#define COLA_HPP
#include <queue>
#include <exception>
#include "../include/nodo.hpp"



class Cola_exception : public std::exception {
    // Excepcion especifica y exclusivamente para errores dentro de la cola.
    // Usar de la forma "throw Cola_exception();" cuando una precondicion no se cumpla.

    // Ejemplo:
    //     if (condicion_de_error()){
    //         throw cola_exception();
    //     }
};

template<typename T>
class Cola {
private:
    Nodo<T>* primer_nodo;
    Nodo<T>* ultimo_nodo;
    size_t cantidad_datos;


public:
    // Constructor.
    Cola(){
        cantidad_datos = 0;
        primer_nodo = nullptr;
        ultimo_nodo = nullptr;
    };

    // Pre: -
    // Post: Agrega el dato al final de la cola.
        void alta(T dato){
            Nodo<T>* nuevo = new Nodo(dato);
            if(cantidad_datos == 0){
                primer_nodo = nuevo;
                ultimo_nodo = nuevo;
            }else{
                ultimo_nodo->cambiar_siguiente(nuevo);
                ultimo_nodo = nuevo;
            }
             cantidad_datos++;

        };

    // Pre: La cola no puede estar vacía.
    // Post: Elimina el primer dato.
    T baja(){
        if(cantidad_datos > 0){
            Nodo<T>* aux = primer_nodo;
            primer_nodo = primer_nodo->obtener_siguiente();
            T dato = aux->obtener_dato();
            delete aux;
            cantidad_datos--;
            return dato;
        }else{
            throw Cola_exception();
        }
    };

    // Pre: La cola no puede estar vacía.
    // Post: Devuelve el primer dato en la cola.
    T primero(){
        if(cantidad_datos == 0){
            throw Cola_exception();
        }else{
            return primer_nodo->obtener_dato();

        }
    };

    // Pre: La cola no puede estar vacía.
    // Post: Devuelve el último dato en la cola.
    T ultimo(){
        if(cantidad_datos == 0){
            throw Cola_exception();
        }else{
            return  ultimo_nodo->obtener_dato();
        }
    };

    // Pre: -
    // Post: Devuelve la cantidad de datos de la cola.
    size_t tamanio(){
        return cantidad_datos;
    };

    // Pre: -
    // Post: Devuelve true si la cola esta vacía (es decir, si no hay datos).
    bool vacio(){
        return(cantidad_datos == 0);
    };

    // El constructor de copia está deshabilitado.
    Cola(const Cola& l) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const Cola& l) = delete;

    // Destructor.
    ~Cola(){
        while(! vacio()){
            baja();
        }
    };
};

#endif