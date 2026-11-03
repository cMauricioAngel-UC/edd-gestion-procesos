# Evidencias de verificación

[Registro de compilación y ejecución del 3/11](pruebas-integracion-20261103.txt).

Se compiló con g++ `-std=c++98 -Wall -Wextra -pedantic -Werror` en Linux y se ejecutó `make test`. La suite recorre escenarios de lista, FIFO, capacidad exacta, exceso, liberación intercalada, persistencia con nombre/tiempo/memoria y un registro truncado. La secuencia del menú comprueba rechazo de NaN, ejecución del siguiente, liberación y reapertura.

Estas son pruebas locales de la versión integrada y corregida. El DOCX original de Bonifacio incluía resultados declarados y marcadores de capturas: no se convierten en evidencia de Dev-C++ ni en ensayos realizados. Quedan pendientes la ejecución en el equipo de exposición, ensayo conjunto y aprobación docente. Los archivos de pruebas se crean en directorios temporales; no se publican datos personales de ejecución.

[Pruebas C++](../../tests/pruebas.cpp) · [Secuencia de menú y aislamiento](../../tests/ejecutar.py).
