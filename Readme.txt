1. Crear un blink con los tx y rx conectados a transmisión y recepción.
2. Buscar la frecuencia de baudios a las que se recibe un ok dado el comando AT.
3. Una vez encontrado utilizar AT+UART= "X",8,1,0,0 cambiar X por 38400 (para este caso). 
4. Una vez hecho el cambio de frecuencia cargar el código con el serial a 115200 y el softSerial a 38400, dado que uno es más veloz que otro. 
5. Cambiar los cables de TX RX a los pines pertenecientes al puerto serial virtual.
6. Continuar configuración.

7. Para descargar libreria esp ir a archivo, preferencias y pegar en agregar tarjetas el link:	
	http://arduino.esp8266.com/package_esp8266com_index.json
8. Reiniciar arduino.
9. Dirigirse a herramientas, gestor de tarjetas y buscar esp8266 de esp community. Instalar.
