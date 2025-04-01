const int segmentPins[7] = {2, 4, 5, 12, 13, 14, 15}; 
const int transistor1 = 25;
const int transistor2 = 26;
const int transistor3 = 22;
const int transistor4 = 23;

// Muestra del 0 a 9
const byte numbers[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

int number = 0; // Número inicial 
unsigned long lastUpdateTime = 0; // Última actualización del número
const int updateInterval = 500; // Intervalo de actualización

void setup() {
  // Activación de pines
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW);
  }
  // Activación de transistores
  pinMode(transistor1, OUTPUT);
  pinMode(transistor2, OUTPUT);
  pinMode(transistor3, OUTPUT);
  pinMode(transistor4, OUTPUT);
  digitalWrite(transistor1, LOW);
  digitalWrite(transistor2, LOW);
  digitalWrite(transistor3, LOW);
  digitalWrite(transistor4, LOW);
}

void loop() {
  unsigned long currentTime = millis();
  // Contador 
  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;
    number++;
    if (number > 9999) {
      number = 0; // Reiniciar a 0 cuando llegue a 9999
    }
  }

  int thousands = number / 1000; // Millar
  int hundreds = (number / 100) % 10; // Centenas
  int tens = (number / 10) % 10; // Decenas
  int units = number % 10; // Unidades

  // Mostrar las unidades de mil
  digitalWrite(transistor1, HIGH);
  digitalWrite(transistor2, LOW);
  digitalWrite(transistor3, LOW);
  digitalWrite(transistor4, LOW);
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], numbers[thousands][i]);
  }
  delay(5); // Ajustar el retardo para un refresco adecuado

  // Mostrar las centenas
  digitalWrite(transistor1, LOW);
  digitalWrite(transistor2, HIGH);
  digitalWrite(transistor3, LOW);
  digitalWrite(transistor4, LOW);
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], numbers[hundreds][i]);
  }
  delay(5); // Ajustar el retardo para un refresco adecuado

  // Mostrar las decenas
  digitalWrite(transistor1, LOW);
  digitalWrite(transistor2, LOW);
  digitalWrite(transistor3, HIGH);
  digitalWrite(transistor4, LOW);
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], numbers[tens][i]);
  }
  delay(5); // Ajustar el retardo para un refresco adecuado

  // Mostrar las unidades
  digitalWrite(transistor1, LOW);
  digitalWrite(transistor2, LOW);
  digitalWrite(transistor3, LOW);
  digitalWrite(transistor4, HIGH);
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], numbers[units][i]);
  }
  delay(5); // Ajustar el retardo para un refresco adecuado
}
