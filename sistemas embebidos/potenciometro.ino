//#include <Arduino.h>

// Parámetros de lectura y cálculo
float voltage   = 3.3;      // Voltaje de referencia
float vol       = 0.0;      // Voltaje medido
float angulomax = 270.0;    // Ángulo máximo (en grados)
float angulo    = 0.0;      // Ángulo calculado

// Pines
const int potPin = 34;      // Pin analógico del potenciómetro
const int ledPin = 2;       // Pin digital del LED

// Función de PWM por software
// duty: valor entre 0 y 255 (0 = apagado, 255 = encendido máximo)
void softPWM(int pin, int duty) {
  // Definimos un período de PWM de 2000 microsegundos (aprox. 500 Hz)
  const int periodo = 2000; 
  int tiempoAlto = (duty * periodo) / 255; // Tiempo en HIGH
  int tiempoBajo = periodo - tiempoAlto;    // Tiempo en LOW

  digitalWrite(pin, HIGH);
  delayMicroseconds(tiempoAlto);
  digitalWrite(pin, LOW);
  delayMicroseconds(tiempoBajo);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Leemos el valor analógico (0 - 4095)
  int valorAnalogico = analogRead(potPin);
  
  // Convertimos la lectura a voltaje
  vol = (valorAnalogico / 4096.0) * voltage;
  
  // Calculamos el ángulo proporcional
  angulo = (vol / voltage) * angulomax;
  
  // Mapeamos el voltaje a un valor de brillo (0 - 255)
  int brillo = (int)((vol / voltage) * 255);

  // Mostramos los valores por el Monitor Serial
  Serial.print("Voltage: ");
  Serial.print(vol, 2);
  Serial.print(" V, Ángulo: ");
  Serial.print(angulo, 1);
  Serial.print("°, Brillo: ");
  Serial.println(brillo);

  // Durante 500 ms, ejecutamos el PWM por software de forma continua
  unsigned long inicio = millis();
  while (millis() - inicio < 500) {
    softPWM(ledPin, brillo);
  }
}