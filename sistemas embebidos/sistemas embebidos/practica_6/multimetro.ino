#include <ESP32Servo.h>
#include <TM1637Display.h>

#define VOLT_PIN 34       // ADC voltímetro
#define LDR_PIN 35        // ADC fotómetro (LDR)
#define MODE_BUTTON 15    // Botón para cambiar de modo
#define SERVO_PIN 23      // PWM del servo
#define LED_VOLT_PIN 18   // LED para modo voltímetro
#define LED_LUX_PIN 19    // LED para modo fotómetro

Servo servo;
TM1637Display display(4, 5);  // Pinos del display TM1637 (CLK, DIO)

int mode = 0;  // 0 = voltímetro, 1 = fotómetro

void setup() {
  pinMode(MODE_BUTTON, INPUT_PULLUP);
  pinMode(LED_VOLT_PIN, OUTPUT);
  pinMode(LED_LUX_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
  display.setBrightness(0x0f);  // Establecer el brillo del display

  digitalWrite(LED_VOLT_PIN, HIGH);  // Encender LED de voltímetro por defecto
  digitalWrite(LED_LUX_PIN, LOW);    // Apagar LED de fotómetro por defecto

  Serial.begin(115200);  // Solo por si necesitas depurar
}

void loop() {
  // Leer botón para cambiar modo
  if (digitalRead(MODE_BUTTON) == LOW) {
    mode = !mode;
    delay(500);  // debounce

    // Cambiar LED
    if (mode == 0) {
      digitalWrite(LED_VOLT_PIN, HIGH);  // Encender LED de voltímetro
      digitalWrite(LED_LUX_PIN, LOW);    // Apagar LED de fotómetro
    } else {
      digitalWrite(LED_VOLT_PIN, LOW);   // Apagar LED de voltímetro
      digitalWrite(LED_LUX_PIN, HIGH);   // Encender LED de fotómetro
    }
  }

  if (mode == 0) {
    medirVoltaje();
  } else {
    medirLuz();
  }

  delay(300);
}

void medirVoltaje() {
  int raw = analogRead(VOLT_PIN);
  float voltLeido = (raw * 3.3) / 4095.0;
  float voltaje = corregirVoltaje(voltLeido);

  // Mostrar valor en el display
  int valorMostrar = (int)(voltaje * 10);  // Para mostrar un valor entre 0 y 33
  display.showNumberDec(valorMostrar, false);

  // Mover servo (0.0V → 0°, 3.3V → 180°)
  int angulo = map(voltaje * 100, 0, 330, 0, 180);
  servo.write(constrain(angulo, 0, 180));
}

void medirLuz() {
  int raw = analogRead(LDR_PIN);

  // Valores estimados: 683 (oscuridad) – 3870 (flash)
  int nivel = constrain(map(raw, 683, 3870, 0, 99), 0, 99);
  float luz = nivel / 10.0;

  // Mostrar valor en el display
  int valorMostrar = (int)(luz * 10);  // Para mostrar un valor entre 0 y 9.9
  display.showNumberDec(valorMostrar, false);

  // Mover servo (0.0 → 0°, 9.9 → 180°)
  int angulo = map(nivel, 0, 99, 0, 180);
  servo.write(constrain(angulo, 0, 180));
}

float corregirVoltaje(float vLeido) {
  float tabla[][2] = {
    {0.00, 0.00},
    {0.37, 0.50},
    {0.87, 1.00},
    {1.37, 1.50},
    {1.85, 2.00},
    {2.38, 2.50},
    {3.07, 3.00},
    {3.30, 3.30}
  };

  const int n = sizeof(tabla) / sizeof(tabla[0]);

  if (vLeido <= tabla[0][0]) return tabla[0][1];
  if (vLeido >= tabla[n - 1][0]) return tabla[n - 1][1];

  for (int i = 0; i < n - 1; i++) {
    float x0 = tabla[i][0], y0 = tabla[i][1];
    float x1 = tabla[i + 1][0], y1 = tabla[i + 1][1];

    if (vLeido >= x0 && vLeido <= x1) {
      float t = (vLeido - x0) / (x1 - x0);
      return y0 + t * (y1 - y0);
    }
  }

  return vLeido;
}
