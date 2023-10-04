#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <string>

const std::string ACCION_GUARDADO = "GUARDADO";
const std::string ACCION_APERTURA_MAPA = "APERTURA_MAPA";

class evento {
private:
    std::string accion_ejecutada;
    // Otros atributos asociados a la descripcion del evento.

public:
    // Constructor.
    explicit evento(std::string accion_ejecutada);

    // Pre:
    // Post: Devuelve true si la accion coincide con la ejecutada.
    bool operator==(const std::string& accion);

    // Otros metodos asociados a la clase.
};

#endif