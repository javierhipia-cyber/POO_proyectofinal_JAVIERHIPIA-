#include "SensorCaudal.h"
#include <iostream>

SensorCaudal::SensorCaudal(int id, const std::string& ubicacion,
                           double lectura, double minimo)
    : Sensor(id, ubicacion, lectura), caudalMinimo(minimo) {}

void SensorCaudal::procesarLectura() {
    std::cout << "[CAUDAL] " << *this;
    if (lectura < caudalMinimo)
        std::cout << " --> ALERTA: CAUDAL BAJO";
    else
        std::cout << " --> Estado normal";
    std::cout << std::endl;
}
