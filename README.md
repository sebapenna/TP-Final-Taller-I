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

./server PORT (Habilita el servidor a recibir conexiones y crea una "nueva partida" por cada cliente que se conecte)

./client (Conecta el cliente al servidor y envia y recibe una serie de mensajes propios del protocolo)

En la terminal del cliente se vera en pantalla los datos recibidos de distintos objetos en el mapa.
Para cerrar el servidor se debe presionar la letra 'q'
## Controles

* Para salir del juego se puede presionar la cruz de la ventana o a su vez la q.
* Click izquierdo para poner portal azul sobre una superficie posible.
* Click derecho para poner portal naranja sobre una superficie posible.
* Click del medio para la PinTool.
* W para saltar
* D para moverse a la derecha
* A para moverse a la izquierda
* O para cometer un suicidio
* K para matar a la chell restant
* E para levantar una roca
* F para soltar una roca
* R para deshacer los portales puestos por el jugador.


Manual de Proyecto: https://docs.google.com/document/d/1yPug7UHTOMCyLKyBQwqXsFqV-qyH_LjJhlikPEDWw88/edit?ts=5d10f6be#

Manual de Usuario: https://docs.google.com/document/d/1G6lf7TsFlmXrUqH2_vvfhIsHxhLbivZl49jD5aZUoQI/edit?ts=5d105838

Documentacion Tecnica: https://docs.google.com/document/d/1cbQB0FRhWOrpLvDB_RfdPb2K7EfsNJ5cLFd7dYTcm5U/edit?ts=5d116ebc#
