#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "SensorCaudal.h"
#include "ListaGen.h"
#include "ServidorSockets.h"

static void agregarMuestra(ListaGen<Sensor*>& lista, const MuestraSensor& m) {
    const std::string ubicacion = std::string("Nodo-") + std::to_string(m.idSensor);
    if (std::strcmp(m.tipo, "TEMP") == 0) {
        lista.insertar(new SensorTemperatura(m.idSensor, ubicacion, m.valor));
    } else if (std::strcmp(m.tipo, "PRESION") == 0) {
        lista.insertar(new SensorPresion(m.idSensor, ubicacion, m.valor));
    } else if (std::strcmp(m.tipo, "CAUDAL") == 0) {
        lista.insertar(new SensorCaudal(m.idSensor, ubicacion, m.valor));
    } else {
        throw std::runtime_error("Tipo de sensor desconocido en la trama.");
    }
}

int main(int argc, char* argv[]) {
    std::cout << "==============================================\n";
    std::cout << " SMTI - SERVIDOR DE TELEMETRIA INDUSTRIAL\n";
    std::cout << "==============================================\n";

    ListaGen<Sensor*> listaPlanta;

    try {
        // Ejecucion normal: demostracion local para comprobar polimorfismo y Heap.
        if (argc < 2 || std::string(argv[1]) != "--server") {
            listaPlanta.insertar(new SensorTemperatura(101, "Caldera-01", 92.5));
            listaPlanta.insertar(new SensorPresion(102, "Tuberia-02", 7.4));
            listaPlanta.insertar(new SensorCaudal(103, "Conducto-03", 1.2));

            std::cout << "\n--- PROCESAMIENTO POLIMORFICO ---\n";
            listaPlanta.procesarTodo();
            std::cout << "\nSensores almacenados: " << listaPlanta.tamanio() << std::endl;
            std::cout << "Al terminar, la lista libera nodos y sensores del Heap.\n";
            std::cout << "\nPara iniciar el servidor TCP real ejecute: programa --server\n";
            return 0;
        }

        // Modo de red: escucha en 8080 y recibe una trama binaria completa.
        ServidorSMTI servidor;
        servidor.iniciar(8080);

        MuestraSensor muestra;
        if (servidor.recibirUnaMuestra(muestra)) {
            agregarMuestra(listaPlanta, muestra);
            std::cout << "\n[MUESTRA RECIBIDA] ID: " << muestra.idSensor
                      << " | Tipo: " << muestra.tipo
                      << " | Valor: " << muestra.valor << std::endl;
            listaPlanta.procesarTodo();
        }
        servidor.detener();

    } catch (const std::exception& e) {
        std::cerr << "[EXCEPCION SMTI] " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
