#include <iostream>
#include <string>
#include <cstdlib>
#include "PCB.h"
#include "ListaProcesos.h"
#include "ColaPrioridad.h"
#include "PilaMemoria.h"
#include "Persistencia.h"

using namespace std;

// Las tres estructuras y sus operaciones se agrupan para pasarlas a los menus.
struct Sistema {
    ListaProcesos lista;
    ColaPrioridad cola;
    PilaMemoria   pila;
};

// ---------- entrada validada (rechaza texto sobrante) ----------
static bool leerEntero(const char* msg, int minimo, int maximo, int& out) {
    cout << msg;
    string s;
    if (!getline(cin, s)) return false;
    char* fin = NULL;
    long v = strtol(s.c_str(), &fin, 10);
    if (s.empty() || fin == s.c_str() || *fin != '\0' || v < minimo || v > maximo) {
        cout << "  Valor invalido (rango " << minimo << ".." << maximo << ").\n";
        return false;
    }
    out = (int)v;
    return true;
}
static bool leerFloat(const char* msg, float& out) {
    cout << msg;
    string s;
    if (!getline(cin, s)) return false;
    char* fin = NULL;
    double v = strtod(s.c_str(), &fin);
    if (s.empty() || fin == s.c_str() || *fin != '\0' || v != v || v < 0 || v > 1000000) {
        cout << "  Valor invalido (numero >= 0).\n";
        return false;
    }
    out = (float)v;
    return true;
}

// ---------- impresion ----------
static void imprimirProc(const PCB& p, void*) {
    cout << "  PID " << p.pid << " | " << p.nombre << " | prio " << p.prioridad
         << " | " << p.estado << " | t=" << p.tiempoEjecucion
         << " | mem=" << p.memoriaKB << " KB\n";
}
static void imprimirCola(int pid, int pr, void*) {
    cout << "  PID " << pid << " (prio " << pr << ")\n";
}
static void imprimirBloque(int pid, int kb, void*) {
    cout << "  PID " << pid << ": " << kb << " KB\n";
}

static bool pedirPid(int& pid) { return leerEntero("PID: ", 1, 2000000000, pid); }

// ---------- 1. Procesos ----------
static void registrar(Sistema& s) {
    int pid, pr; float t;
    if (!pedirPid(pid)) return;
    cout << "Nombre: ";
    string nombre;
    if (!getline(cin, nombre) || nombre.empty()) { cout << "  Nombre vacio.\n"; return; }
    if (!leerEntero("Prioridad (1-10, 1 = mas alta): ", 1, 10, pr)) return;
    if (!leerFloat("Tiempo estimado de ejecucion: ", t)) return;
    PCB p(pid, nombre, pr, t);      // estado Listo, memoria 0
    cout << (s.lista.insertar(p) ? "  Proceso registrado.\n" : "  Error: PID repetido o datos invalidos.\n");
}

static void buscarPid(Sistema& s) {
    int pid; if (!pedirPid(pid)) return;
    PCB* p = s.lista.buscarPorPid(pid);
    if (p) imprimirProc(*p, NULL); else cout << "  No existe.\n";
}

static void buscarNombre(Sistema& s) {
    cout << "Nombre: ";
    string n; getline(cin, n);
    PCB* p = s.lista.buscarPorNombre(n);   // primera coincidencia
    if (p) imprimirProc(*p, NULL); else cout << "  No existe.\n";
}

static void cambiarPrioridad(Sistema& s) {
    int pid, pr;
    if (!pedirPid(pid)) return;
    PCB* p = s.lista.buscarPorPid(pid);
    if (!p) { cout << "  No existe.\n"; return; }
    if (!leerEntero("Nueva prioridad (1-10): ", 1, 10, pr)) return;
    if (pr == p->prioridad) { cout << "  Sin cambios: ya tiene esa prioridad.\n"; return; }
    p->prioridad = pr;
    if (s.cola.contiene(pid)) { s.cola.eliminarPid(pid); s.cola.encolar(pid, pr); } // reubicar
    cout << "  Prioridad actualizada.\n";
}

