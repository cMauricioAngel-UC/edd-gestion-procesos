# Capítulo 2. Diseño de la solución — plantilla para el equipo

## 2.1 Arquitectura

```text
main.cpp / menú
   ├── ListaProcesos: PCB completos, propiedad de los procesos
   ├── ColaPrioridad: PID + prioridad, orden de ejecución
   ├── PilaMemoria: PID + KB, bloques asignados
   └── Persistencia: procesos.txt, cola.txt, memoria.txt
```

Describir qué módulo escribió cada integrante y cómo se integran los tres. Agregar un diagrama de nodos propio de lista, cola y pila.

## 2.2 Operaciones y pseudocódigo

### Agregar proceso — Anthony

```text
leer PID, nombre y prioridad
si PID <= 0 o prioridad fuera de 1..10: rechazar
si buscarPorPid(PID) devuelve un nodo: rechazar duplicado
crear PCB con estado Listo y memoriaKB = 0
enlazar el nuevo nodo en la lista
```

### Cambiar estado — Mauricio + Anthony

```text
buscar el proceso por PID
si no existe o el estado no es válido: informar error
si pasa a Bloqueado: retirarlo de la cola
si pasa a Terminado: retirarlo de la cola y liberar sus bloques
actualizar el campo estado del PCB
```

### Encolar por prioridad — Isai

Explicar con pseudocódigo cómo se mantiene el orden de 1 a 10 y el FIFO en empates. Adjuntar un ejemplo con tres PID y prioridades 3, 1 y 3.

### Liberar memoria por PID — Kevin

Explicar con pseudocódigo el uso de la pila auxiliar y por qué se conserva el orden. Adjuntar el caso `A, B, A, C` → liberar A → `B, C`.

## 2.3 Complejidad y estructuras de control

| Operación | Tiempo previsto | Justificación por el autor |
|---|---:|---|
| Buscar PID en lista | O(n) | Recorre hasta encontrar o llegar a NULL |
| Insertar en cola ordenada | O(n) | Busca la posición de prioridad |
| Desencolar | O(1) | Cambia el puntero del frente |
| Push / pop | O(1) | Cambia el puntero del tope |
| Liberar memoria por PID | O(n) | Recorre los bloques con pila auxiliar |

Cada autor debe explicar los `if` y bucles de su implementación con un caso concreto. La consigna no exige medir milisegundos reales.

## 2.4 Diagramas de flujo pendientes

- Registrar proceso, incluyendo PID duplicado.
- Encolar y ejecutar siguiente, incluyendo cola vacía.
- Asignar y liberar memoria, incluyendo capacidad insuficiente.
- Guardar y cargar, incluyendo primera ejecución sin archivos.

## 2.5 Decisiones a validar con la docente el 27/10

- Confirmar que la simulación de 1024 KB y los estados propuestos son adecuados.
- Mostrar que ABB se reserva para el trabajo posterior de estructuras no lineales.
- Registrar cualquier cambio solicitado en el acta del equipo.
