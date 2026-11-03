# Aportes recibidos y procedencia

Registro del 3/11/2026, America/Lima. Los cuatro integrantes vuelven a formar el equipo según Mauricio. Kevin figura como integrante; Mauricio indica que aún no ha aportado material. El registro identifica evidencia recibida y no asigna autoría por el solo nombre del módulo.

| Persona | Material acreditado | Incorporación |
|---|---|---|
| Bonifacio Colonio Mariano Anthony | [Informe original](bonifacio/2026-11-03/Informe_Final_Grupo_5.docx); [Diagramas](../Diagramas/) publicados por MarianoBoni33 | Se aprovecharon estructura de cuatro capítulos, tablas, pseudocódigo, manual y figuras. Se corrigieron el título ABB, firmas/relaciones, complejidad, estados de prueba y limitaciones de persistencia. |
| Isai Andre Hilario Toribio | [ZIP original enviado](isai/2026-11-03/trabajo-original.zip) | Incluye diez archivos .h/.cpp; se normalizaron los nombres sin ` (1)` y se integraron en include, src y main.cpp. Añade implementaciones y un menú funcional respecto de la base anterior. |
| Mauricio Angel Champi Mamani | Base previa del repositorio y solicitud de integración | La integración, correcciones, documentación y pruebas se publican bajo su cuenta con asistencia de Codex. No se presentan como commits personales de los otros integrantes. |
| Kevin Gregory Garay Leon | Sin aporte recibido a la fecha, según Mauricio | Nombre en las portadas; sin módulo o prueba atribuidos. |

Las imágenes del DOCX que ya estaban en Diagramas se reconocen por su huella y se referencian; no se cuentan dos veces. El DOCX y el ZIP originales se conservan sin modificaciones y sus huellas están en [manifest.json](manifest.json).

## Límites de atribución

La cabecera recibida de ColaPrioridad dice que es una referencia de integración y que debe reemplazarse por la implementación de Isaí. Se conserva ese comentario: el ZIP acredita qué material envió Isaí según Mauricio, pero no prueba autoría exclusiva de los diez archivos ni resuelve por sí solo la procedencia del contenido. El informe original asignaba módulos a integrantes y contenía campos de actas vacíos; esas asignaciones no se convirtieron en aportes acreditados.

Los originales no se usan como instrucciones para declarar pruebas completas. Los resultados reproducidos están en [el registro de ejecución](../docs/evidencias/pruebas-integracion-20261103.txt).

## Cambios respecto del paquete recibido

- PID y prioridad inválidos rechazados también por las operaciones locales de cola/pila.
- Tiempo NaN/no finito rechazado al registrar e insertar.
- Lectura de cola y memoria por filas completas: rechaza registros truncados y campos sobrantes.
- Carga de bloques para procesos terminados rechazada.
- Archivos reorganizados y compilación reproducible mediante Makefile.
- Pruebas automáticas de estructuras, persistencia e integración añadidas.

El guardado sigue reemplazando tres archivos por separado; no se atribuye atomicidad ni recuperación garantizada ante interrupciones. No se ha verificado Dev-C++ ni el ensayo de exposición en esta revisión.