static void cambiarEstado(Sistema& s) {
    int pid, e;
    if (!pedirPid(pid)) return;
    PCB* p = s.lista.buscarPorPid(pid);
    if (!p) { cout << "  No existe.\n"; return; }
    if (!leerEntero("Estado (1 Listo, 2 Ejecucion, 3 Bloqueado, 4 Terminado): ", 1, 4, e)) return;
    const char* nuevo = (e == 1) ? ESTADO_LISTO : (e == 2) ? ESTADO_EJECUCION
                      : (e == 3) ? ESTADO_BLOQUEADO : ESTADO_TERMINADO;
    if (e != 1) s.cola.eliminarPid(pid);          // la cola solo admite Listos
    if (e == 4) { s.pila.liberarPorPid(pid); p->memoriaKB = 0; }
    p->estado = nuevo;
    cout << "  Estado actualizado.\n";
}

static void eliminar(Sistema& s) {
    int pid; if (!pedirPid(pid)) return;
    if (!s.lista.buscarPorPid(pid)) { cout << "  No existe.\n"; return; }
    s.cola.eliminarPid(pid);      // 1) retirar de la cola
    s.pila.liberarPorPid(pid);    // 2) liberar sus bloques
    s.lista.eliminar(pid);        // 3) eliminar de la lista
    cout << "  Proceso eliminado.\n";
}

static void menuProcesos(Sistema& s) {
    int op = -1;
    while (op != 0) {
        cout << "\n--- PROCESOS ---\n 1 Registrar\n 2 Listar\n 3 Buscar por PID\n"
             << " 4 Buscar por nombre\n 5 Cambiar prioridad\n 6 Cambiar estado\n"
             << " 7 Eliminar\n 0 Volver\n";
        if (!leerEntero("Opcion: ", 0, 7, op)) { if (cin.eof()) return; op = -1; continue; }
        switch (op) {
            case 1: registrar(s); break;
            case 2: if (s.lista.vacia()) cout << "  (sin procesos)\n"; else s.lista.recorrer(imprimirProc, NULL); break;
            case 3: buscarPid(s); break;
            case 4: buscarNombre(s); break;
            case 5: cambiarPrioridad(s); break;
            case 6: cambiarEstado(s); break;
            case 7: eliminar(s); break;
        }
    }
}

// ---------- 2. Planificador ----------
static void encolar(Sistema& s) {
    int pid; if (!pedirPid(pid)) return;
    PCB* p = s.lista.buscarPorPid(pid);
    if (!p) { cout << "  No existe.\n"; return; }
    if (p->estado != ESTADO_LISTO) { cout << "  Solo se encolan procesos Listos (no Bloqueado/Terminado).\n"; return; }
    if (s.cola.contiene(pid)) { cout << "  Ya esta en la cola.\n"; return; }
    s.cola.encolar(pid, p->prioridad);
    cout << "  Encolado.\n";
}

static void ejecutarSiguiente(Sistema& s) {
    int pid, pr;
    if (!s.cola.desencolar(pid, pr)) { cout << "  La cola esta vacia.\n"; return; }
    PCB* p = s.lista.buscarPorPid(pid);
    if (!p) return;
    p->estado = ESTADO_EJECUCION;
    cout << "  Ejecutando PID " << pid << " (" << p->nombre << ")...\n";
    int kb = s.pila.liberarPorPid(pid);     // solo los bloques de ESTE PID
    p->memoriaKB = 0;
    p->estado = ESTADO_TERMINADO;
    cout << "  Termino. Memoria liberada: " << kb << " KB.\n";
}

static void menuPlanificador(Sistema& s) {
    int op = -1;
    while (op != 0) {
        cout << "\n--- PLANIFICADOR ---\n 1 Encolar proceso\n 2 Mostrar cola\n"
             << " 3 Ejecutar siguiente\n 0 Volver\n";
        if (!leerEntero("Opcion: ", 0, 3, op)) { if (cin.eof()) return; op = -1; continue; }
        switch (op) {
            case 1: encolar(s); break;
            case 2: if (s.cola.vacia()) cout << "  (cola vacia)\n"; else s.cola.recorrer(imprimirCola, NULL); break;
            case 3: ejecutarSiguiente(s); break;
        }
    }
}

