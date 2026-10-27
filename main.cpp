#include <iostream>
#include <sstream>
#include <string>
#include "include/PCB.h"

// Compilacion actual: g++ -std=c++98 main.cpp -o gestor
// Tras integrar los tres modulos: g++ -std=c++98 -DED_MODULOS_LISTOS main.cpp ...
#ifdef ED_MODULOS_LISTOS
#include "include/ListaProcesos.h"
#include "include/ColaPrioridad.h"
#include "include/PilaMemoria.h"
#include "include/Persistencia.h"
#endif

static bool leerEntero(const std::string& etiqueta, int& valor) {
    std::string linea;
    std::cout << etiqueta;
    if (!std::getline(std::cin, linea)) return false;
    std::istringstream entrada(linea);
    char sobrante;
    if (!(entrada >> valor) || (entrada >> sobrante)) {
        std::cout << "Ingrese un numero entero valido.\n";
        return false;
    }
    return true;
}

#ifdef ED_MODULOS_LISTOS
static bool leerDecimal(const std::string& etiqueta, float& valor) {
    std::string linea;
    std::cout << etiqueta;
    if (!std::getline(std::cin, linea)) return false;
    std::istringstream entrada(linea);
    char sobrante;
    if (!(entrada >> valor) || (entrada >> sobrante)) {
        std::cout << "Ingrese un numero valido.\n";
        return false;
    }
    return true;
}

static bool leerTexto(const std::string& etiqueta, std::string& valor) {
    std::cout << etiqueta;
    if (!std::getline(std::cin, valor)) return false;
    if (valor.empty() || valor.find(';') != std::string::npos) {
        std::cout << "El texto no puede estar vacio ni contener ';'.\n";
        return false;
    }
    return true;
}

static void mostrarPCB(const PCB& p) {
    std::cout << "PID: " << p.pid << " | Nombre: " << p.nombre
              << " | Prioridad: " << p.prioridad << " | Estado: " << p.estado
              << " | Tiempo: " << p.tiempoEjecucion
              << " | Memoria: " << p.memoriaKB << " KB\n";
}

static void menuProcesos(ListaProcesos& lista, ColaPrioridad& cola,
                         PilaMemoria& pila) {
    int opcion;
    std::cout << "\nPROCESOS\n1 Registrar  2 Eliminar  3 Buscar PID  "
                 "4 Buscar nombre  5 Prioridad  6 Listar  7 Cambiar estado\n";
    if (!leerEntero("Opcion: ", opcion)) return;
    int pid;
    PCB* p;
    std::string texto;
    switch (opcion) {
    case 1: {
        PCB nuevo;
        if (!leerEntero("PID positivo: ", nuevo.pid) || nuevo.pid <= 0 ||
            !leerTexto("Nombre: ", nuevo.nombre) ||
            !leerEntero("Prioridad (1-10): ", nuevo.prioridad) ||
            !prioridadValida(nuevo.prioridad) ||
            !leerDecimal("Tiempo estimado de ejecucion: ",
                         nuevo.tiempoEjecucion) ||
            nuevo.tiempoEjecucion < 0) {
            std::cout << "Datos invalidos.\n"; return;
        }
        std::cout << (lista.insertar(nuevo) ? "Registrado.\n" :
                      "PID duplicado.\n");
        break;
    }
    case 2:
        if (!leerEntero("PID: ", pid)) return;
        if (!lista.buscarPorPid(pid)) { std::cout << "No existe.\n"; return; }
        cola.eliminarPid(pid);
        pila.liberarPorPid(pid);
        std::cout << (lista.eliminar(pid) ? "Eliminado en cascada.\n" :
                      "Error al eliminar.\n");
        break;
    case 3:
        if (!leerEntero("PID: ", pid)) return;
        p = lista.buscarPorPid(pid);
        if (p) mostrarPCB(*p); else std::cout << "No existe.\n";
        break;
    case 4:
        if (!leerTexto("Nombre: ", texto)) return;
        p = lista.buscarPorNombre(texto);
        if (p) mostrarPCB(*p); else std::cout << "No existe.\n";
        break;
    case 5: {
        int prioridad;
        if (!leerEntero("PID: ", pid) ||
            !leerEntero("Prioridad (1-10): ", prioridad) ||
            !prioridadValida(prioridad)) { std::cout << "Datos invalidos.\n"; return; }
        p = lista.buscarPorPid(pid);
        if (!p) { std::cout << "No existe.\n"; return; }
        const bool enCola = cola.contiene(pid);
        if (!lista.modificarPrioridad(pid, prioridad)) return;
        if (enCola) { cola.eliminarPid(pid); cola.encolar(pid, prioridad); }
        std::cout << "Prioridad actualizada.\n";
        break;
    }
    case 6: lista.mostrar(); break;
    case 7:
        if (!leerEntero("PID: ", pid) ||
            !leerTexto("Estado (Listo/Ejecucion/Bloqueado/Terminado): ", texto) ||
            !estadoValido(texto)) { std::cout << "Datos invalidos.\n"; return; }
        p = lista.buscarPorPid(pid);
        if (!p) { std::cout << "No existe.\n"; return; }
        if (texto == "Terminado") {
            cola.eliminarPid(pid);
            pila.liberarPorPid(pid);
            p->memoriaKB = 0;
        }
        if (texto == "Bloqueado") cola.eliminarPid(pid);
        lista.cambiarEstado(pid, texto);
        std::cout << "Estado actualizado.\n";
        break;
    default: std::cout << "Opcion desconocida.\n";
    }
}

