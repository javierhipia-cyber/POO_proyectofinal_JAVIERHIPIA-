#include "SensorPresion.h"
#include <iostream>

SensorPresion::SensorPresion(int id, const std::string& ubicacion,
                             double lectura, double maxima)
    : Sensor(id, ubicacion, lectura), presionMaxima(maxima) {}

void SensorPresion::procesarLectura() {
    std::cout << "[PRESION] " << *this;
    if (lectura > presionMaxima)
        std::cout << " --> ALERTA: PRESION ALTA";
    else
        std::cout << " --> Estado normal";
    std::cout << std::endl;
}
