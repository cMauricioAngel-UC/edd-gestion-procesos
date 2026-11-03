#ifndef COLAPRIORIDAD_H
#define COLAPRIORIDAD_H

// MODULO DE ISAI. Esta version es solo una REFERENCIA de integracion:
// reemplazar por la implementacion de Isai, manteniendo estas firmas.

// Cola enlazada de prioridad: el frente es el de menor valor numerico.
// En empates se respeta el orden de llegada (FIFO).
class ColaPrioridad {
public:
    typedef void (*Visitante)(int pid, int prioridad, void*);

    ColaPrioridad();
    ~ColaPrioridad();

    void encolar(int pid, int prioridad);     // ignora PID repetido: consultar contiene() antes
    bool desencolar(int& pid, int& prioridad);// false si esta vacia
    bool eliminarPid(int pid);
    bool contiene(int pid) const;
    void recorrer(Visitante v, void* ctx) const; // frente -> final
    void liberarTodo();
    int  tamanio() const;
    bool vacia() const;

private:
    // Nodo: solo PID y prioridad (el PCB completo vive en la lista).
    struct Nodo {
        int   pid;
        int   prioridad;
        Nodo* siguiente;
    };
    Nodo* frente_;
    int       cantidad_;
    ColaPrioridad(const ColaPrioridad&);
    ColaPrioridad& operator=(const ColaPrioridad&);
};

#endif
