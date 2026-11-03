#include <cstddef>
#include <limits>
#include "ListaProcesos.h"

ListaProcesos::ListaProcesos() : cabeza_(NULL), cola_(NULL), cantidad_(0) {}
ListaProcesos::~ListaProcesos() { liberarTodo(); }

bool ListaProcesos::insertar(const PCB& p) {
    if (!pidValido(p.pid) || p.nombre.empty() || !prioridadValida(p.prioridad) ||
        !estadoValido(p.estado) || p.tiempoEjecucion != p.tiempoEjecucion || p.tiempoEjecucion > std::numeric_limits<float>::max() || p.tiempoEjecucion < 0 || p.memoriaKB < 0)
        return false;                                // datos invalidos
    if (buscarPorPid(p.pid) != NULL) return false;   // PID duplicado
    Nodo* n = new Nodo;
    n->dato = p;
    n->siguiente = NULL;
    if (cabeza_ == NULL) { cabeza_ = n; cola_ = n; }  // lista vacia
    else { cola_->siguiente = n; cola_ = n; }         // enlazar al final
    cantidad_++;
    return true;
}

PCB* ListaProcesos::buscarPorPid(int pid) {
    Nodo* a = cabeza_;
    while (a != NULL) {               // recorre hasta hallar o llegar a NULL
        if (a->dato.pid == pid) return &a->dato;
        a = a->siguiente;
    }
    return NULL;
}

PCB* ListaProcesos::buscarPorNombre(const std::string& nombre) {
    Nodo* a = cabeza_;
    while (a != NULL) {
        if (a->dato.nombre == nombre) return &a->dato;
        a = a->siguiente;
    }
    return NULL;
}

bool ListaProcesos::eliminar(int pid) {
    Nodo* anterior = NULL;
    Nodo* actual = cabeza_;
    while (actual != NULL && actual->dato.pid != pid) {
        anterior = actual;            // guarda el nodo previo para reconectar
        actual = actual->siguiente;
    }
    if (actual == NULL) return false; // vacia o PID inexistente
    if (anterior == NULL) cabeza_ = actual->siguiente;      // era la cabeza
    else anterior->siguiente = actual->siguiente;           // interior/ultimo
    if (actual == cola_) cola_ = anterior;                  // era el ultimo
    delete actual;
    cantidad_--;
    return true;
}

void ListaProcesos::recorrer(Visitante v, void* ctx) const {
    const Nodo* a = cabeza_;
    while (a != NULL) { v(a->dato, ctx); a = a->siguiente; }
}

void ListaProcesos::liberarTodo() {
    while (cabeza_ != NULL) {
        Nodo* sig = cabeza_->siguiente;
        delete cabeza_;
        cabeza_ = sig;
    }
    cola_ = NULL;
    cantidad_ = 0;
}

int  ListaProcesos::tamanio() const { return cantidad_; }
bool ListaProcesos::vacia() const { return cabeza_ == NULL; }
