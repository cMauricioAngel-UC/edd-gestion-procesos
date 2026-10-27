#ifndef ED_PERSISTENCIA_H
#define ED_PERSISTENCIA_H

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include "ListaProcesos.h"
#include "ColaPrioridad.h"
#include "PilaMemoria.h"

// Mauricio: formato de tres archivos separados por ';'. Un nombre no puede
// contener ';' ni saltos de linea. No se usan contenedores STL para las ED.
class Persistencia {
    struct ContextoArchivo {
        std::ostream* salida;
        bool correcto;
        explicit ContextoArchivo(std::ostream& s) : salida(&s), correcto(true) {}
    };

    static bool textoSeguro(const std::string& valor) {
        return valor.find(';') == std::string::npos &&
               valor.find('\n') == std::string::npos &&
               valor.find('\r') == std::string::npos;
    }

    static void escribirProceso(const PCB& p, void* dato) {
        ContextoArchivo& c = *static_cast<ContextoArchivo*>(dato);
        if (!textoSeguro(p.nombre) || !textoSeguro(p.estado)) {
            c.correcto = false;
            return;
        }
        *c.salida << p.pid << ';' << p.nombre << ';' << p.prioridad << ';'
                  << p.estado << ';' << std::setprecision(9)
                  << p.tiempoEjecucion << ';' << p.memoriaKB << '\n';
        if (!*c.salida) c.correcto = false;
    }

    static void escribirPar(int pid, int valor, void* dato) {
        ContextoArchivo& c = *static_cast<ContextoArchivo*>(dato);
        *c.salida << pid << ';' << valor << '\n';
        if (!*c.salida) c.correcto = false;
    }

    static bool entero(const std::string& texto, int& valor) {
        std::istringstream entrada(texto);
        char sobrante;
        return (entrada >> valor) && !(entrada >> sobrante);
    }

    static bool decimal(const std::string& texto, float& valor) {
        std::istringstream entrada(texto);
        char sobrante;
        return (entrada >> valor) && !(entrada >> sobrante);
    }

    static bool separarPar(const std::string& linea, int& pid, int& valor) {
        int separadores = 0;
        for (std::string::size_type i = 0; i < linea.size(); ++i)
            if (linea[i] == ';') ++separadores;
        if (separadores != 1) return false;
        std::istringstream entrada(linea);
        std::string a, b, extra;
        if (!std::getline(entrada, a, ';') ||
            !std::getline(entrada, b, ';') ||
            std::getline(entrada, extra, ';')) return false;
        return entero(a, pid) && entero(b, valor) && pid > 0;
    }

    static bool separarProceso(const std::string& linea, PCB& p) {
        int separadores = 0;
        for (std::string::size_type i = 0; i < linea.size(); ++i)
            if (linea[i] == ';') ++separadores;
        if (separadores != 5) return false;
        std::istringstream entrada(linea);
        std::string campos[6], extra;
        for (int i = 0; i < 6; ++i)
            if (!std::getline(entrada, campos[i], ';')) return false;
        if (std::getline(entrada, extra, ';')) return false;
        p.nombre = campos[1];
        p.estado = campos[3];
        return entero(campos[0], p.pid) && entero(campos[2], p.prioridad) &&
               decimal(campos[4], p.tiempoEjecucion) &&
               entero(campos[5], p.memoriaKB) && p.pid > 0 &&
               !p.nombre.empty() && prioridadValida(p.prioridad) &&
               estadoValido(p.estado) && p.tiempoEjecucion >= 0 &&
               p.memoriaKB >= 0;
    }

    static void limpiar(ListaProcesos& lista, ColaPrioridad& cola,
                        PilaMemoria& pila) {
        lista.liberarTodo();
        cola.liberarTodo();
        pila.liberarTodo();
    }

public:
    static bool guardar(const ListaProcesos& lista, const ColaPrioridad& cola,
                        const PilaMemoria& pila,
                        const std::string& directorio = ".") {
        std::ofstream procesos((directorio + "/procesos.txt").c_str());
        std::ofstream turnos((directorio + "/cola.txt").c_str());
        std::ofstream memoria((directorio + "/memoria.txt").c_str());
        if (!procesos || !turnos || !memoria) return false;
        ContextoArchivo cp(procesos), cc(turnos), cm(memoria);
        lista.recorrer(escribirProceso, &cp);
        cola.recorrer(escribirPar, &cc);
        pila.recorrerDesdeBase(escribirPar, &cm);
        procesos.flush(); turnos.flush(); memoria.flush();
        return cp.correcto && cc.correcto && cm.correcto &&
               procesos.good() && turnos.good() && memoria.good();
    }

    // Llamar al iniciar, antes de aceptar operaciones del usuario. Si los tres
    // archivos faltan, es la primera ejecucion. Un archivo corrupto deja las
    // estructuras vacias y devuelve false para que el error sea visible.
    static bool cargar(ListaProcesos& lista, ColaPrioridad& cola,
                       PilaMemoria& pila,
                       const std::string& directorio = ".") {
        std::ifstream procesos((directorio + "/procesos.txt").c_str());
        std::ifstream turnos((directorio + "/cola.txt").c_str());
        std::ifstream memoria((directorio + "/memoria.txt").c_str());
        if (!procesos && !turnos && !memoria) return true;
        if (!procesos || !turnos || !memoria) return false;
        limpiar(lista, cola, pila);
        std::string linea;
        while (std::getline(procesos, linea)) {
            PCB p;
            if (!separarProceso(linea, p) || !lista.insertar(p)) {
                limpiar(lista, cola, pila); return false;
            }
        }
        while (std::getline(turnos, linea)) {
            int pid, prioridad;
            if (!separarPar(linea, pid, prioridad) ||
                !prioridadValida(prioridad) || cola.contiene(pid) ||
                !lista.buscarPorPid(pid) ||
                lista.buscarPorPid(pid)->prioridad != prioridad ||
                lista.buscarPorPid(pid)->estado == "Terminado") {
                limpiar(lista, cola, pila); return false;
            }
            cola.encolar(pid, prioridad);
        }
        while (std::getline(memoria, linea)) {
            int pid, kb;
            if (!separarPar(linea, pid, kb) || kb <= 0 ||
                !lista.buscarPorPid(pid) ||
                lista.buscarPorPid(pid)->estado == "Terminado" ||
                !pila.push(pid, kb)) {
                limpiar(lista, cola, pila); return false;
            }
        }
        if (procesos.bad() || turnos.bad() || memoria.bad()) {
            limpiar(lista, cola, pila); return false;
        }
        return true;
    }
};

#endif
