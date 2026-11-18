# Proyecto SMTI - Servidor TCP de Telemetria

Proyecto C++11 para la Evaluacion 3 de Programacion Orientada a Objetos.

## Estructura
- `include/`: archivos de cabecera `.h`.
- `src/`: implementaciones `.cpp` y `main.cpp`.
- `.gitignore`: excluye ejecutables y archivos temporales.

## Requisitos implementados
- Clase abstracta `Sensor`, destructor virtual y `procesarLectura()` puro.
- Clases derivadas `SensorTemperatura`, `SensorPresion` y `SensorCaudal` con `override`.
- Sobrecarga amiga de `operator<<`.
- `ListaGen<T>` con nodos dinamicos, insercion, recorrido, busqueda por ID y limpieza.
- La lista es propietaria de los punteros que recibe: al destruirse elimina sensores y nodos.
- Servidor TCP en puerto 8080 con `socket`, `bind`, `listen`, `accept` y `recv`.
- Excepciones `std::runtime_error` capturadas en `main`.

## Compilacion

### Linux
Desde la carpeta del proyecto:
```bash
g++ -std=c++11 -Wall -Wextra -Iinclude src/*.cpp -o SMTI
./SMTI
./SMTI --server
```

### Windows con MinGW
```bash
g++ -std=c++11 -Wall -Wextra -Iinclude src/*.cpp -o SMTI.exe -lws2_32
SMTI.exe
SMTI.exe --server
```

La ejecucion sin argumentos muestra una demostracion local y termina. Con `--server`, el programa queda escuchando en el puerto 8080 y espera una conexion que envie una trama binaria `MuestraSensor` completa.

## Formato de trama TCP
La estructura enviada debe coincidir en ambos extremos:
```cpp
struct MuestraSensor {
    int idSensor;
    double valor;
    char tipo[12];
};
```
Valores admitidos para `tipo`: `TEMP`, `PRESION` o `CAUDAL`. TCP es un flujo de bytes; por eso `recv` se repite hasta completar el tamaño de la estructura.

## Abrir en ZinjaI
1. Descomprima esta carpeta.
2. En ZinjaI cree un proyecto C++ nuevo dentro de `Proyecto_SMTI`.
3. Agregue todos los `.cpp` de `src/` y configure `include/` como directorio de cabeceras si el IDE lo solicita.
4. Seleccione C++11 en las opciones del compilador.
5. En Windows, agregue `-lws2_32` a las opciones del enlazador.
6. Guarde el proyecto desde ZinjaI dentro de esta carpeta. El archivo de proyecto generado por su version del IDE debe quedar junto a `README.md`.

## Publicar en GitHub
Siga `GuaGitHub.pdf`: cree un repositorio publico, copie su URL HTTPS y, desde una consola abierta en esta carpeta, ejecute:
```bash
git init
git add .
git commit -m "Proyecto SMTI C++11"
git branch -M main
git remote add origin URL_HTTPS_DE_TU_REPOSITORIO
git push -u origin main
```
Reemplace `URL_HTTPS_DE_TU_REPOSITORIO` por la URL real, sin signos `< >`.
Luego, en GitHub: Settings -> Collaborators -> Add people -> busque `PABTORO` y envie la invitacion.

**Importante:** no se puede fabricar desde aqui el enlace de tu repositorio: GitHub lo genera cuando lo creas en tu cuenta. La carpeta y el codigo si quedan preparados para subir.
