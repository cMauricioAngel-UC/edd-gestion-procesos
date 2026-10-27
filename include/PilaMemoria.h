#ifndef ED_PILA_MEMORIA_H
#define ED_PILA_MEMORIA_H

// Kevin: pila enlazada de bloques; capacidad total 1024 KB.
class PilaMemoria {
public:
    PilaMemoria();
    ~PilaMemoria();
    bool push(int pid, int kb);
    bool pop(int& pid, int& kb);
    int liberarPorPid(int pid); // devuelve KB liberados, preserva el orden restante
    bool contiene(int pid) const;
    void estado() const;
    bool vacia() const;
    void liberarTodo();
    // Recorre desde la base al tope para restaurar el mismo orden al cargar.
    void recorrerDesdeBase(void (*visitar)(int, int, void*), void* contexto) const;
private:
    struct Nodo;
    Nodo* tope_;
    int usadosKB_;
    PilaMemoria(const PilaMemoria&);
    PilaMemoria& operator=(const PilaMemoria&);
};

#endif
