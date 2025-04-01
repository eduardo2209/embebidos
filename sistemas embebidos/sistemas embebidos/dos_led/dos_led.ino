#include "BluetoothSerial.h"

// Verificación de Bluetooth habilitado
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth no está habilitado
#endif

// Verificación de comunicación serial Bluetooth
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Comunicación Serial Bluetooth no habilitada
#endif

// Definición de pines
#define LED1_PIN 19      // LED 1
#define LED2_PIN 4      // LED 2
#define BUTTON1_PIN 5   // Botón para LED 1
#define BUTTON2_PIN 18  // Botón para LED 2

// Comandos Bluetooth
const char CMD_LED1_ON = 'A';
const char CMD_LED1_OFF = 'a';
const char CMD_LED2_ON = 'B';
const char CMD_LED2_OFF = 'b';
const char CMD_STATUS = '?';

BluetoothSerial SerialBT;

void setup() {
  // Inicialización de comunicación serial
  Serial.begin(115200);
  
  // Configuración de pines
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  
  // Inicialización Bluetooth
  SerialBT.begin("ESP32 Control Dual");
  Serial.println("Dispositivo iniciado. Listo para conexión Bluetooth");
  printInstructions();
  
  // Estado inicial
  updateLEDs();
}

void loop() {
  // Control por Bluetooth
  handleBluetooth();
  
  // Control por botones físicos
  handleButtons();
  
  delay(20);
}

void handleBluetooth() {
  if (SerialBT.available()) {
    char receivedChar = (char)SerialBT.read();
    Serial.print("Comando BT recibido: ");
    Serial.println(receivedChar);
    
    switch(receivedChar) {
      case CMD_LED1_ON:
        digitalWrite(LED1_PIN, HIGH);
        sendStatus();
        break;
      case CMD_LED1_OFF:
        digitalWrite(LED1_PIN, LOW);
        sendStatus();
        break;
      case CMD_LED2_ON:
        digitalWrite(LED2_PIN, HIGH);
        sendStatus();
        break;
      case CMD_LED2_OFF:
        digitalWrite(LED2_PIN, LOW);
        sendStatus();
        break;
      case CMD_STATUS:
        sendStatus();
        break;
      default:
        SerialBT.println("Comando no válido");
        printInstructions();
    }
  }
}

void handleButtons() {
  // Control de botón para LED1
  if (digitalRead(BUTTON1_PIN) == LOW) {
    delay(50); // Anti-rebote
    digitalWrite(LED1_PIN, !digitalRead(LED1_PIN));
    sendStatus();
    while(digitalRead(BUTTON1_PIN) == LOW); // Espera a soltar el botón
  }
  
  // Control de botón para LED2
  if (digitalRead(BUTTON2_PIN) == LOW) {
    delay(50); // Anti-rebote
    digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));
    sendStatus();
    while(digitalRead(BUTTON2_PIN) == LOW); // Espera a soltar el botón
  }
}

void updateLEDs() {
  // Actualiza el estado físico de los LEDs según sus pines
  // (Función para posibles expansiones)
}

void sendStatus() {
  String status = "Estado: LED1=";
  status += digitalRead(LED1_PIN) ? "ON" : "OFF";
  status += ", LED2=";
  status += digitalRead(LED2_PIN) ? "ON" : "OFF";
  
  SerialBT.println(status);
  Serial.println(status);
}

void printInstructions() {
  String instructions = "Comandos disponibles:\n";
  instructions += "'A' - Encender LED1\n";
  instructions += "'a' - Apagar LED1\n";
  instructions += "'B' - Encender LED2\n";
  instructions += "'b' - Apagar LED2\n";
  instructions += "'?' - Consultar estado";
  
  SerialBT.println(instructions);
  Serial.println(instructions);
}