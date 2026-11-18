#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string>

class Sensor {
protected:
    int id;
    std::string ubicacion;
    double lectura;

public:
    Sensor(int _id, const std::string& _ubicacion, double _lectura)
        : id(_id), ubicacion(_ubicacion), lectura(_lectura) {}

    virtual ~Sensor();

    int getId() const;
    double getLectura() const;
    const std::string& getUbicacion() const;

    virtual void procesarLectura() = 0;

    friend std::ostream& operator<<(std::ostream& os, const Sensor& s);
};

#endif
