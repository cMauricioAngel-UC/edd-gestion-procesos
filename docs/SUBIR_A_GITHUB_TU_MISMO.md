# Subir el avance a GitHub tú mismo

La sesión de GitHub CLI quedó iniciada como `cMauricioAngel-UC`. El repositorio local ya existe en `~/Proyectos/edd-gestion-procesos/`, pero aún no tiene commits ni remoto.

## 1. Crear el repositorio en la página que está abierta

1. Propietario: `cMauricioAngel-UC`.
2. Nombre: `edd-gestion-procesos`.
3. Visibilidad: **Private**, según el plan del equipo.
4. Deja sin marcar “Add README”, `.gitignore` y licencia, porque los dos primeros ya están en tu carpeta local.
5. Pulsa **Create repository** y copia la URL HTTPS que GitHub muestre. No la inventes; usa la que aparezca en tu cuenta.

## 2. Hacer tu primer commit y subirlo

Abre una terminal en `~/Proyectos/edd-gestion-procesos/` y ejecuta cada línea tras revisarla:

```sh
git status
git config --local user.name "Mauricio Angel Champi Mamani"
git config --local user.email "TU_CORREO_DE_GITHUB"
git add .
git commit -m "avance C2-1: base y lista didactica"
git remote add origin URL_HTTPS_COPIADA_DE_GITHUB
git push -u origin main
```

Sustituye `TU_CORREO_DE_GITHUB` por el correo que quieras asociar a tus commits, y `URL_HTTPS_COPIADA_DE_GITHUB` por la URL real. La carpeta `build/` y los datos `.txt` están excluidos por `.gitignore`.

## 3. Incorporar al equipo

Invita a Anthony, Isai y Kevin como colaboradores cuando tengas sus usuarios de GitHub. Que cada uno implemente y explique su módulo en una rama propia, haga commits desde su cuenta y abra un Pull Request. Eso deja evidencia de trabajo en equipo para la rúbrica.

No subas el ZIP de entrega como único archivo del repositorio: sube los archivos fuente individuales para que se puedan revisar los cambios y aportes.
