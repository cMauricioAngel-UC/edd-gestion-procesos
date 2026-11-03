# Sistema de Gestión de Procesos

Proyecto de Estructura de Datos · Universidad Continental · Grupo 5 · 2026-20.

Simulador de procesos en C++98 con lista enlazada, cola de prioridad y pila de memoria implementadas con nodos propios. La versión integrada del 3/11 incorpora el paquete enviado por Isaí, la organización documental y los diagramas aportados por Bonifacio, con correcciones y pruebas registradas.

## Consultar el proyecto

- **[Informes por capítulo — vista Markdown, PDF y Word](docs/informes/README.md)**.
- **[Aportes por integrante y originales recibidos](aportes/README.md)**.
- **[Diagramas — vistas, fuentes y revisión de los aportes de Bonifacio](Diagramas/README.md)**.
- **[Pruebas ejecutadas y límites de la verificación](docs/evidencias/README.md)**.
- **[Cabeceras](include/) · [Implementaciones](src/) · [Menú principal](main.cpp)**.

## Compilar y comprobar

```sh
make
make test
./build/gestor
```

Requiere g++, make y Python 3 para el lanzador de pruebas. El ejecutable usa procesos.txt, cola.txt y memoria.txt en su directorio de trabajo. Las pruebas trabajan en directorios temporales. Para Dev-C++, incluir main.cpp y los cuatro .cpp de src, y configurar include como ruta de cabeceras; su comprobación en el equipo de exposición sigue pendiente.

## Reglas del simulador

- PID positivo y único; nombre no vacío; prioridad 1–10, con 1 como más alta; tiempo estimado finito y no negativo.
- El PCB completo vive en la lista. La cola conserva PID/prioridad y admite solo procesos Listo; empates FIFO.
- La pila almacena bloques de hasta 1024 KB acumulados. `pop` retira el tope; liberar por PID conserva el orden de los demás bloques.
- Eliminar o terminar un proceso coordina cola, memoria y PCB. Guardar/cargar verifica referencias y memoria por PID.

## Integrantes y aportes

Mauricio Angel Champi Mamani, Bonifacio Colonio Mariano Anthony, Isai Andre Hilario Toribio y Kevin Gregory Garay Leon. La composición fue confirmada por Mauricio el 3/11. Kevin aún no tiene aporte recibido, según esa confirmación. La [tabla de aportes](aportes/README.md) distingue el envío de material, el historial de Git y la autoría acreditada.

## Estado de verificación

`make test` pasó localmente con C++98: estructuras, FIFO, memoria, persistencia y menú integrado. El detalle reproducible está en el registro. El guardado de tres archivos es secuencial, no atómico. La pila usa recursión para recorrer desde la base. Faltan comprobar el entorno de exposición, el ensayo y la aprobación docente; no se declara entrega formal.

La carpeta version_para_equipo conserva el avance anterior. Para la versión integrada se usan los archivos de la raíz, include y src.
