#ifndef LISTAPROCESOS_H
#define LISTAPROCESOS_H

// MODULO DE: Mauricio

#include <string>
#include "PCB.h"

// Lista enlazada simple de procesos. Es la unica duena de los PCB.
class ListaProcesos {
public:
    typedef void (*Visitante)(const PCB&, void*);

    ListaProcesos();
    ~ListaProcesos();

    bool insertar(const PCB& p);              // al final; false si PID repetido
    PCB* buscarPorPid(int pid);               // NULL si no existe
    PCB* buscarPorNombre(const std::string& nombre); // primer resultado
    bool eliminar(int pid);                   // cabeza, interior o ultimo
    void recorrer(Visitante v, void* ctx) const;
    void liberarTodo();
    int  tamanio() const;
    bool vacia() const;

private:
    // Nodo: un PCB completo y la direccion del siguiente nodo (NULL = fin).
    struct Nodo {
        PCB   dato;
        Nodo* siguiente;
    };
    Nodo* cabeza_;
    Nodo* cola_;   // ultimo nodo: inserta al final en O(1)
    int          cantidad_;
    ListaProcesos(const ListaProcesos&);            // sin copia
    ListaProcesos& operator=(const ListaProcesos&);
};

#endif