static void menuCola(ListaProcesos& lista, ColaPrioridad& cola,
                     PilaMemoria& pila) {
    int opcion, pid;
    std::cout << "\nPLANIFICADOR\n1 Encolar  2 Ejecutar siguiente  3 Ver cola\n";
    if (!leerEntero("Opcion: ", opcion)) return;
    if (opcion == 1) {
        if (!leerEntero("PID: ", pid)) return;
        PCB* p = lista.buscarPorPid(pid);
        if (!p || p->estado == "Terminado" || p->estado == "Bloqueado" ||
            cola.contiene(pid)) { std::cout << "No se puede encolar.\n"; return; }
        cola.encolar(pid, p->prioridad);
        std::cout << "Encolado.\n";
    } else if (opcion == 2) {
        if (!cola.desencolar(pid)) { std::cout << "Cola vacia.\n"; return; }
        PCB* p = lista.buscarPorPid(pid);
        if (!p) { std::cout << "PID inexistente: estado inconsistente.\n"; return; }
        lista.cambiarEstado(pid, "Ejecucion");
        mostrarPCB(*p);
        lista.cambiarEstado(pid, "Terminado");
        pila.liberarPorPid(pid);
        p->memoriaKB = 0;
        std::cout << "Proceso terminado y memoria liberada.\n";
    } else if (opcion == 3) cola.mostrar();
    else std::cout << "Opcion desconocida.\n";
}

static void menuMemoria(ListaProcesos& lista, PilaMemoria& pila) {
    int opcion, pid, kb;
    std::cout << "\nMEMORIA\n1 Asignar  2 Liberar tope  "
                 "3 Liberar por PID  4 Estado\n";
    if (!leerEntero("Opcion: ", opcion)) return;
    if (opcion == 1) {
        if (!leerEntero("PID: ", pid) || !leerEntero("KB: ", kb) || kb <= 0)
            { std::cout << "Datos invalidos.\n"; return; }
        PCB* p = lista.buscarPorPid(pid);
        if (!p || p->estado == "Terminado")
            { std::cout << "PID inexistente o terminado.\n"; return; }
        if (pila.push(pid, kb)) { p->memoriaKB += kb; std::cout << "Asignado.\n"; }
        else std::cout << "Memoria insuficiente.\n";
    } else if (opcion == 2) {
        if (!pila.pop(pid, kb)) { std::cout << "Pila vacia.\n"; return; }
        PCB* p = lista.buscarPorPid(pid);
        if (p) p->memoriaKB -= kb;
        std::cout << "Liberados " << kb << " KB del PID " << pid << ".\n";
    } else if (opcion == 3) {
        if (!leerEntero("PID: ", pid)) return;
        kb = pila.liberarPorPid(pid);
        PCB* p = lista.buscarPorPid(pid);
        if (p) p->memoriaKB -= kb;
        std::cout << "Liberados " << kb << " KB.\n";
    } else if (opcion == 4) pila.estado();
    else std::cout << "Opcion desconocida.\n";
}
#endif

int main() {
    std::cout << "Sistema de Gestion de Procesos - C2-1 ED\n";
#ifdef ED_MODULOS_LISTOS
    ListaProcesos lista;
    ColaPrioridad cola;
    PilaMemoria pila;
    if (!Persistencia::cargar(lista, cola, pila)) {
        std::cerr << "No se pudo cargar el estado. Corrija los archivos antes "
                     "de iniciar; no se sobrescribiran.\n";
        return 1;
    }
#else
    std::cout << "Avance parcial: los modulos de lista, cola y pila estan pendientes.\n";
#endif
    int opcion;
    while (true) {
        std::cout << "\n1 Procesos  2 Planificador  3 Memoria  "
                     "4 Guardar ahora  0 Salir\n";
        if (!leerEntero("Opcion: ", opcion)) {
            if (std::cin.eof()) break;
            continue;
        }
        if (opcion == 0) break;
#ifdef ED_MODULOS_LISTOS
        if (opcion == 1) menuProcesos(lista, cola, pila);
        else if (opcion == 2) menuCola(lista, cola, pila);
        else if (opcion == 3) menuMemoria(lista, pila);
        else if (opcion == 4)
            std::cout << (Persistencia::guardar(lista, cola, pila) ?
                          "Guardado.\n" : "Error al guardar.\n");
        else std::cout << "Opcion desconocida.\n";
#else
        if (opcion >= 1 && opcion <= 4)
            std::cout << "Modulo pendiente de integracion.\n";
        else std::cout << "Opcion desconocida.\n";
#endif
    }
#ifdef ED_MODULOS_LISTOS
    if (!Persistencia::guardar(lista, cola, pila))
        std::cerr << "No se pudo guardar al salir.\n";
#endif
    return 0;
}
