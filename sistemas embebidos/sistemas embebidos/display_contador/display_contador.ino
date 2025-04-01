#define PBTN_PIN 15

/* Pines del display de 7 segmentos */ 
                    /*| a | b | c | d | e | f | g |*/
const int segments[] = {23, 22, 21, 19, 18, 5, 4};

/* Variables */ 
int count = 0;
/* Configuración de los pines */ 
void setup() {
  Serial.begin(115200);
  pinMode(PBTN_PIN, INPUT_PULLUP);
  for (int i = 0; i < 7; i++) {
    pinMode(segments[i], OUTPUT);
    digitalWrite(segments[i], LOW); 
    /* Asegurarse de que todos los segmentos estén apagados al inicio */
  }
}


/* Función para mostrar el número en el display */ 
void displayNumber(int num) {
  const bool segmentMap[10][7] = {
  /* a, b, c, d, e, f, g */
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
  /* Recorre el mapa para mostrar los números */
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], segmentMap[num][i]);
  }
}

void loop() {
  pbtn = digitalRead(PBTN_PIN);
  /* Activa la funcion cada que se presione el pinshi boton */
  if (pbtn == LOW && anpbtn == HIGH) {
    count = (count + 1) % 10;
    displayNumber(count);
    Serial.println(count);
  }
  /* Actualiza el estado del pinshi boton */
  anpbtn = pbtn;
}

