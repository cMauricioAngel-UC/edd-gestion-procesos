# Sistema de Gestión de Procesos — Estructura de Datos

**Universidad Continental | Ingeniería de Sistemas e Informática | 2026-20**

## 1. Descripción del proyecto

Sistema de gestión de procesos desarrollado en C++ que simula algunas funciones de administración de tareas de un sistema operativo, aplicando estructuras de datos dinámicas lineales implementadas manualmente.

El proyecto busca demostrar cómo las listas enlazadas, las colas y las pilas permiten registrar procesos, organizar su ejecución según prioridades y administrar bloques de memoria simulada.

El desarrollo se realiza de manera progresiva, comenzando con una aplicación de consola y avanzando hacia una visualización más completa de los procesos.

## 2. Objetivo general

Desarrollar un simulador de gestión de procesos en C++ utilizando estructuras de datos dinámicas lineales, que permita registrar, buscar, modificar y eliminar procesos, planificar su ejecución según prioridades y gestionar memoria simulada.

## 3. Objetivos específicos

- Implementar una lista enlazada para administrar los procesos registrados.
- Desarrollar una cola de prioridad para simular la planificación de CPU.
- Implementar una pila enlazada para administrar bloques de memoria.
- Permitir la consulta y modificación de los datos de cada proceso.
- Guardar y recuperar información mediante archivos de texto.
- Incorporar una interfaz que facilite la visualización del estado del sistema.
- Validar el funcionamiento mediante pruebas de inserción, búsqueda, eliminación y gestión de memoria.

## 4. Estructuras de datos

**Lista enlazada — ListaProcesos**

Almacena los procesos mediante nodos dinámicos que contienen un PCB y un puntero al siguiente elemento. Permite registrar, buscar, modificar y eliminar procesos.

**Cola de prioridad — ColaPrioridad**

Organiza los procesos pendientes según su prioridad. El valor numérico menor representa mayor prioridad y, en caso de empate, se conserva el orden de llegada.

**Pila enlazada — PilaMemoria**

Simula la asignación y liberación de bloques de memoria, aplicando operaciones de inserción y extracción sobre el tope.

**PCB — Bloque de Control de Proceso**

Representa la información de cada proceso: PID, nombre, prioridad, estado, tiempo de ejecución y memoria asignada.

## 5. Estado actual del desarrollo

**Revisión: 27/10/2026**

| Componente                     | Estado                                             |
| ------------------------------ | -------------------------------------------------- |
| Estructura PCB compartida      | Definida                                           |
| Lista enlazada didáctica       | Operaciones básicas implementadas                  |
| Búsqueda y eliminación por PID | Implementadas en versión didáctica                 |
| Cola de prioridad              | Interfaz definida; implementación pendiente        |
| Pila de memoria                | Interfaz definida; implementación pendiente        |
| Menú principal                 | Estructura de integración preparada                |
| Persistencia de archivos       | Código preparado; integración y pruebas pendientes |
| Interfaz de monitoreo simulado | Propuesta futura                                   |
| Lectura de procesos reales     | Ampliación opcional no implementada                |

El programa todavía no constituye una versión final. Las funcionalidades pendientes no deben considerarse implementadas hasta que se integren y validen.

## 6. Organización del repositorio

- `include/PCB.h`: definición compartida del proceso.
- `include/ListaProcesos.h`: interfaz de la lista enlazada.
- `include/ColaPrioridad.h`: interfaz de la cola de prioridad.
- `include/PilaMemoria.h`: interfaz de la pila de memoria.
- `include/Persistencia.h`: funciones previstas para guardar y cargar archivos.
- `main.cpp`: menú principal y estructura de integración.
- `version_para_equipo/main.cpp`: implementación didáctica parcial con operaciones básicas de lista.
- `README.md`: descripción del proyecto, estado actual y planificación.

## 7. Compilación de la versión didáctica

El proyecto utiliza C++98 como base de compatibilidad con Dev-C++.

Comando para compilar el ejemplo didáctico:

`g++ -std=c++98 -Wall -Wextra -pedantic version_para_equipo/main.cpp -o avance`

Ejecución en Linux:

`./avance`

La aplicación principal necesitará integrar las implementaciones de lista, cola y pila antes de habilitar todas sus funcionalidades.

## 8. Planificación de desarrollo

### Semana 1 — Planificación y análisis

- Identificación del problema.
- Definición inicial de requerimientos.
- Selección y justificación de estructuras de datos.
- Elaboración del Capítulo 1.
- Organización del equipo.

El diseño original consideró un Árbol Binario de Búsqueda. Posteriormente se decidió orientar C2-1 hacia lista, cola y pila para cumplir con los requisitos de la Unidad 3.

### Semana 2 — Diseño e implementación parcial

- Actualización de los capítulos 1 y 2.
- Definición de las interfaces y estructuras compartidas.
- Implementación inicial de la lista enlazada.
- Desarrollo paralelo de cola y pila.
- Preparación de pseudocódigos y diagramas.
- Presentación del avance parcial y registro de observaciones del docente.

### Semana 3 — Integración y validación

- Completar lista, cola y pila.
- Integrar los módulos con el menú.
- Implementar y probar persistencia.
- Verificar entradas inválidas y casos especiales.
- Preparar pruebas, capturas y manual de usuario.
- Consolidar los capítulos finales y evidencias de trabajo en equipo.

## 9. Evolución futura del sistema

Una vez que las funciones obligatorias estén operativas, se propone mejorar la interfaz del simulador.

**Fase A — Visualización general**

Presentar los procesos registrados en una tabla con PID, nombre, prioridad, estado y memoria asignada.

**Fase B — Simulación automática**

Incorporar actualizaciones periódicas de la visualización y una simulación de cambios de estado y ejecución de procesos, conservando la cola de prioridad y las estructuras implementadas.

**Fase C — Investigación de monitoreo real (opcional)**

Evaluar la posibilidad de consultar información de procesos reales de Windows o Linux, inicialmente en modo de solo lectura.

Esta ampliación dependerá del tiempo disponible, la compatibilidad del entorno y la aprobación del equipo y docente. No sustituye los objetivos obligatorios de la evaluación.

## 10. Integrantes y responsabilidades propuestas

| Integrante | Responsabilidad                                      |
| ---------- | ---------------------------------------------------- |
| Mauricio   | Integración, menú, PCB, persistencia y documentación |
| Anthony    | Lista enlazada de procesos                           |
| Isai       | Cola de prioridad                                    |
| Kevin      | Pila de memoria                                      |

Cada integrante debe implementar, probar, documentar y explicar su módulo, registrando sus contribuciones mediante commits.

## 11. Alcance y limitaciones

El sistema está diseñado como una simulación educativa. Actualmente no administra los procesos reales del dispositivo ni modifica la planificación del sistema operativo.

La prioridad del proyecto es demostrar la implementación correcta de estructuras dinámicas lineales, su interacción y la resolución de los requerimientos establecidos.

## 12. Documentación

Los borradores de planificación, diseño y guías del equipo se encuentran en [Google Drive](https://drive.google.com/drive/folders/1dHN9C6gltpdiZE9SI_pRcXBnIdCkt8Dy).

El historial de Git permite revisar los avances y contribuciones realizados durante el desarrollo.
