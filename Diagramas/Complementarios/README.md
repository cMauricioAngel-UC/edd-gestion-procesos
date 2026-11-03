# Flujos complementarios cotejados

Versión integrada del 3/11/2026. Cada pie distingue la operación local y la coordinación del menú.

[Editable diagrams.net](../Flujos_complementarios.drawio) · [Índice de diagramas](../README.md)

## Búsqueda por PID en la lista

NULL indica fin de lista o búsqueda sin resultado. El ciclo recorre nodos, no posiciones de un arreglo.

![Búsqueda por PID en la lista](02_buscar.png)

[SVG editable](02_buscar.svg)

## Validación del encolamiento

La integración permite encolar solo procesos Listo. El método encolar rechaza PID/prioridad inválidos y PID repetido; el recorrido con act está en el flujo siguiente.

![Validación del encolamiento](04_encolar_validacion.png)

[SVG editable](04_encolar_validacion.svg)

## Inserción ordenada con act

El método encolar retorna void y usa cantidad_. La integración valida antes el PID y el estado Listo. Avanzar con <= conserva FIFO entre iguales.

![Inserción ordenada con act](05_encolar_act.png)

[SVG editable](05_encolar_act.svg)

## Asignación y enlaces del tope

Se admite el total exacto de 1024 KB. Actualizar cada contador una sola vez; identificar qué actualización pertenece a la pila y cuál a la coordinación con el PCB.

![Asignación y enlaces del tope](asignar.png)

[SVG editable](asignar.svg)

## Liberación por PID y pila auxiliar

Al borrar un nodo coincidente, acumular sus KB, restar usadosKB_ y decrementar cantidad_. Los demás nodos se transfieren sin copiarlos. Continuar con restauración.

![Liberación por PID y pila auxiliar](08_liberar_filtrar.png)

[SVG editable](08_liberar_filtrar.svg)

## Restauración y contadores

liberarPorPid retorna los KB liberados; los contadores internos ya se actualizaron durante el filtrado. El menú pone memoriaKB en cero. No restar dos veces usadosKB_. La doble inversión conserva el orden.

![Restauración y contadores](09_liberar_restaurar.png)

[SVG editable](09_liberar_restaurar.svg)

## Liberación del tope

Pop es LIFO. La búsqueda del PCB pertenece a la coordinación y cuesta O(n), aunque extraer el nodo de la pila cuesta O(1).

![Liberación del tope](10_pop.png)

[SVG editable](10_pop.svg)

## Modificación de prioridad

Solicitar la misma prioridad conserva la posición. Una prioridad diferente cuenta como una nueva llegada a ese grupo de prioridad.

![Modificación de prioridad](11_prioridad.png)

[SVG editable](11_prioridad.svg)
