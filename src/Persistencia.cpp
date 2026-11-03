#include <cstdio>
#include <fstream>
#include <sstream>
#include "Persistencia.h"

static const char* F_PROC = "procesos.txt";
static const char* F_COLA = "cola.txt";
static const char* F_MEM  = "memoria.txt";

static void escribirProc(const PCB& p, void* ctx) {
    std::ofstream* f = static_cast<std::ofstream*>(ctx);
    *f << p.pid << ' ' << p.prioridad << ' ' << p.estado << ' '
       << p.tiempoEjecucion << ' ' << p.memoriaKB << ' ' << p.nombre << '\n';
}
static void escribirPar(int a, int b, void* ctx) {
    std::ofstream* f = static_cast<std::ofstream*>(ctx);
    *f << a << ' ' << b << '\n';
}

static bool reemplazar(const char* destino) {
    std::string tmp = std::string(destino) + ".tmp";
    std::remove(destino);   // en Windows rename no sobrescribe
    return std::rename(tmp.c_str(), destino) == 0;
}

bool guardarTodo(const ListaProcesos& l, const ColaPrioridad& c,
                 const PilaMemoria& m, std::string& error) {
    std::string t1 = std::string(F_PROC) + ".tmp";
    std::string t2 = std::string(F_COLA) + ".tmp";
    std::string t3 = std::string(F_MEM) + ".tmp";
    {
        std::ofstream f1(t1.c_str()), f2(t2.c_str()), f3(t3.c_str());
        if (!f1 || !f2 || !f3) { error = "No se pudo crear un archivo temporal."; return false; }
        l.recorrer(escribirProc, &f1);
        c.recorrer(escribirPar, &f2);
        m.recorrerDesdeBase(escribirPar, &f3);
        if (!f1.good() || !f2.good() || !f3.good()) { error = "Error al escribir."; return false; }
    } // se cierran los archivos aqui
    if (!reemplazar(F_PROC) || !reemplazar(F_COLA) || !reemplazar(F_MEM)) {
        error = "No se pudo reemplazar un archivo.";
        return false;
    }
    return true;
}

struct CtxVerif { const PilaMemoria* m; bool ok; };
static void verificarMem(const PCB& p, void* ctx) {
    CtxVerif* c = static_cast<CtxVerif*>(ctx);
    if (c->m->totalPorPid(p.pid) != p.memoriaKB) c->ok = false;
}

static bool cargarInterno(ListaProcesos& l, ColaPrioridad& c, PilaMemoria& m,
                          std::string& error) {
    std::string linea;
    // Primera ejecucion (ningun archivo) != archivos incompletos (error).
    int presentes = 0;
    if (std::ifstream(F_PROC).is_open()) presentes++;
    if (std::ifstream(F_COLA).is_open()) presentes++;
    if (std::ifstream(F_MEM).is_open())  presentes++;
    if (presentes == 0) return true;
    if (presentes < 3) { error = "faltan archivos de datos (carga incompleta)"; return false; }
    {   // ---- procesos ----
        std::ifstream f(F_PROC);
        while (f && std::getline(f, linea)) {
            if (linea.empty()) continue;
            std::istringstream s(linea);
            PCB p; std::string est;
            if (!(s >> p.pid >> p.prioridad >> est >> p.tiempoEjecucion >> p.memoriaKB)) {
                error = "procesos.txt: linea invalida"; return false; }
            std::getline(s, p.nombre);
            if (!p.nombre.empty() && p.nombre[0] == ' ') p.nombre.erase(0, 1);
            if (p.pid <= 0 || p.prioridad < 1 || p.prioridad > 10 || !estadoValido(est) ||
                p.tiempoEjecucion < 0 || p.memoriaKB < 0 || p.nombre.empty()) {
                error = "procesos.txt: valores fuera de rango"; return false; }
            p.estado = est;
            if (!l.insertar(p)) { error = "procesos.txt: PID repetido"; return false; }
        }
    }
    {   // ---- cola ----
        std::ifstream f(F_COLA);
        int pid, pr;
        while (std::getline(f, linea)) {
            if (linea.empty()) continue;
            std::istringstream fila(linea); std::string sobrante;
            if (!(fila >> pid >> pr) || (fila >> sobrante)) { error = "cola.txt: formato invalido"; return false; }
            PCB* p = l.buscarPorPid(pid);
            if (p == NULL || p->prioridad != pr || p->estado != ESTADO_LISTO || c.contiene(pid)) {
                error = "cola.txt: entrada inconsistente"; return false; }
            c.encolar(pid, pr);
        }
        if (f.is_open() && !f.eof()) { error = "cola.txt: formato invalido"; return false; }
    }
    {   // ---- memoria (base -> tope) ----
        std::ifstream f(F_MEM);
        int pid, kb;
        while (std::getline(f, linea)) {
            if (linea.empty()) continue;
            std::istringstream fila(linea); std::string sobrante;
            if (!(fila >> pid >> kb) || (fila >> sobrante)) { error = "memoria.txt: formato invalido"; return false; }
            if (l.buscarPorPid(pid) == NULL || l.buscarPorPid(pid)->estado == ESTADO_TERMINADO || !m.push(pid, kb)) {
                error = "memoria.txt: entrada inconsistente"; return false; }
        }
        if (f.is_open() && !f.eof()) { error = "memoria.txt: formato invalido"; return false; }
    }
    CtxVerif v; v.m = &m; v.ok = true;   // memoriaKB del PCB == suma en la pila
    l.recorrer(verificarMem, &v);
    if (!v.ok) { error = "memoriaKB de un PCB no coincide con la pila"; return false; }
    return true;
}

bool cargarTodo(ListaProcesos& l, ColaPrioridad& c, PilaMemoria& m,
                std::string& error) {
    l.liberarTodo(); c.liberarTodo(); m.liberarTodo();
    if (cargarInterno(l, c, m, error)) return true;
    l.liberarTodo(); c.liberarTodo(); m.liberarTodo();
    return false;
}
