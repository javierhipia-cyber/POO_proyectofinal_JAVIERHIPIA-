#ifndef LISTAGEN_H
#define LISTAGEN_H

#include <cstddef>
#include <type_traits>

// Lista enlazada generica. Si T es un puntero, la lista asume su propiedad
// y libera el objeto apuntado al destruir o vaciar la lista.
template <typename T>
struct NodoGen {
    T dato;
    NodoGen<T>* siguiente;

    explicit NodoGen(const T& valor) : dato(valor), siguiente(0) {}
};

template <typename T>
class ListaGen {
private:
    NodoGen<T>* head;
    std::size_t cantidad;

    static void liberarDato(T dato, std::true_type) { delete dato; }
    static void liberarDato(const T&, std::false_type) {}

public:
    ListaGen() : head(0), cantidad(0) {}
    ListaGen(const ListaGen&) = delete;
    ListaGen& operator=(const ListaGen&) = delete;

    ~ListaGen() { limpiar(); }

    void insertar(const T& nuevoDato) {
        NodoGen<T>* nuevo = new NodoGen<T>(nuevoDato);
        nuevo->siguiente = head;
        head = nuevo;
        ++cantidad;
    }

    void recorrer(void (*accion)(T)) const {
        NodoGen<T>* actual = head;
        while (actual != 0) {
            accion(actual->dato);
            actual = actual->siguiente;
        }
    }

    // Disponible para listas cuyos elementos sean punteros a objetos con getId().
    T buscarPorId(int idBuscado) const {
        NodoGen<T>* actual = head;
        while (actual != 0) {
            if (actual->dato != 0 && actual->dato->getId() == idBuscado)
                return actual->dato;
            actual = actual->siguiente;
        }
        return T();
    }

    void procesarTodo() const {
        NodoGen<T>* actual = head;
        while (actual != 0) {
            if (actual->dato != 0)
                actual->dato->procesarLectura();
            actual = actual->siguiente;
        }
    }

    void limpiar() {
        NodoGen<T>* actual = head;
        while (actual != 0) {
            NodoGen<T>* siguiente = actual->siguiente;
            liberarDato(actual->dato, std::is_pointer<T>());
            delete actual;
            actual = siguiente;
        }
        head = 0;
        cantidad = 0;
    }

    std::size_t tamanio() const { return cantidad; }
    bool vacia() const { return head == 0; }
};

#endif
