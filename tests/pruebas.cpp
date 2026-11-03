#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include "ListaProcesos.h"
#include "ColaPrioridad.h"
#include "PilaMemoria.h"
#include "Persistencia.h"
int main() {
 ListaProcesos l; ColaPrioridad c; PilaMemoria m; int pid,pr,kb; std::string err;
 assert(!c.desencolar(pid,pr)); assert(!m.pop(pid,kb));
 PCB a(101,"Editor con espacios",3,3.5f), b(102,"Navegador",1,2), d(103,"Terminal",3,4);
 assert(l.insertar(a)); assert(l.insertar(b)); assert(l.insertar(d)); assert(!l.insertar(a));
 assert(l.buscarPorNombre("Editor con espacios")->pid==101);
 PCB bad(104,"Invalido",5,std::numeric_limits<float>::quiet_NaN()); assert(!l.insertar(bad));
 c.encolar(101,3); c.encolar(102,1); c.encolar(103,3); c.encolar(101,1); c.encolar(104,11);
 assert(c.tamanio()==3); assert(c.desencolar(pid,pr)&&pid==102); assert(c.desencolar(pid,pr)&&pid==101); assert(c.desencolar(pid,pr)&&pid==103);
 c.encolar(101,3);c.encolar(102,1);c.encolar(103,3);assert(c.eliminarPid(101));assert(c.desencolar(pid,pr)&&pid==102);assert(c.desencolar(pid,pr)&&pid==103);
 assert(m.push(101,400));assert(m.push(102,300));assert(m.push(101,324));assert(!m.push(103,1));assert(m.liberarPorPid(101)==724);assert(m.usadosKB()==300);assert(m.pop(pid,kb)&&pid==102&&kb==300);
 assert(m.push(101,100));assert(m.push(102,200));assert(m.push(101,50));assert(m.push(103,75));assert(m.liberarPorPid(101)==150);assert(m.pop(pid,kb)&&pid==103);assert(m.pop(pid,kb)&&pid==102);
 assert(m.push(101,256));l.buscarPorPid(101)->memoriaKB=256;c.encolar(102,1);c.encolar(101,3);c.encolar(103,3);
 assert(guardarTodo(l,c,m,err)); ListaProcesos l2;ColaPrioridad c2;PilaMemoria m2;assert(cargarTodo(l2,c2,m2,err));
 assert(l2.buscarPorPid(101)->tiempoEjecucion==3.5f);assert(l2.buscarPorPid(101)->nombre=="Editor con espacios");assert(l2.buscarPorPid(101)->memoriaKB==256);assert(m2.totalPorPid(101)==256);
 assert(c2.desencolar(pid,pr)&&pid==102);assert(c2.desencolar(pid,pr)&&pid==101);assert(c2.desencolar(pid,pr)&&pid==103);
 {std::ofstream f("cola.txt");f<<"102";}assert(!cargarTodo(l2,c2,m2,err));assert(l2.vacia()&&c2.vacia()&&m2.vacia());
 assert(l.eliminar(102));assert(l.eliminar(103));assert(l.eliminar(101));assert(l.vacia());assert(l.insertar(a));
 std::cout<<"OK: lista, cola/FIFO, capacidad, liberacion intercalada, persistencia y registro truncado.\n";
}
