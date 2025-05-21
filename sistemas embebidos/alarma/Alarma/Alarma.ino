// Pines de entrada y LED
const int ledPin = 5;
const int alSwitchPin = 2;
const int puSwitchPin = 4;
const int v1SwitchPin = 16;
const int v2SwitchPin = 17;

// Control de transistores
const int display1Enable = 12;
const int display2Enable = 14;

// Pines de segmentos
const int segA1 = 13;
const int segA2 = 19;
const int segB  = 22;
const int segC  = 3;
const int segD1 = 15;
const int segD2 = 18;
const int segE  = 32;
const int segF  = 27;
const int segG1 = 26;
const int segG2 = 23;
const int segK  = 21;
const int segN  = 33;

// Variables de multiplexación
unsigned long previousMillis = 0;
const unsigned long intervalo = 300; // Tiempo por display
int stepIndex = 0;
int fase = 0;
int totalPares = 0;
char pares[3][2];

// Parpadeo del LED
unsigned long ledPreviousMillis = 0;
const unsigned long ledInterval = 200; // 0.2 s
bool ledState = false;

void apagarSegmentos() {
  digitalWrite(segA1, LOW); digitalWrite(segA2, LOW); digitalWrite(segB, LOW);  digitalWrite(segC, LOW);
  digitalWrite(segD1, LOW); digitalWrite(segD2, LOW); digitalWrite(segE, LOW);  digitalWrite(segF, LOW);
  digitalWrite(segG1, LOW); digitalWrite(segG2, LOW); digitalWrite(segK, LOW);  digitalWrite(segN, LOW);
}

void mostrarCaracter(char c) {
  apagarSegmentos();

  switch (c) {
    case 'P': digitalWrite(segA1, HIGH); digitalWrite(segA2, HIGH);
              digitalWrite(segB, HIGH);  digitalWrite(segF, HIGH);
              digitalWrite(segE, HIGH);  digitalWrite(segG1, HIGH);
              digitalWrite(segG2, HIGH); break;

    case 'V': digitalWrite(segF, HIGH);  digitalWrite(segE, HIGH);
              digitalWrite(segN, HIGH);  digitalWrite(segK, HIGH); break;

    case 'U': digitalWrite(segB, HIGH);  digitalWrite(segC, HIGH);
              digitalWrite(segD1, HIGH); digitalWrite(segD2, HIGH);
              digitalWrite(segE, HIGH);  digitalWrite(segF, HIGH); break;

    case '1': digitalWrite(segB, HIGH);  digitalWrite(segC, HIGH); break;

    case '2': digitalWrite(segA1, HIGH); digitalWrite(segA2, HIGH);
              digitalWrite(segB, HIGH);  digitalWrite(segG1, HIGH);
              digitalWrite(segG2, HIGH); digitalWrite(segE, HIGH);
              digitalWrite(segD1, HIGH); digitalWrite(segD2, HIGH); break;

    case '0': digitalWrite(segA1, HIGH); digitalWrite(segA2, HIGH);
              digitalWrite(segB, HIGH);  digitalWrite(segC, HIGH);
              digitalWrite(segD1, HIGH); digitalWrite(segD2, HIGH);
              digitalWrite(segE, HIGH);  digitalWrite(segF, HIGH);
              digitalWrite(segG1, HIGH); digitalWrite(segG2, HIGH);
              digitalWrite(segK, HIGH);  digitalWrite(segN, HIGH); break;

    default: break;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(alSwitchPin, INPUT);
  pinMode(puSwitchPin, INPUT);
  pinMode(v1SwitchPin, INPUT);
  pinMode(v2SwitchPin, INPUT);

  pinMode(display1Enable, OUTPUT);
  pinMode(display2Enable, OUTPUT);
  digitalWrite(display1Enable, LOW);
  digitalWrite(display2Enable, LOW);

  pinMode(segA1, OUTPUT); pinMode(segA2, OUTPUT);
  pinMode(segB, OUTPUT);  pinMode(segC, OUTPUT);
  pinMode(segD1, OUTPUT); pinMode(segD2, OUTPUT);
  pinMode(segE, OUTPUT);  pinMode(segF, OUTPUT);
  pinMode(segG1, OUTPUT); pinMode(segG2, OUTPUT);
  pinMode(segK, OUTPUT);  pinMode(segN, OUTPUT);

  apagarSegmentos();
}

void loop() {
  int al = digitalRead(alSwitchPin);
  int pu = digitalRead(puSwitchPin);
  int v1 = digitalRead(v1SwitchPin);
  int v2 = digitalRead(v2SwitchPin);

  bool alertaActiva = (pu == HIGH || v1 == HIGH || v2 == HIGH);

  if (al == HIGH) {
    // Parpadeo del LED si hay switches activos
    if (alertaActiva) {
      unsigned long currentMillis = millis();
      if (currentMillis - ledPreviousMillis >= ledInterval) {
        ledPreviousMillis = currentMillis;
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
      }
    } else {
      digitalWrite(ledPin, HIGH); // Encendido fijo
    }

    // Construir arreglo de pares activos solo cuando empieza
    if (stepIndex == 0 && fase == 0) {
      totalPares = 0;
      if (pu == HIGH) { pares[totalPares][0] = 'P'; pares[totalPares][1] = 'U'; totalPares++; }
      if (v1 == HIGH) { pares[totalPares][0] = 'V'; pares[totalPares][1] = '1'; totalPares++; }
      if (v2 == HIGH) { pares[totalPares][0] = 'V'; pares[totalPares][1] = '2'; totalPares++; }

      if (totalPares == 0) {
        digitalWrite(display1Enable, HIGH);
        digitalWrite(display2Enable, LOW);
        mostrarCaracter('0');
        Serial.println("Display1: 0");
        delay(500);
        return;
      }
    }

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= intervalo) {
      previousMillis = currentMillis;

      // Apagar todo antes de siguiente fase
      digitalWrite(display1Enable, LOW);
      digitalWrite(display2Enable, LOW);
      mostrarCaracter(' ');

      if (fase == 0) {
        // Mostrar Display 1
        digitalWrite(display1Enable, HIGH);
        mostrarCaracter(pares[stepIndex][0]);
        Serial.print("Display1: ");
        Serial.println(pares[stepIndex][0]);
        fase = 1;
      } else {
        // Mostrar Display 2
        digitalWrite(display2Enable, HIGH);
        mostrarCaracter(pares[stepIndex][1]);
        Serial.print("Display2: ");
        Serial.println(pares[stepIndex][1]);
        fase = 0;
        stepIndex = (stepIndex + 1) % totalPares;
      }
    }

  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(display1Enable, LOW);
    digitalWrite(display2Enable, LOW);
    mostrarCaracter(' ');
    stepIndex = 0;
    fase = 0;
  }
}