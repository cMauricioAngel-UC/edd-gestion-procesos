CXX ?= g++
CXXFLAGS ?= -std=c++98 -Wall -Wextra -pedantic -Werror
SOURCES = src/ListaProcesos.cpp src/ColaPrioridad.cpp src/PilaMemoria.cpp src/Persistencia.cpp

.PHONY: all test clean
all: build/gestor
build/gestor: main.cpp $(SOURCES) $(wildcard include/*.h)
	mkdir -p build
	$(CXX) $(CXXFLAGS) -Iinclude main.cpp $(SOURCES) -o $@
test: all
	$(CXX) $(CXXFLAGS) -Iinclude tests/pruebas.cpp $(SOURCES) -o build/pruebas
	python3 tests/ejecutar.py
clean:
	rm -f build/gestor build/pruebas
