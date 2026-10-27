# Capítulo 1. Análisis del problema — borrador C2-1

## 1.1 Descripción del problema

Un sistema operativo necesita registrar procesos, decidir cuál atender y administrar la memoria que les asigna. En esta simulación, cada proceso se identifica por un PID y conserva nombre, prioridad, estado, tiempo de ejecución y memoria asignada. El usuario debe poder crear, encontrar, actualizar y eliminar procesos; además, debe observar el orden de atención y liberar memoria al terminar un proceso.

La consigna de la Unidad 3 exige estructuras dinámicas lineales. Un arreglo estático de PCB requiere fijar una capacidad y desplazar elementos al insertar o eliminar en posiciones intermedias. La lista enlazada permite crecer según los procesos registrados y enlazar o retirar nodos sin desplazar el resto. Una cola de prioridad ordena los PID para atender primero el menor valor numérico de prioridad; entre prioridades iguales se conserva el orden de llegada. Una pila representa los bloques asignados y permite liberar directamente el último bloque.

El sistema propuesto usa una **lista enlazada de PCB**, una **cola enlazada de prioridad** y una **pila enlazada de bloques de memoria**. La lista es la fuente única de datos del proceso. La cola y la pila conservan solo el PID y el dato que necesitan, evitando copias divergentes del PCB.

## 1.2 Requerimientos funcionales

| ID | Requerimiento |
|---|---|
| RF1 | Registrar un proceso con PID único, nombre, prioridad entre 1 y 10 y estado inicial Listo. |
| RF2 | Buscar procesos por PID o nombre y mostrar sus datos. |
| RF3 | Modificar prioridad y reubicar el PID si se encuentra en la cola. |
| RF4 | Cambiar el estado entre Listo, Ejecucion, Bloqueado y Terminado. |
| RF5 | Eliminar un proceso y retirar también sus entradas de cola y memoria. |
| RF6 | Encolar procesos válidos por prioridad, conservando FIFO en empates. |
| RF7 | Desencolar y simular la ejecución; al terminar, liberar la memoria del proceso. |
| RF8 | Asignar bloques de memoria hasta un máximo total de 1024 KB; liberar el tope o los bloques de un PID. |
| RF9 | Mostrar la lista, la cola y el estado de memoria. |
| RF10 | Guardar y cargar el estado en archivos de texto. |

## 1.3 Requerimientos no funcionales

- Compatibilidad con el Dev-C++ usado por el equipo mediante C++98.
- Implementación propia de los nodos de lista, cola y pila, sin `std::list`, `std::queue` ni `std::stack`.
- Menú de consola comprensible y validación de PID, prioridad, tamaño de memoria y entrada no numérica.
- Liberación de nodos en destructores y en operaciones de borrado; ausencia de referencias a PCB eliminados.
- Historial Git y documentación que muestren las contribuciones de cada integrante.

## 1.4 Estructuras de datos y justificación

**PCB:** registro con `pid`, `nombre`, `prioridad`, `estado`, `tiempoEjecucion` y `memoriaKB`. Los posibles estados son un conjunto fijo; el programa los valida con comparaciones. Esto cubre el contraste solicitado entre datos de tamaño fijo y estructuras dinámicas.

**Lista enlazada:** un nodo contiene un PCB y un puntero al siguiente. Permite insertar y eliminar procesos sin mover otros nodos. Como no está ordenada por PID, buscar por PID o nombre toma O(n).

**Cola de prioridad enlazada:** un nodo contiene PID, prioridad y siguiente. La inserción recorre hasta su lugar O(n); extraer el frente toma O(1). En empates se inserta después de los nodos con igual prioridad.

**Pila de memoria enlazada:** cada nodo contiene PID, KB y siguiente. `push` y `pop` operan sobre el tope en O(1). Liberar todos los bloques de un PID requiere recorrer y reconstruir el orden con una pila auxiliar: O(n) tiempo y O(n) memoria auxiliar en el peor caso.

Un arreglo estático sirve para datos cuyo tamaño es conocido. Para procesos y bloques que cambian durante la ejecución, las estructuras enlazadas permiten ajustar la cantidad de nodos a la demanda. El límite de 1024 KB es una regla de la simulación, no el tamaño fijo de un arreglo.

## 1.5 Alcance y límites

El proyecto simula decisiones de un sistema operativo; no controla procesos reales del equipo ni mide tiempo de CPU. La docente indica que, además de la complejidad Big-O, se explique qué hacen y por qué se emplean los `if`, `while`, `for` y demás estructuras de control presentes en el código. El sistema se presentará con una demostración en consola y archivos de persistencia.
