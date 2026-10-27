# Guía breve para Mauricio y el equipo — 27/10/2026

## 1. Qué exige el curso y qué tenemos

El sílabo ubica listas, colas y pilas en la Unidad 3. Las prácticas de las semanas 9 y 10 trabajan nodos, punteros y operaciones básicas. El ABB pertenece a la Unidad 4; por eso se apartó del proyecto C2-1. La consigna exige las tres estructuras dinámicas lineales desde cero, cada una con inserción, eliminación y búsqueda, además de menú, guardado/carga, repositorio con aportes de todos, informe y sustentación.

| Criterio | Estado verificable al 26/10 | Qué falta |
|---|---|---|
| Lista dinámica | **Parcial:** ejemplo funcional en `version_para_equipo/main.cpp` con insertar, buscar PID, eliminar y mostrar | Buscar por nombre, modificar prioridad, integrar con cola y pila |
| Cola de prioridad | Solo contrato y borrador de integración | Isai: nodos propios, encolar ordenado, desencolar, buscar/eliminar PID, mostrar |
| Pila de memoria | Solo contrato y borrador de integración | Kevin: nodos propios, push/pop, búsqueda por PID, liberar por PID, capacidad |
| Menú | Existe en ambas versiones | Conectar todas las operaciones y comprobar casos vacíos |
| Persistencia | Código de lectura/escritura redactado, sin prueba integrada | Integrar con módulos y probar cerrar/reabrir |
| Evidencia de equipo | Git local creado; GitHub autenticado como `cMauricioAngel-UC` | Crear repositorio privado, commits de cada integrante, actas y tablero |
| Informe | Borradores de Caps. 1 y 2 | Revisar en grupo, completar diagramas, pruebas, manual y evidencias |

**Veredicto:** la elección de estructuras coincide con el sílabo y la consigna. El código actual **todavía no cumple la rúbrica como entrega final**. Para el avance del 27/10, la lista didáctica ofrece una demostración real y el resto debe presentarse como trabajo pendiente.

### Lectura de la rúbrica (sin asignar nota)

| Criterio | Evidencia disponible | Brecha |
|---|---|---|
| 6.1 Identifica | El plan enumera PID, prioridad, estados, capacidad y restricciones | Explicarlo con claridad en el informe y la exposición |
| 6.2 Interpreta | El diseño de lista + cola + pila responde a la consigna | Faltan diagramas completos y pseudocódigo de cada integrante |
| 6.3 Resuelve | La lista didáctica ejecuta operaciones básicas | Falta implementación y prueba integrada de cola, pila y persistencia |
| 8.1 Proactividad | Roles y cronograma definidos | Faltan commits y aportes individuales visibles |
| 8.2 Acuerdos | El plan distribuye responsabilidades | Faltan actas, tablero y registro de cumplimiento |

## 2. Explicación de 90 segundos

> «El Avance 01 proponía un ABB. Al revisar la consigna vimos que C2-1 exige exclusivamente estructuras dinámicas lineales de la Unidad 3. Por eso cambiamos a una lista enlazada para almacenar procesos, una cola de prioridad para elegir cuál se ejecuta y una pila para bloques de memoria. El PID conecta las tres estructuras; la lista guarda los datos completos. Hoy funciona una primera lista con insertar, buscar, eliminar y mostrar. El equipo está implementando la cola y la pila por separado. Después integraremos el menú, el guardado en archivos y las pruebas.»

Si la docente pregunta por el código: `struct NodoProceso` contiene un PCB y un puntero `siguiente`. `insertar` crea un nodo con `new` y lo coloca al inicio. `buscar` recorre con `while`. `eliminar` conserva `anterior` y `actual` para reconectar la lista y hace `delete`. `liberar` borra los nodos al salir.

## 3. Reparto de tareas desde esta base

1. **Mauricio:** mantener el PCB común y el menú; integrar sin copiar PCB en cola ni pila. Al eliminar un proceso, retirar primero sus entradas de cola y memoria. Probar carga/guardado cuando los tres módulos estén listos.
2. **Anthony:** revisar el ejemplo de lista, pasarlo a su propio módulo y completar búsqueda por nombre, cambio de prioridad y pruebas con lista vacía, PID repetido, primer/último nodo.
3. **Isai:** crear `NodoCola {pid, prioridad, siguiente}`. Prioridad 1 sale primero; con igual prioridad se respeta FIFO. Probar inserciones `(101,3), (102,1), (103,3)` → salen `102,101,103`.
4. **Kevin:** crear `NodoMemoria {pid, kb, siguiente}`. Probar push/pop, tope vacío, 1024 KB exactos y exceso. Para liberar todos los bloques de un PID, preservar el orden de los demás.
5. **Todos:** explicar su propia estructura en la sustentación y dejar commits verificables; la rúbrica también evalúa proactividad y respeto de acuerdos.

## 4. Demo corta para mañana

Compilar y ejecutar `version_para_equipo/main.cpp`. Registrar 101/Editor/prioridad 3 y 102/Navegador/prioridad 1; listar, buscar 101, eliminar 101 y listar. Indicar que el orden mostrado es el de la **lista** (inserción al inicio), no el de la futura cola de CPU.

## 5. Preguntas útiles a la docente

- ¿Qué operaciones de las tres estructuras deben estar funcionando ya en el avance, y cuáles pueden completarse para la entrega final?
- ¿Aprueba la cola ordenada por prioridad y la pila con capacidad simulada de 1024 KB?
- ¿Cómo prefiere que expliquemos la complejidad: Big-O más descripción de los `while`/`if`, como indica la consigna?

Registrar las respuestas en el acta y actualizar el plan antes de repartir los cambios.
