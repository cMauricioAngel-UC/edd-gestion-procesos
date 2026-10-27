# Guía de integración para el equipo

## Reglas compartidas

- `PCB.h` define el dato único del proceso. La lista conserva el PCB; cola y pila guardan solo PID y su valor (prioridad o KB).
- Los headers de `include/` fijan las firmas. Implementar sin cambiarlas; avisar antes de proponer una nueva operación.
- El proyecto debe compilar en C++98. Usar `NULL`, constructores y destructores; liberar todos los nodos.
- Cada módulo incluye `liberarTodo()` para reiniciar ante una carga inválida y un método de recorrido para guardar en disco.
- No usar contenedores STL para representar las tres estructuras.

## Anthony — `ListaProcesos`

Nodo sugerido: `PCB dato; Nodo* siguiente;`. `insertar` rechaza PID repetido; `eliminar` contempla cabeza, interior y lista vacía; `buscarPorPid` y `buscarPorNombre` recorren hasta hallar el primer resultado. `recorrer` visita cada PCB sin modificarlo.

Casos mínimos: lista vacía, PID duplicado, primer y último nodo, búsqueda inexistente, prioridad fuera de 1–10, destructor sin fugas.

## Isai — `ColaPrioridad`

Nodo sugerido: `int pid, prioridad; Nodo* siguiente;`. Ordenar al insertar de menor prioridad numérica a mayor. En empates, insertar **después** de los existentes para conservar FIFO. `desencolar` quita el frente. `eliminarPid` y `contiene` recorren por PID. `recorrer` visita del frente al final.

Caso mínimo: encolar `(A,3), (B,1), (C,3)` y desencolar `B, A, C`; probar cola vacía y eliminación de un nodo interior.

## Kevin — `PilaMemoria`

Nodo sugerido: `int pid, kb; Nodo* siguiente;`. Mantener `usadosKB_` entre 0 y 1024. `push` rechaza KB no positivos o sin capacidad; `pop` libera el tope. `liberarPorPid` usa una pila auxiliar propia y vuelve a apilar el resto en el orden original. `recorrerDesdeBase` debe visitar de la base al tope para que la carga conserve el estado.

Caso mínimo: bloques `A, B, A, C`; liberar A; deben quedar `B, C` con C arriba. Probar 1024 KB exactos, exceso y pila vacía.

## Mauricio — integración

- Registrar: agregar a la lista en estado `Listo`.
- Encolar: exigir PID existente, no terminado, no bloqueado y no repetido en cola.
- Cambiar prioridad: actualizar PCB y reubicar si está en cola.
- Ejecutar: desencolar, marcar `Ejecucion` y luego `Terminado`, liberar sus bloques.
- Eliminar: retirar de cola, liberar memoria y eliminar de lista.
- Persistir: guardar los tres recorridos; cargar procesos primero, cola segundo y memoria al final.

**Al integrar:** probar que `memoriaKB` en cada PCB coincide con los bloques de la pila. El cargador actual valida PID y límites pero todavía no verifica ese total cruzado. Si la carga falla, `main.cpp` termina antes de guardar, para preservar los archivos que requieren corrección.
