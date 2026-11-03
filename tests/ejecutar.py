from pathlib import Path
import tempfile,subprocess
root=Path(__file__).resolve().parents[1]
with tempfile.TemporaryDirectory() as t:
 r=subprocess.run([str(root/'build/pruebas')],cwd=t,text=True,capture_output=True);print(r.stdout,end='');assert r.returncode==0,r.stderr
with tempfile.TemporaryDirectory() as t:
 # Register, reject NaN, enqueue, assign memory, execute, persist, then reload.
 entries=['1','1','101','Editor','3','3.5','1','102','Navegador','1','2','1','103','Invalido','2','nan','0','2','1','101','1','102','2','0','3','1','102','300','0','2','3','0','0']
 r=subprocess.run([str(root/'build/gestor')],input='\n'.join(entries)+'\n',cwd=t,text=True,capture_output=True,timeout=10)
 assert r.returncode==0 and 'Ejecutando PID 102' in r.stdout and 'Memoria liberada: 300 KB' in r.stdout
 assert 'Valor invalido (numero >= 0)' in r.stdout
 r2=subprocess.run([str(root/'build/gestor')],input='1\n2\n0\n0\n',cwd=t,text=True,capture_output=True,timeout=10)
 assert 'Navegador | prio 1 | Terminado' in r2.stdout and 'mem=0 KB' in r2.stdout
 print('OK: menu integrado, rechazo NaN, ejecucion, liberacion y reapertura.')
 print('Salida de demostracion:')
 for line in (r.stdout+r2.stdout).splitlines():
  if any(s in line for s in ['Proceso registrado','Valor invalido (numero','Ejecutando PID','Termino.','PID 101 |','PID 102 |']):print(line)
