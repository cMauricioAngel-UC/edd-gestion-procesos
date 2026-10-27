#include <iostream>
#include <string>

using namespace std;

// Version corta para explicar el avance del 27/10.
// Anthony puede tomar estas funciones como punto de partida de su modulo.
struct PCB {
    int pid;
    string nombre;
    int prioridad; // 1 es la mas alta
    string estado;
};

struct NodoProceso {
    PCB dato;
    NodoProceso* siguiente;
};

NodoProceso* buscar(NodoProceso* lista, int pid) {
    while (lista != NULL) {
        if (lista->dato.pid == pid) return lista;
        lista = lista->siguiente;
    }
    return NULL;
}

bool insertar(NodoProceso*& lista, const PCB& nuevo) {
    if (buscar(lista, nuevo.pid) != NULL) return false;
    NodoProceso* nodo = new NodoProceso;
    nodo->dato = nuevo;
    nodo->siguiente = lista;
    lista = nodo;
    return true;
}

bool eliminar(NodoProceso*& lista, int pid) {
    NodoProceso* actual = lista;
    NodoProceso* anterior = NULL;
    while (actual != NULL && actual->dato.pid != pid) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == NULL) return false;
    if (anterior == NULL) lista = actual->siguiente;
    else anterior->siguiente = actual->siguiente;
    delete actual;
    return true;
}

void mostrar(NodoProceso* lista) {
    if (lista == NULL) cout << "No hay procesos.\n";
    while (lista != NULL) {
        cout << "PID " << lista->dato.pid
             << " | " << lista->dato.nombre
             << " | prioridad " << lista->dato.prioridad
             << " | " << lista->dato.estado << '\n';
        lista = lista->siguiente;
    }
}

void liberar(NodoProceso*& lista) {
    while (lista != NULL) {
        NodoProceso* siguiente = lista->siguiente;
        delete lista;
        lista = siguiente;
    }
}

bool leerEntero(const string& mensaje, int& valor) {
    cout << mensaje;
    if (cin >> valor) return true;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Ingrese un numero entero.\n";
    return false;
}

int main() {
    NodoProceso* lista = NULL;
    int opcion = -1;
    cout << "GESTION DE PROCESOS - AVANCE DIDACTICO\n";
    cout << "Funciona la lista. Cola, pila y archivos siguen pendientes.\n";

    do {
        cout << "\n1 Registrar  2 Buscar  3 Eliminar  4 Listar\n";
        cout << "5 Cola (pendiente)  6 Pila (pendiente)";
        cout << "  7 Guardar/cargar (pendiente)  0 Salir\n";
        if (!leerEntero("Opcion: ", opcion)) continue;

        if (opcion == 1) {
            PCB p;
            if (!leerEntero("PID positivo: ", p.pid)) continue;
            if (p.pid <= 0) { cout << "PID invalido.\n"; continue; }
            cout << "Nombre: ";
            cin >> ws;
            getline(cin, p.nombre);
            if (p.nombre.empty()) { cout << "Nombre vacio.\n"; continue; }
            if (!leerEntero("Prioridad (1-10): ", p.prioridad)) continue;
            if (p.prioridad < 1 || p.prioridad > 10) {
                cout << "Prioridad invalida.\n"; continue;
            }
            p.estado = "Listo";
            cout << (insertar(lista, p) ? "Registrado.\n" : "PID repetido.\n");
        } else if (opcion == 2) {
            int pid;
            if (!leerEntero("PID a buscar: ", pid)) continue;
            NodoProceso* encontrado = buscar(lista, pid);
            if (encontrado != NULL)
                cout << encontrado->dato.nombre << " (" << encontrado->dato.estado << ")\n";
            else cout << "No encontrado.\n";
        } else if (opcion == 3) {
            int pid;
            if (!leerEntero("PID a eliminar: ", pid)) continue;
            cout << (eliminar(lista, pid) ? "Eliminado.\n" : "No encontrado.\n");
        } else if (opcion == 4) mostrar(lista);
        else if (opcion >= 5 && opcion <= 7)
            cout << "Pendiente: responsable debe integrar su modulo.\n";
        else if (opcion != 0) cout << "Opcion invalida.\n";
    } while (opcion != 0 && !cin.eof());

    liberar(lista);
    return 0;
}
