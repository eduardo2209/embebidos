//Codigo con foto resistencia 


// Definimos los pines para cada segmento del display de 16 segmentos
const int segmentos[] = {15, 13, 33, 23, 22, 32, 2, 4, 5, 18, 12, 14, 27, 26, 25, 19};

// Pin de la fotorresistencia
const int pinFotoresistencia = 34;  // Ajusta según la conexión en tu ESP32
const int umbralLuz = 2000;  // Ajusta según la lectura de tu fotorresistencia

// Definimos la representación de cada letra en el display
const int letras[][16] = {
  { 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 }, // A
  { 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0 }, // B
  { 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, // C
  { 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0 }, // D
  { 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 }, // E
  { 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 }, // F
  { 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0 }, // G
  { 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 }, // H
  { 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0 }, // I
  { 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // J
  { 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0 }, // K
  { 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, // L
  { 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0 }, // M
  { 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0 }, // N
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, // O
  { 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 }, // P
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0 }, // Q
  { 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0 }, // R
  { 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0 }, // S
  { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0 }, // T
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, // U
  { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1 }, // V
  { 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1 }, // W
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1 }, // X
  { 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0 }, // Y
  { 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 }  // Z
};

// Nombres del equipo
const char* nombres[] = {"ZAHARA", "KEVIN", "MICHEL"};

void setup() {
  for (int i = 0; i < 16; i++) {
    pinMode(segmentos[i], OUTPUT);
    digitalWrite(segmentos[i], LOW);
  }
  pinMode(pinFotoresistencia, INPUT);
}

void apagarDisplay() {
  for (int i = 0; i < 16; i++) {
    digitalWrite(segmentos[i], LOW);
  }
}

void mostrarLetra(char letra) {
  if (letra >= 'A' && letra <= 'Z') {
    int indice = letra - 'A';
    for (int i = 0; i < 16; i++) {
      digitalWrite(segmentos[i], letras[indice][i]);
    }
  }
}

void mostrarNombre(const char* nombre) {
  for (int i = 0; nombre[i] != '\0'; i++) {
    if (analogRead(pinFotoresistencia) < umbralLuz) {
      apagarDisplay();
      return;
    }
    mostrarLetra(nombre[i]);
    delay(500);
    apagarDisplay();
    delay(200);
  }
  Serial.begin(115200); // En setup()

}

void loop() {
  int luz = analogRead(pinFotoresistencia);

Serial.println(luz);  // Para ver el valor en tiempo real
delay(500);

  if (luz >= umbralLuz) {
    for (int i = 0; i < 4; i++) {
      mostrarNombre(nombres[i]);
      delay(1000);
    }
  } else {
    apagarDisplay();
  }
}