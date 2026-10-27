# Avance fácil de explicar el 27/10

Compila únicamente `main.cpp` en C++98. Esta versión muestra una lista enlazada de procesos con operaciones reales de insertar, buscar por PID, eliminar y mostrar. Está escrita con el mismo patrón de las prácticas de la semana 9: `struct Nodo`, puntero a cabeza, `new`, `delete` y recorridos `while`.

**No es la entrega final.** Falta buscar por nombre, cambiar prioridad, cola ordenada, pila de memoria, persistencia y la integración. Anthony debe revisar, explicar y completar la lista como su módulo; Isai y Kevin implementan sus estructuras, cada uno con su propia contribución y commits. Mauricio integra después.

Secuencia para demostrar: registrar PID 101 con prioridad 3, registrar PID 102 con prioridad 1, listar, buscar 101, eliminar 101 y listar de nuevo. Explica que la lista inserta al inicio, de modo que se ve 102 antes que 101; eso **no** representa todavía el orden de ejecución de la cola.
