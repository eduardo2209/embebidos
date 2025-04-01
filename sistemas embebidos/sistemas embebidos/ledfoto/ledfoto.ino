// Definición de pines para el display de 7 segmentos
const int segmentPins[] = {13, 12, 14, 27, 26, 25, 33}; // a, b, c, d, e, f, g
const int photoResistorPin = 34; // Pin ADC del fotorresistor

// Definición de los números del 0 al 4 en un display de 7 segmentos (cátodo común)
const byte numbers[5][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}  // 4
};

void setup() {
  // Configurar los pines de los segmentos como salidas
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  // Iniciar comunicación serial para depuración
  Serial.begin(115200);
  Serial.println("Iniciando sistema con fotorresistor...");
}

void loop() {
  // Leer el valor del fotorresistor
  int sensorValue = analogRead(photoResistorPin);

  // Mapear el valor del fotorresistor a un rango de 0 a 4
  int displayNum = map(sensorValue, 0, 4095, 0, 4);

  // Mostrar el número en el display
  displayNumber(displayNum);

  // Imprimir el valor para depuración
  Serial.print("Valor del fotorresistor: ");
  Serial.print(sensorValue);
  Serial.print(" -> Mostrando número: ");
  Serial.println(displayNum);

  // Esperar un momento antes de leer de nuevo
  delay(500);
}

// Función para mostrar un número en el display
void displayNumber(int num) {
  // Encender los segmentos correspondientes al número
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], numbers[num][i]);
  }
}