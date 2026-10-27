# Sistema de Gestión de Procesos — Estructura de Datos C2-1

Avance preparado el 26/10/2026 para mostrar código parcial el martes 27/10. La consigna pide tres estructuras dinámicas lineales **implementadas desde cero**. El ABB del Avance 01 se reserva para C2-2.

## Empieza aquí para la reunión del equipo

`version_para_equipo/main.cpp` es un ejemplo **más cercano a las prácticas de clase**: `struct`, punteros, `new`, `delete`, `while` y `switch`. La lista ya permite insertar, buscar por PID, eliminar y mostrar. Cola, pila y archivos aparecen como pendientes. Se compiló en C++98 y se probó con dos procesos, búsqueda y eliminación.

```sh
g++ -std=c++98 -Wall -Wextra -pedantic version_para_equipo/main.cpp -o avance
./avance
```

Lee `docs/GUIA_PARA_MANANA.md` antes de enseñar el código. El `main.cpp` de la raíz y `include/Persistencia.h` son **borradores de integración posterior**; tienen más abstracciones y aún no se pueden probar como sistema completo.

## Estado real

- **Mauricio:** `PCB.h`, contratos, menú e integración futura en `main.cpp`, lectura y escritura de los tres archivos en `Persistencia.h`.
- **Anthony, Isai y Kevin:** las implementaciones de lista, cola y pila siguen pendientes. Sus headers son contratos; todavía no hay métodos definidos.
- **Ejemplo didáctico:** `version_para_equipo/main.cpp` contiene una lista básica funcional para practicar y revisar con Anthony; aún no está conectada al borrador de integración.
- El ejecutable actual abre el menú y declara los módulos pendientes. **No demuestra aún la funcionalidad completa.**

## Compilar el avance de Mauricio

```sh
g++ -std=c++98 -Wall -Wextra -pedantic main.cpp -o gestor_parcial
./gestor_parcial
```

Abrir `main.cpp` en Dev-C++ y compilarlo como un solo archivo. Cuando los tres módulos tengan implementaciones, compilar con `-DED_MODULOS_LISTOS` y agregar sus `.cpp` al proyecto (o colocar las implementaciones en sus headers, según el acuerdo del equipo). Sin esta opción, el menú presenta explícitamente el estado parcial.

## Contratos del equipo

Ver `docs/GUIA_EQUIPO.md`. Cada integrante implementa su estructura en su rama con commits propios. No usar `std::list`, `std::queue` ni `std::stack`. `std::string`, flujos de archivo y flujos de texto se usan solo para entrada/salida.

## Archivos persistidos

- `procesos.txt`: `pid;nombre;prioridad;estado;tiempoEjecucion;memoriaKB`
- `cola.txt`: `pid;prioridad`, del frente al final
- `memoria.txt`: `pid;kb`, de la base al tope

Si es la primera ejecución y no existe ninguno de los tres archivos, se inicia vacío. Una carga con un archivo faltante o datos inválidos informa error. No editar manualmente los archivos durante la ejecución.

## Antes de la demostración del 27/10

1. Integrar al menos las operaciones básicas de los módulos que ya tenga el equipo.
2. Compilar en el Dev-C++ real del grupo y mostrar una secuencia corta: registrar, buscar, encolar, ejecutar y guardar/cargar.
3. Llevar el diseño actualizado y explicar a la docente el paso del ABB a estructuras lineales.
4. Registrar roles, acuerdos y aportes individuales; la consigna pide historial Git y actas.

La revisión concreta de plazos y riesgos está en `docs/REVISION_PLAN_2026-10-26.md`.
