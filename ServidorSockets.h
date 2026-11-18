#ifndef SERVIDOR_SOCKETS_H
#define SERVIDOR_SOCKETS_H

#include <string>
#include <cstdint>

#ifdef _WIN32
    #include <winsock2.h>
    typedef SOCKET SocketHandle;
#else
    typedef int SocketHandle;
#endif

// La trama binaria solicitada en la guia.
struct MuestraSensor {
    int idSensor;
    double valor;
    char tipo[12];
};

class ServidorSMTI {
private:
    SocketHandle servidor;
    bool iniciado;

    void cerrarSocket(SocketHandle socket);

public:
    ServidorSMTI();
    ~ServidorSMTI();

    void iniciar(unsigned short puerto = 8080);
    bool recibirUnaMuestra(MuestraSensor& muestra);
    void detener();

    ServidorSMTI(const ServidorSMTI&) = delete;
    ServidorSMTI& operator=(const ServidorSMTI&) = delete;
};

#endif
