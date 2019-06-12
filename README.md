# TP Final Taller de Programacion I: Portal

## Alumnos
* Medina Jonathan Claudio
* Penna Sebastian Ignacio

## Introducción
El presente trabajo consta de la creacion de un Portal 2D en C++, utilizando librerias de SDL, Box2D. En el cual cada jugador controla a chell. El proyecto consta de  realizar un servidor multithreading que se comunica con los clientes a traves de sockets TCP, utilizaremos un protocolo para poder mantenerse en sintonia el cliente con el servidor.
La libreria SDL es utilizada para realizar la interfaz grafica del videojuego, y Box2D es utilizado para recrear la fisica del videojuego.
Ademas utilizamos YAML para guardar configuraciones.

## Instalacion
* Para instalar SDL, en la terminal ejecutar: sudo apt install libsdl2-dev && sudo apt install libsdl2-image-dev && sudo apt install libsdl2-ttf-dev && sudo apt-get install libsdl2-mixer-dev
* Para instalar CPPUnit en la terminal, ejecutar: sudo apt-get install libcppunit-dev
* Clonar repositorio
* Y realizar un cmake . dentro de la carpeta descargada.


En caso de que el cliente no funcione, mover los *.png a donde esta el binario del client.

Por el momento el servido esta testeado contra un cliente de prueba. Para ejecutarlos se debe acceder al directorio Server y ejecutar por linea de comandos:
./server PORT (Habilita el servidor a recibir conexiones y crea una "nueva partida" por cada cliente que se conecte)
./client IP PORT (Conecta el cliente al servidor y envia y recibe una serie de mensajes propios del protocolo)

En la terminal del cliente se vera en pantalla los datos recibidos de distintos objetos en el mapa.
Para cerrar el servidor se debe presionar la letra 'q'
