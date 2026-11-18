#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H

#include "Sensor.h"

class SensorTemperatura : public Sensor {
private:
    double umbralMaximo;

public:
    SensorTemperatura(int id, const std::string& ubicacion,
                      double lectura, double umbral = 80.0);
    void procesarLectura() override;
};

#endif
