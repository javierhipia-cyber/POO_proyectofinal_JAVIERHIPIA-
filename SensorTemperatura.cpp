#include "SensorTemperatura.h"
#include <iostream>

SensorTemperatura::SensorTemperatura(int id, const std::string& ubicacion,
                                     double lectura, double umbral)
    : Sensor(id, ubicacion, lectura), umbralMaximo(umbral) {}

void SensorTemperatura::procesarLectura() {
    std::cout << "[TEMPERATURA] " << *this;
    if (lectura > umbralMaximo)
        std::cout << " --> ALERTA: SOBRETEMPERATURA CRITICA";
    else
        std::cout << " --> Estado normal";
    std::cout << std::endl;
}
