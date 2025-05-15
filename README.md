# INTRODUCCIÓN A GITHUB

## Instalación de GitHub

Git es el sistema de control de versiones que se usa para trabajar con GitHub.

🔹 Windows

Descarga Git desde la página oficial: https://git-scm.com/downloads
Ejecuta el instalador y sigue los pasos (puedes dejar las opciones por defecto).
Para verificar la instalación, abre Símbolo del sistema (cmd) y escribe:

`git --version`

🔹 Linux (Ubuntu/Debian)

Instala Git con:

~~~
sudo apt update
sudo apt install git
~~~

Verificar instalación:

`git --version`

***

## Generar repositorio

- Vale para que todo funcione os explico los pasos que tenéis que hacer:

1. Generar vuestra clave ssh en github. Esto evitará que se nos pida las credenciales cada vez que hagamos un push por ejemplo. Adjunto vídeo:
   - Linux: https://www.youtube.com/watch?v=EoLrCX1VVog.
   - Windows:https://www.youtube.com/watch?v=X40b9x9BFGo.
     - Mi recomendación es que uséis cualquier distribución de linux para trabajar más cómodo con github, no hace falta crearos una partición con una máquina virtual podéis. En cualquier caso con Windows también podéis hacerlo.
  
2. Id al directorio local dónde queráis trabajar e ingresar lo siguiente:
~~~
git init
git remote add origin git@github.com:wh0dini5/TrabajoMP24-25.git
~~~
1. Una vez hecho esto, os tendrá que salir algo parecido tal que así:

![Screenshot_20250313_155758](https://github.com/user-attachments/assets/40d94cd9-6042-4d67-9ca1-fa1af6e198ca)


4. Ya con esto deberíamos de tenerlo todo preparado para hacer código desde este directorio.
***

### COMANDOS BÁSICOS DE GITHUB

- **`git pull`**: cargamos el contenido del repositorio que hay en github en nuestro repositorio, en esencia es actualizar nuestro repositorio local con los últimos cambios que se han hecho.
- **`git add .`**: añadimos los archivos modificados al repositorio local.
- **`git commit -m "mensaje corto explicando los cambios hechos"`**: se guardan los cambios hechos en nuestro repositorio local (como hacer un snapshot del nuestro repositorio local).
- **`git push`**: subir los cambios que hemos hecho en nuestro repositorio local (nuestra máquina) al repositorio "global" (github).
- **`git checkout <rama>`**: cambiamos la rama en la que estamnos trabajando.
- **`git branch -D <nombre-rama>`**: borramos la rama con nombre-rama.
***

### WORKFLOW

Podemos seguir dos tipos de workflow diferentes:
1. El primero de ellos es que todos nosotros trabajemos en la rama **"dev"**, ya que la rama **"main"** la dejaremos para cuando tengamos el proyecto final hecho o bien cuando tengamos el proyecto avanzado nos vaya bien con muchas funcionalidades que se hayan desarrollado y queramos ponerlo en la rama **"main"** como punto de control, pero vaya lo tocaremos más bien poco.
   - **Ventajas**: Es menos tedioso y liante, sobretodo sino se está muy familiarizado con github.
   - **Desventajas**: Si queremos trabajar en paralelo, tendremos que tener cuidado a la hora de realizar los push, y puede ser un poco caótico. Más díficil a la hora de detectar errores.

![Screenshot_20250313_162437](https://github.com/user-attachments/assets/9952b860-403a-48fe-ab98-670b5b21d8bb)

2. El segundo de ellos es el que veo más óptimo para que podamos trabajar más cómodamente pero también es el más tedioso y es la creación de una rama para cada funcionalidad que queramos hacer. 

   - **Ventajas**: Esto nos permite trabajar en paralelo, y si dos de nosotros está trabajando en la rama de **"dev"**, no tengamos problemas a la hora de añadir nuevos cambios y podamos estar tranquilamente trabajando en la funcionalidad que estemos implementando en dicho momento. Mejor a la hora de detectar errores.
   - **Desventajas**: Es un poco más liante porque vamos a tener que crear ramas por cada funcionalidad y/o módulo (podemos debatirlo).

![Screenshot_20250313_162733](https://github.com/user-attachments/assets/71fa0641-eac3-4f57-a75c-ddd3443a6b39)

![Screenshot_20250313_162931](https://github.com/user-attachments/assets/f1c72243-671a-42db-a97e-8ec0e66fbe7b)


#### Alternativas a usar la terminal con github.

Si queréis que sea algo más atractivo a la hora de trabajar con github, y más gráfico para que se vea mejor las cosas (sobretodo si te pilla de nuevas). Podéis descargaros "Github Desktop". Yo no he trabajado con esto, pero es cierto que parece bastante intuitivo.

**VÍDEO OBLIGATORIO DE VER PARA ENTENDER BIEN EL FUNCIONAMIENTO DE GITHUB Y/O GITHUB DESKTOP** -> https://www.youtube.com/watch?v=8Dd7KRpKeaE


## Descomposición del proyecto

![Screenshot_20250326_173444](https://github.com/user-attachments/assets/b8263db2-d859-418c-8d16-5020b46cde2a)

