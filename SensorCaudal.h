#ifndef SENSOR_CAUDAL_H
#define SENSOR_CAUDAL_H

#include "Sensor.h"

class SensorCaudal : public Sensor {
private:
    double caudalMinimo;

public:
    SensorCaudal(int id, const std::string& ubicacion,
                 double lectura, double minimo = 2.0);
    void procesarLectura() override;
};

#endif
