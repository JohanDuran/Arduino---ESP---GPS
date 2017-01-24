1. Crear un blink con los tx y rx conectados a transmisión y recepción.
2. Buscar la frecuencia de baudios a las que se recibe un ok dado el comando AT.
3. Una vez encontrado utilizar AT+UART= "X",8,1,0,0 cambiar X por 9600 (para este caso). 
4. Cambiar los cables de TX RX a los pines pertenecientes al puerto serial virtual.
5. Utilizar la misma frecuencia de baudios en los dos Seriales.
6. Continuar configuración.