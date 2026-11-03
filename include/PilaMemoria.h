#ifndef PILAMEMORIA_H
#define PILAMEMORIA_H

// MODULO DE: Mauricio

// Pila enlazada de bloques. Capacidad total simulada: 1024 KB.
class PilaMemoria {
public:
    typedef void (*Visitante)(int pid, int kb, void*);
    static const int CAPACIDAD_KB = 1024;

    PilaMemoria();
    ~PilaMemoria();

    bool push(int pid, int kb);               // false si kb<=0 o sin espacio
    bool pop(int& pid, int& kb);              // false si esta vacia
    int  liberarPorPid(int pid);              // devuelve KB liberados
    int  totalPorPid(int pid) const;
    int  bloquesDePid(int pid) const;         // cantidad de bloques
    void recorrerDesdeBase(Visitante v, void* ctx) const; // base -> tope
    void liberarTodo();
    int  usadosKB() const;
    int  libresKB() const;
    int  tamanio() const;
    bool vacia() const;

private:
    // Nodo: bloque de memoria de un PID; siguiente = bloque inferior.
    struct Nodo {
        int   pid;
        int   kb;
        Nodo* siguiente;
    };
    Nodo* tope_;
    int          usadosKB_;
    int          cantidad_;
    static void recorrerRec(const Nodo* n, Visitante v, void* ctx);
    PilaMemoria(const PilaMemoria&);
    PilaMemoria& operator=(const PilaMemoria&);
};

#endif
