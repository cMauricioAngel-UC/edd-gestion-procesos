#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

// MODULO DE: Mauricio

#include <string>
#include "ListaProcesos.h"
#include "ColaPrioridad.h"
#include "PilaMemoria.h"

// Guarda los tres archivos (procesos.txt, cola.txt, memoria.txt).
// Escribe primero en .tmp y luego reemplaza, para no dejar estados parciales.
bool guardarTodo(const ListaProcesos& l, const ColaPrioridad& c,
                 const PilaMemoria& m, std::string& error);

// Carga procesos -> cola -> memoria y valida consistencia.
// Si un archivo no existe se considera primera ejecucion (estado vacio).
// Si algo es invalido: deja todo vacio, devuelve false y explica en error.
bool cargarTodo(ListaProcesos& l, ColaPrioridad& c, PilaMemoria& m,
                std::string& error);

#endif
