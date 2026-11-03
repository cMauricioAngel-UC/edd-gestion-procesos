#include <cstddef>
#include "PilaMemoria.h"

PilaMemoria::PilaMemoria() : tope_(NULL), usadosKB_(0), cantidad_(0) {}
PilaMemoria::~PilaMemoria() { liberarTodo(); }

bool PilaMemoria::push(int pid, int kb) {
    if (pid <= 0 || kb <= 0 || kb > CAPACIDAD_KB - usadosKB_) return false;
    Nodo* n = new Nodo;
    n->pid = pid;
    n->kb = kb;
    n->siguiente = tope_;     // el nuevo nodo apunta al tope anterior
    tope_ = n;
    usadosKB_ += kb;
    cantidad_++;
    return true;
}

bool PilaMemoria::pop(int& pid, int& kb) {
    if (tope_ == NULL) return false;
    Nodo* n = tope_;
    pid = n->pid;
    kb = n->kb;
    tope_ = n->siguiente;
    usadosKB_ -= kb;
    cantidad_--;
    delete n;
    return true;
}

// Usa una pila auxiliar propia: los bloques de otros PID pasan a la
// auxiliar (invirtiendo el orden) y luego se devuelven (restaurandolo).
int PilaMemoria::liberarPorPid(int pid) {
    Nodo* aux = NULL;
    int liberados = 0;
    while (tope_ != NULL) {
        Nodo* n = tope_;
        tope_ = n->siguiente;
        if (n->pid == pid) {
            liberados += n->kb;
            usadosKB_ -= n->kb;
            cantidad_--;
            delete n;
        } else {
            n->siguiente = aux;   // mover a la auxiliar
            aux = n;
        }
    }
    while (aux != NULL) {         // devolver al orden original
        Nodo* n = aux;
        aux = n->siguiente;
        n->siguiente = tope_;
        tope_ = n;
    }
    return liberados;
}

int PilaMemoria::totalPorPid(int pid) const {
    int total = 0;
    const Nodo* a = tope_;
    while (a != NULL) {
        if (a->pid == pid) total += a->kb;
        a = a->siguiente;
    }
    return total;
}

int PilaMemoria::bloquesDePid(int pid) const {
    int cuenta = 0;
    const Nodo* a = tope_;
    while (a != NULL) {
        if (a->pid == pid) cuenta++;
        a = a->siguiente;
    }
    return cuenta;
}

// La recursion visita primero los nodos mas profundos (la base)
// y al volver visita el tope: orden base -> tope.
void PilaMemoria::recorrerRec(const Nodo* n, Visitante v, void* ctx) {
    if (n == NULL) return;
    recorrerRec(n->siguiente, v, ctx);
    v(n->pid, n->kb, ctx);
}

void PilaMemoria::recorrerDesdeBase(Visitante v, void* ctx) const {
    recorrerRec(tope_, v, ctx);
}

void PilaMemoria::liberarTodo() {
    int p, k;
    while (pop(p, k)) {}
}

int  PilaMemoria::usadosKB() const { return usadosKB_; }
int  PilaMemoria::libresKB() const { return CAPACIDAD_KB - usadosKB_; }
int  PilaMemoria::tamanio() const { return cantidad_; }
bool PilaMemoria::vacia() const { return tope_ == NULL; }