// ---------- 3. Memoria ----------
static void asignarMemoria(Sistema& s) {
    int pid, kb;
    if (!pedirPid(pid)) return;
    PCB* p = s.lista.buscarPorPid(pid);
    if (!p) { cout << "  No existe.\n"; return; }
    if (p->estado == ESTADO_TERMINADO) { cout << "  El proceso ya termino.\n"; return; }
    if (!leerEntero("KB a asignar: ", 1, PilaMemoria::CAPACIDAD_KB, kb)) return;
    if (!s.pila.push(pid, kb)) { cout << "  Memoria insuficiente (libres: " << s.pila.libresKB() << " KB).\n"; return; }
    p->memoriaKB += kb;
    cout << "  Bloque asignado.\n";
}

static void liberarTope(Sistema& s) {
    int pid, kb;
    if (!s.pila.pop(pid, kb)) { cout << "  La pila esta vacia.\n"; return; }
    PCB* p = s.lista.buscarPorPid(pid);
    if (p) p->memoriaKB -= kb;
    cout << "  Liberado bloque de PID " << pid << ": " << kb << " KB.\n";
}

static void liberarPid(Sistema& s) {
    int pid; if (!pedirPid(pid)) return;
    PCB* p = s.lista.buscarPorPid(pid);
    if (!p) { cout << "  No existe.\n"; return; }
    int kb = s.pila.liberarPorPid(pid);
    p->memoriaKB = 0;
    cout << "  Liberados " << kb << " KB.\n";
}

static void buscarBloques(Sistema& s) {
    int pid; if (!pedirPid(pid)) return;
    cout << "  PID " << pid << ": " << s.pila.bloquesDePid(pid) << " bloque(s), "
         << s.pila.totalPorPid(pid) << " KB.\n";
}

static void menuMemoria(Sistema& s) {
    int op = -1;
    while (op != 0) {
        cout << "\n--- MEMORIA ---\n 1 Asignar bloque\n 2 Liberar tope\n"
             << " 3 Liberar todos los bloques de un PID\n 4 Buscar bloques de un PID\n"
             << " 5 Mostrar memoria\n 0 Volver\n";
        if (!leerEntero("Opcion: ", 0, 5, op)) { if (cin.eof()) return; op = -1; continue; }
        switch (op) {
            case 1: asignarMemoria(s); break;
            case 2: liberarTope(s); break;
            case 3: liberarPid(s); break;
            case 4: buscarBloques(s); break;
            case 5:
                cout << "  Usados: " << s.pila.usadosKB() << " / " << PilaMemoria::CAPACIDAD_KB << " KB (base -> tope)\n";
                s.pila.recorrerDesdeBase(imprimirBloque, NULL);
                break;
        }
    }
}

// ---------- principal ----------
static void guardar(Sistema& s) {
    string err;
    if (guardarTodo(s.lista, s.cola, s.pila, err)) cout << "  Guardado.\n";
    else cout << "  Error al guardar: " << err << "\n";
}

int main() {
    Sistema s;
    string err;
    if (!cargarTodo(s.lista, s.cola, s.pila, err)) {
        // No se guarda nada: se preservan los archivos para corregirlos.
        cout << "Error al cargar datos: " << err << "\nCorrija los archivos .txt y reinicie.\n";
        return 1;
    }
    int op = -1;
    while (op != 0) {
        cout << "\n===== GESTION DE PROCESOS =====\n 1 Procesos\n 2 Planificador\n"
             << " 3 Memoria\n 4 Guardar ahora\n 0 Salir\n";
        if (!leerEntero("Opcion: ", 0, 4, op)) { if (cin.eof()) break; op = -1; continue; }
        switch (op) {
            case 1: menuProcesos(s); break;
            case 2: menuPlanificador(s); break;
            case 3: menuMemoria(s); break;
            case 4: guardar(s); break;
            case 0: guardar(s); break;
        }
    }
    return 0;
}
