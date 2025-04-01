// Practica 1 encender un led 
// Team Septiembre(9) + compañero Dario
// Proposito: Encender un led con el ES32 y que varie su encendido con forme avanza el tiempo
//23/01/2025

#define LED_BUILTIN 23
int coun=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(coun);
  digitalWrite(LED_BUILTIN, LOW);
  delay(coun);
  coun+=10;

  if (coun>=200){
    coun=0;
  }

}

