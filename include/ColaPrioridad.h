#ifndef ED_COLA_PRIORIDAD_H
#define ED_COLA_PRIORIDAD_H

// Isai: cola enlazada ordenada. Prioridad 1 primero; empates FIFO.
class ColaPrioridad {
public:
    ColaPrioridad();
    ~ColaPrioridad();
    void encolar(int pid, int prioridad);
    bool desencolar(int& pid);
    bool eliminarPid(int pid);
    bool contiene(int pid) const;
    void mostrar() const;
    bool vacia() const;
    void liberarTodo();
    // Recorre del proximo a ejecutar al ultimo; lo usa persistencia.
    void recorrer(void (*visitar)(int, int, void*), void* contexto) const;
private:
    struct Nodo;
    Nodo* frente_;
    ColaPrioridad(const ColaPrioridad&);
    ColaPrioridad& operator=(const ColaPrioridad&);
};

#endif
