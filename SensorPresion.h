#ifndef SENSOR_PRESION_H
#define SENSOR_PRESION_H

#include "Sensor.h"

class SensorPresion : public Sensor {
private:
    double presionMaxima;

public:
    SensorPresion(int id, const std::string& ubicacion,
                  double lectura, double maxima = 10.0);
    void procesarLectura() override;
};

#endif
