# TP Final Taller de Programacion I: Portal

## Alumnos
* Medina Jonathan Claudio
* Penna Sebastian Ignacio

## Introducción
El presente trabajo consta de la creacion de un Portal 2D en C++, utilizando librerias de SDL, Box2D. En el cual cada jugador controla a chell. El proyecto consta de  realizar un servidor multithreading que se comunica con los clientes a traves de sockets TCP, utilizaremos un protocolo para poder mantenerse en sintonia el cliente con el servidor.
La libreria SDL es utilizada para realizar la interfaz grafica del videojuego, y Box2D es utilizado para recrear la fisica del videojuego.
Ademas utilizamos YAML para guardar configuraciones.

## Instalacion
* Para instalar CMake, en la terminal ejecutar: sudo apt-get install cmake
* Para instalar SDL, en la terminal ejecutar: sudo apt install libsdl2-dev && sudo apt install libsdl2-image-dev && sudo apt install libsdl2-ttf-dev && sudo apt-get install libsdl2-mixer-dev
* Para instalar CPPUnit en la terminal, ejecutar: sudo apt-get install libcppunit-dev
* Para instalar QT, en la terminal ejecutar: sudo apt-get install qt5-default
* Clonar repositorio
* Y realizar un cmake . dentro de la carpeta descargada.


En caso de que el cliente no funcione, mover los *.png a donde esta el binario del client.

Por el momento el servido esta testeado contra un cliente de prueba. Para ejecutarlos se debe acceder al directorio Server y ejecutar por linea de comandos:
## Forma de Uso
### Servidor
    Para ejecutar el servidor se debe ejecutar desde la terminal el comando:
./portal_server PORT
    dónde PORT será el puerto donde se realizará la conexión del servidor esperando conexiones de los distintos clientes.
    Una vez iniciado el servidor el mismo está disponible a distintas conexiones, ya sea para crear nuevas partidas (ya que se trata de un servidor multi-partidas) así como la inclusión de nuevos jugadores a partidas ya existentes (juego multi-jugador). En la terminal se verán una serie de mensajes cuando se detecten nuevas conexiones, comiencen o terminen partidas o se cierren distintos sockets ante el posible abandono de jugadores tanto durante como previo al comienzo de una partida.
    
    Es posible cerrar el servidor en medio de la ejecución del mismo, asegurando su correcto cierre sin problemas de funcionamiento presionando la tecla ‘q’, seguida de ENTER, en la terminal donde se está ejecutando el mismo.

### Cliente
    Para ejecutar el cliente se debe abrir una terminal y ejecutar:
./portal_client
    Una vez ejecutado el comando se abrirá una ventana donde el jugador podrá seleccionar tanto el puerto e ip a los cuales conectarse, si quiere crear una nueva partida o unirse a una existente y por último seleccionar las distintas opciones que brindará el servidor en base a la decisión tomada. En ambos casos una vez creado o unido a una partida se podrán ver en pantalla distintos mensajes, notificando cuando ha ocurrido algo, ya sea que un jugador se vaya de la partida, o un jugador ingresó al juego. O cuando el owner del juego se ha ido del juego.


## Controles
Ya iniciada la partida el usuario verá a su Chell (personaje que utilizará en el juego) centrada en la pantalla. Desde éste momento el jugador tendrá como objetivo llegar a la Cake (punto final de la partida), ubicada en algún lugar del mapa. Para ello podrá realizar distintas acciones a través de las siguientes teclas:
A: moverse a izquierda;
D: moverse a derecha;
W: saltar (podrá saltar y moverse una vez en el aire);
E: cargar una roca;
F: soltar roca que está cargando;
O: suicidarse, continuará viendo la partida, fijada la cámara donde murió;
K: matar a otra Chell;
R: borra los portales creados por el jugador;
Q: cierra la partida;
Click izquierdo: dispara el portal azul;
Click derecho: dispara el portal naranja;
Click del medio (rueda del mouse): dispara la pin tool;



Manual de Proyecto: https://docs.google.com/document/d/1yPug7UHTOMCyLKyBQwqXsFqV-qyH_LjJhlikPEDWw88/edit?ts=5d10f6be#

Manual de Usuario: https://docs.google.com/document/d/1G6lf7TsFlmXrUqH2_vvfhIsHxhLbivZl49jD5aZUoQI/edit?ts=5d105838

Documentacion Tecnica: https://docs.google.com/document/d/1cbQB0FRhWOrpLvDB_RfdPb2K7EfsNJ5cLFd7dYTcm5U/edit?ts=5d116ebc#
