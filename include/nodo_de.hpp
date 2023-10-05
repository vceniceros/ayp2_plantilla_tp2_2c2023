#ifndef NODO_DE_HPP
#define NODO_DE_HPP

template<typename T>
class Nodo_de {
private:
    T dato{};
    Nodo_de<T>* anterior;
    Nodo_de<T>* siguiente;
public:
    // Constructor.
    Nodo_de(T dato);

    // Constructor.
    Nodo_de(T dato, Nodo_de<T>* anterior, Nodo_de<T>* siguiente);

    // Pre: -
    // Post: Devuelve un puntero al nodo anterior.
    Nodo_de<T>* obtener_anterior();

    // Pre: -
    // Post: Devuelve un puntero al nodo siguiente.
    Nodo_de<T>* obtener_siguiente();

    // Pre: -
    // Post: Cambia el puntero al nodo anterior.
    void cambiar_anterior(Nodo_de<T>* nuevo);

    // Pre: -
    // Post: Cambia el puntero al nodo siguiente.
    void cambiar_siguiente(Nodo_de<T>* nuevo);

    // Pre: -
    // Post: Devuelve el dato almacenado.
    T obtener_dato();

    // Destructor.
    ~Nodo_de();
};

#endif