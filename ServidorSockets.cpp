#include "ServidorSockets.h"
#include <stdexcept>
#include <cstring>
#include <iostream>

#ifdef _WIN32
    #include <ws2tcpip.h>
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <cerrno>
#endif

ServidorSMTI::ServidorSMTI() : servidor(
#ifdef _WIN32
    INVALID_SOCKET
#else
    -1
#endif
), iniciado(false) {}

ServidorSMTI::~ServidorSMTI() { detener(); }

void ServidorSMTI::cerrarSocket(SocketHandle socket) {
#ifdef _WIN32
    if (socket != INVALID_SOCKET) closesocket(socket);
#else
    if (socket >= 0) close(socket);
#endif
}

void ServidorSMTI::iniciar(unsigned short puerto) {
#ifdef _WIN32
    WSADATA datos;
    int wsa = WSAStartup(MAKEWORD(2, 2), &datos);
    if (wsa != 0)
        throw std::runtime_error("No se pudo iniciar Winsock.");
    servidor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (servidor == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("No se pudo crear el socket TCP.");
    }
    BOOL reutilizar = TRUE;
    setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR,
               reinterpret_cast<const char*>(&reutilizar), sizeof(reutilizar));
#else
    servidor = socket(AF_INET, SOCK_STREAM, 0);
    if (servidor < 0)
        throw std::runtime_error("No se pudo crear el socket TCP.");
    int reutilizar = 1;
    setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &reutilizar, sizeof(reutilizar));
#endif

    sockaddr_in direccion;
    std::memset(&direccion, 0, sizeof(direccion));
    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = htonl(INADDR_ANY);
    direccion.sin_port = htons(puerto);

    if (bind(servidor, reinterpret_cast<sockaddr*>(&direccion),
             sizeof(direccion)) < 0) {
        detener();
        throw std::runtime_error("Fallo bind: el puerto puede estar ocupado.");
    }

    if (listen(servidor, 5) < 0) {
        detener();
        throw std::runtime_error("Fallo listen al poner el servidor en escucha.");
    }

    iniciado = true;
    std::cout << "[SERVIDOR] Escuchando en el puerto " << puerto << std::endl;
}

bool ServidorSMTI::recibirUnaMuestra(MuestraSensor& muestra) {
    if (!iniciado)
        throw std::runtime_error("El servidor no ha sido iniciado.");

    std::cout << "[SERVIDOR] Esperando conexion de un sensor cliente..." << std::endl;
    sockaddr_in cliente;
#ifdef _WIN32
    int longitud = sizeof(cliente);
    SocketHandle clienteSocket = accept(servidor, reinterpret_cast<sockaddr*>(&cliente), &longitud);
    if (clienteSocket == INVALID_SOCKET)
        throw std::runtime_error("Fallo accept al recibir un cliente.");
#else
    socklen_t longitud = sizeof(cliente);
    SocketHandle clienteSocket = accept(servidor, reinterpret_cast<sockaddr*>(&cliente), &longitud);
    if (clienteSocket < 0)
        throw std::runtime_error("Fallo accept al recibir un cliente.");
#endif

    char* destino = reinterpret_cast<char*>(&muestra);
    std::size_t recibidos = 0;
    while (recibidos < sizeof(MuestraSensor)) {
#ifdef _WIN32
        int n = recv(clienteSocket, destino + recibidos,
                     static_cast<int>(sizeof(MuestraSensor) - recibidos), 0);
#else
        ssize_t n = recv(clienteSocket, destino + recibidos,
                         sizeof(MuestraSensor) - recibidos, 0);
#endif
        if (n <= 0) {
            cerrarSocket(clienteSocket);
            throw std::runtime_error("La conexion se cerro o fallo recv.");
        }
        recibidos += static_cast<std::size_t>(n);
    }

    cerrarSocket(clienteSocket);
    muestra.tipo[sizeof(muestra.tipo) - 1] = '\0';
    return true;
}

void ServidorSMTI::detener() {
    if (servidor !=
#ifdef _WIN32
        INVALID_SOCKET
#else
        -1
#endif
    ) {
        cerrarSocket(servidor);
#ifdef _WIN32
        servidor = INVALID_SOCKET;
        WSACleanup();
#else
        servidor = -1;
#endif
    }
    iniciado = false;
}
