#ifndef ED_LISTA_PROCESOS_H
#define ED_LISTA_PROCESOS_H

#include "PCB.h"

// Anthony: implementar con nodos enlazados propios, sin std::list.
// La lista conserva los PCB; cola y pila solo conservan PID y sus metadatos.
class ListaProcesos {
public:
    ListaProcesos();
    ~ListaProcesos();
    bool insertar(const PCB& proceso); // rechaza PID repetido
    bool eliminar(int pid);
    PCB* buscarPorPid(int pid);
    const PCB* buscarPorPid(int pid) const;
    PCB* buscarPorNombre(const std::string& nombre);
    bool modificarPrioridad(int pid, int prioridad);
    bool cambiarEstado(int pid, const std::string& estado);
    void mostrar() const;
    bool vacia() const;
    void liberarTodo();
    // Recorre de cabeza a cola; lo usa Mauricio para guardar en disco.
    void recorrer(void (*visitar)(const PCB&, void*), void* contexto) const;
private:
    struct Nodo;
    Nodo* cabeza_;
    ListaProcesos(const ListaProcesos&);
    ListaProcesos& operator=(const ListaProcesos&);
};

#endif
