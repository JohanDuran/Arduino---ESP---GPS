/*
   El ESP8266 debe estar pre-configurado a 115200 Baudios
   Conectar el ESP8266 de acuerdo al diagrama UNO_ESP_JSON
*/

#include <SoftwareSerial.h>
#include <TinyGPS.h>

//GPS module
TinyGPS gps;
SoftwareSerial gps(5, 4);

//para el sensor ultrasonico
SoftwareSerial esp(3, 2); //Pines: RX conectado a D3, TX conectado a D2

//
//#define DEBUG_ESP8266 //Comentar si no se quiere imprimir la respuesta del ESP8266
#define ESP8266_OK //Confirmar si el comando AT fue recibido


#define SSID   "AP-12805"
#define PASS   "nadieselasabe"

String server = "AT+CIPSTART=\"TCP\",\"192.168.0.101\",8081";  //Direccion del servidor al que se envían los datos
String JSON = "POST /Proyectos/ArduinoPHPPost/phpPost/test.php HTTP/1.1\r\nHost: 192.168.0.101:8081\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length: "; //Header post/JSON
String trama; // Almacena el comando AT que envía el largo del dato a enviarse al servidor

//-----------------------------------------------------------------------------------------------------------------
void setup() {

  Serial.begin(115200);             // Inicializacion del Monitor Serial a 115200
  esp.begin(38400);           // Inicializacion  puerto serial virtual para el esp
  gps.begin(9600);            //Inicializacion del módulo gps 
  Serial.print("Simple TinyGPS library v. "); Serial.println(TinyGPS::library_version());
  Serial.println();     

  
  Serial.println("Manejo Modulo ESP8266 con Arduino UNO");// Mensaje de inicialización
  
  //*********************Pruebas iniciales**************************
  Serial.println("AT");
  SendCmd("AT", 60);
  Serial.println("ATE1");
  SendCmd("ATE1", 60); //ATE1: Habilita replica/echo del cmd enviado
  Serial.println("ATE0");
  SendCmd("ATE0",60); //ATE0: Deshabilita replica/echo del cmd enviado
  Serial.println("AT+UART");
  SendCmd("AT+UART=38400,8,1,0,0", 60);

  conectarWIFI();                 // Función para conectar el módulo ESP8266 a la red WiFi selecccionada
  delay(20);
}

void loop() {
  //*****************Conexión con el servidor*************************
  String datos = "{\"id1\":\"12\"}";
  String temp = JSON;
  JSON = JSON + String(datos.length()) + "\r\n\r\n" + datos;
  Serial.println(JSON);
  trama = "AT+CIPSEND=" + String(JSON.length());
  Serial.println(trama);
  SendCmd(server, 60);
  esp.println(trama);
  delay(100);
  esp.println(JSON);
  JSON = temp;
  resetESP();
  delay(5000);
}


//****************************************** FUNCIONES****************************************************************//

void conectarWIFI() {       // Función que permite conectarse al servidor específicado en el string server
  Serial.println("AT+CWMODE");
  SendCmd("AT+CWMODE=3", 60);
  Serial.println("AP");
  String AP = "AT+CWJAP=\""; AP += SSID; AP += "\",\""; AP += PASS; AP += "\""; // Comando AT para la conexión WiFi seleccionada con el SSID y PASS
  SendCmd(AP, 60);
  Serial.println("AT");
  SendCmd("AT", 60);
}

void resetESP() {
  Serial.println("RST");
  esp.println("AT+RST");        // Deshabilita el echo de los comandos enviados
  delay(20);
  conectarWIFI();                 // Función para conectar el módulo ESP8266 a la red WiFi selecccionada
}

void leer() {
  while (esp.available()) {
    String recibido = "";
    if (esp.available()) {
      recibido += (char)esp.read();
    }
    Serial.print(recibido);
  }
}

bool findOK() {                     //Función que permite verificar el resultado "OK" del comando AT
  if (esp.find("OK"))         // Si se localiza OK en la respuesta del ESP8266
  {
    Serial.println("OK");
    return true;                    // Devuelve "True"
  }
  else
  {
    //Serial.println("!OK");
    return false;                   // Retorna "False"
  }
}

void SendCmd (String ATcmd, int Tespera) {

#ifdef DEBUG_ESP8266
  esp.println(ATcmd);
  delay(10); //Tiempo a esperar para abrir el puerto esp
  leer();
#endif

#ifdef ESP8266_OK
  while (!findOK()) {
    esp.println(ATcmd);
    delay(Tespera); //Tiempo a esperar para abrir el puerto esp
  }
#endif
  delay(60);
}

