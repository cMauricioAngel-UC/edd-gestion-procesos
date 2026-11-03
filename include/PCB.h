#ifndef PCB_H
#define PCB_H

// MODULO DE: Mauricio e Isai (contrato comun)

#include <string>

// Valores validos del campo estado (conjunto fijo del simulador).
const char* const ESTADO_LISTO     = "Listo";
const char* const ESTADO_EJECUCION = "Ejecucion";
const char* const ESTADO_BLOQUEADO = "Bloqueado";
const char* const ESTADO_TERMINADO = "Terminado";

// PCB = Process Control Block (Bloque de Control de Proceso).
// PID = Process IDentifier: entero positivo y unico entre los procesos
// registrados; conecta el PCB con su turno en la cola y sus bloques en la pila.
struct PCB {
    int         pid;             // identificador unico (> 0)
    std::string nombre;          // nombre para reconocerlo y buscarlo
    int         prioridad;       // 1 (mas alta) .. 10 (mas baja)
    std::string estado;          // Listo, Ejecucion, Bloqueado o Terminado
    float       tiempoEjecucion; // tiempo estimado ingresado (dato simulado)
    int         memoriaKB;       // debe coincidir con la suma de sus bloques

    PCB() : pid(0), nombre(""), prioridad(1), estado(ESTADO_LISTO),
            tiempoEjecucion(0.0f), memoriaKB(0) {}
    PCB(int p, const std::string& n, int pr, float t)
        : pid(p), nombre(n), prioridad(pr), estado(ESTADO_LISTO),
          tiempoEjecucion(t), memoriaKB(0) {}
};

// ---- funciones de validacion ----
inline bool pidValido(int pid)       { return pid > 0; }
inline bool prioridadValida(int pr)  { return pr >= 1 && pr <= 10; }
inline bool estadoValido(const std::string& e) {
    return e == ESTADO_LISTO || e == ESTADO_EJECUCION ||
           e == ESTADO_BLOQUEADO || e == ESTADO_TERMINADO;
}

#endif
