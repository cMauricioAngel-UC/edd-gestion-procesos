#include <cstddef>
#include "ColaPrioridad.h"

ColaPrioridad::ColaPrioridad() : frente_(NULL), cantidad_(0) {}
ColaPrioridad::~ColaPrioridad() { liberarTodo(); }

void ColaPrioridad::encolar(int pid, int prioridad) {
    if (pid <= 0 || prioridad < 1 || prioridad > 10 || contiene(pid)) return;
    Nodo* n = new Nodo;
    n->pid = pid;
    n->prioridad = prioridad;
    n->siguiente = NULL;
    // Se avanza mientras el nodo siguiente tenga prioridad <= la nueva:
    // asi, en empates, el nuevo queda DESPUES (FIFO).
    if (frente_ == NULL || prioridad < frente_->prioridad) {
        n->siguiente = frente_;
        frente_ = n;
    } else {
        Nodo* a = frente_;
        while (a->siguiente != NULL && a->siguiente->prioridad <= prioridad)
            a = a->siguiente;
        n->siguiente = a->siguiente;
        a->siguiente = n;
    }
    cantidad_++;
}

bool ColaPrioridad::desencolar(int& pid, int& prioridad) {
    if (frente_ == NULL) return false;
    Nodo* n = frente_;
    pid = n->pid;
    prioridad = n->prioridad;
    frente_ = n->siguiente;
    delete n;
    cantidad_--;
    return true;
}

bool ColaPrioridad::eliminarPid(int pid) {
    Nodo* anterior = NULL;
    Nodo* actual = frente_;
    while (actual != NULL && actual->pid != pid) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == NULL) return false;
    if (anterior == NULL) frente_ = actual->siguiente;
    else anterior->siguiente = actual->siguiente;
    delete actual;
    cantidad_--;
    return true;
}

bool ColaPrioridad::contiene(int pid) const {
    const Nodo* a = frente_;
    while (a != NULL) {
        if (a->pid == pid) return true;
        a = a->siguiente;
    }
    return false;
}

void ColaPrioridad::recorrer(Visitante v, void* ctx) const {
    const Nodo* a = frente_;
    while (a != NULL) { v(a->pid, a->prioridad, ctx); a = a->siguiente; }
}

void ColaPrioridad::liberarTodo() {
    int p, q;
    while (desencolar(p, q)) {}
}

int  ColaPrioridad::tamanio() const { return cantidad_; }
bool ColaPrioridad::vacia() const { return frente_ == NULL; }
