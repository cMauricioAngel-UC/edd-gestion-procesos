#ifndef ED_PCB_H
#define ED_PCB_H

#include <string>

// Contrato comun del proyecto. La lista enlazada sera duena de cada PCB.
struct PCB {
    int pid;
    std::string nombre;
    int prioridad; // 1 = maxima, 10 = minima
    std::string estado; // Listo, Ejecucion, Bloqueado, Terminado
    float tiempoEjecucion;
    int memoriaKB;

    PCB() : pid(0), prioridad(1), estado("Listo"),
            tiempoEjecucion(0.0f), memoriaKB(0) {}
};

inline bool prioridadValida(int prioridad) {
    return prioridad >= 1 && prioridad <= 10;
}

inline bool estadoValido(const std::string& estado) {
    return estado == "Listo" || estado == "Ejecucion" ||
           estado == "Bloqueado" || estado == "Terminado";
}

#endif
