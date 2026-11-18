#include "Sensor.h"

Sensor::~Sensor() {
    std::cout << "[DESTRUCTOR] Sensor ID " << id
              << " liberado del Heap." << std::endl;
}

int Sensor::getId() const { return id; }
double Sensor::getLectura() const { return lectura; }
const std::string& Sensor::getUbicacion() const { return ubicacion; }

std::ostream& operator<<(std::ostream& os, const Sensor& s) {
    os << "Sensor ID: " << s.id
       << " | Ubicacion: " << s.ubicacion
       << " | Valor: " << s.lectura;
    return os;
}
