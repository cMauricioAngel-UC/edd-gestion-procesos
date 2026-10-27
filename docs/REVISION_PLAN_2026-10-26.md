# Revisión del plan — 26/10/2026

## Confirmado por la consigna

El avance de la segunda semana requiere **código parcial implementado** y una sesión de retroalimentación. La entrega final exige un ejecutable funcional, repositorio Git con commits de todos, PDF técnico, demo y preguntas individuales. Se exigen lista, cola y pila dinámicas lineales construidas desde cero; por eso el ABB del informe del 20/10 no corresponde a este C2-1.

## Estado observado hoy

| Hito previsto | Estado | Acción inmediata |
|---|---|---|
| Plan y reparto de roles | Documentado en el plan del 23/10 | Confirmar acuerdos con el grupo |
| Código de Mauricio | Esqueleto creado el 26/10; ejemplo de lista didáctica probado | Compilar en Dev-C++ y revisar la integración |
| Lista, cola y pila | No estaban en los archivos del proyecto revisados | Cada responsable debe traer su rama/código |
| Repositorio privado y commits | GitHub autenticado como `cMauricioAngel-UC`; Git local sin commits ni remoto | Crear el repositorio privado manualmente, configurar identidad local y subir aportes reales |
| Informe | El Avance 01 todavía describe un ABB | Sustituir el Cap. 1 para C2-1 y adjuntar diseño lineal |
| Actas y tablero | No localizados en la carpeta del proyecto | Registrar reunión, tareas y responsables |

## Prioridad para el martes 27/10

1. Llevar un ejecutable que compile y demostrar solo lo que realmente funcione. `version_para_equipo/main.cpp` muestra una lista operativa; el menú de integración aún no reemplaza los tres módulos.
2. Llevar el diagrama de lista → cola de prioridad → pila y los pseudocódigos de insertar, desencolar y liberar.
3. Explicar el cambio de ABB a estructuras lineales citando el requisito de la Unidad 3.
4. Preguntar a la docente si exige las tres estructuras ya operativas en el avance o acepta integración progresiva, y si el límite de memoria de 1024 KB es adecuado para la simulación.
5. Registrar por escrito la retroalimentación y asignar correcciones hasta el 31/10.

## Riesgos técnicos concretos

- La persistencia depende de que los tres métodos de recorrido de los compañeros respeten su orden documentado.
- Si se edita manualmente uno de los tres `.txt`, la carga puede fallar. En ese caso el programa termina sin sobrescribirlos para permitir su corrección.
- El `PCB.memoriaKB` debe coincidir con la suma de bloques de su PID en la pila. El código de carga aún no verifica esta consistencia.
- El guardado escribe tres archivos por separado; un corte durante la escritura puede dejar un estado parcial. Conviene resolverlo antes de la entrega final.
- El ejecutable integrado y la compatibilidad con Dev-C++ solo se podrán validar cuando existan las implementaciones de los tres módulos.
