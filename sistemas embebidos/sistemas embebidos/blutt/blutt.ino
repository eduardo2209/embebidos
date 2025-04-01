//DECLARACIONES
#include "BluetoothSerial.h"

//DEFINICIONES
//revisar si la tarjeta tiene Bluetooth habilitado
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth no esta habilitado
#endif

//revisar si la tarjeta puede hacer comunicación serial por Bluetooth
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Comunicacion Serial Bluetooth no habilitada
#endif

int recibido;// variable para guardar el caracter recibido como entero
char recibidoChar;// el valor recibido como CHAR se guarda aqui
const char encender = 'led1'; //definir el caracter para encender el LED
const char apagar = 'led0'; //definir el caracter para apagar el LED
const char encender2 = 'led2';
const char apagar2 = 'led1';
#define LED 4
#define LED2 5 //definir el pin donde está conectado el LED

// crear objeto SerialBT que representa la conexion BT
BluetoothSerial SerialBT;

//CONFIGURACIONES
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32 Equipo 4"); // nombre del dispositivo BT
  Serial.println("Dispositivo iniciado, ahora puede conectarlo por BT");
  Serial.println("Para encender el LED, envie: led1");
  Serial.println("Para apagar el LED, envie: led0");
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
}

//BUCLE PRINCIPAL
void loop() {
  //almacenar el caracter leído de la terminal
  recibidoChar =(char)SerialBT.read(); 

  if (Serial.available()) { // si la comunicación serial está habilitada
    // leer la información que llega por el puerto serial y escribirla en el puerto serial BT
    SerialBT.write(Serial.read()); 
  }
  if (SerialBT.available()) { // si la comunicación BT serial está habilitada
    SerialBT.print("Recibido:");// mandar mensaje por BT
    SerialBT.println(recibidoChar);// escribir el caracter que se recibio     
    Serial.print ("Recibido:");// mandar mensaje por serial
    Serial.println(recibidoChar);// escribir el caracter que se recibio     

    if(recibidoChar == encender) { // si se detecta el caracter para encender el LED...
      SerialBT.println("LED ENCENDIDO:");// mandar mensaje por BT
      Serial.println("LED ENCENDIDO:");// mandar mensaje por serial
      digitalWrite(LED, HIGH);// encender el LED
        
      }
    else if(recibidoChar == apagar) { // si se detecta el caracter para apagar el LED...
      SerialBT.println("LED APAGADO:");// mandar mensaje por BT
      Serial.println("LED APAGADO:");// mandar mensaje por serial
      digitalWrite(LED, LOW);// apagar el LED
      }
    else { // si no es ninguno de los caracteres definidos
      SerialBT.println("CARACTER NO VALIDO");// mandar mensaje por BT
      Serial.println("CARACTER NO VALIDO");// mandar mensaje por serial
    }
    
  }
  delay(20);
}
