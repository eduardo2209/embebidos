const int ppot = 34; 
const int pled = 32; 
const float voltR = 3.3; 
int potVa = 0; 
float ang = 0; 
float volt = 0; 
float brilloPorcentaje = 0; 

void setup() {
  Serial.begin(115200); 
  pinMode(pled, OUTPUT); 
  }

void loop() {
  potVa = analogRead(ppot); // Lee el valor del potenciómetro
  volt = potVa * (voltR / 4095.0); // Calcula el voltaje
  ang = map(potVa, 0, 4095, 0, 270); // Mapea el valor del potenciómetro a un ángulo entre 0 y 270 grados
  int brillo = map(potVa, 0, 4095, 0, 255); // Mapea el valor del potenciómetro a un valor de brillo entre 0 y 255
  analogWrite(pled, brillo); // Ajusta el brillo del LED
  brilloPorcentaje = (brillo / 255.0) * 100; // Calcula el porcentaje de brillo
  7
  Serial.print("Ángulo: ");
  Serial.print(ang);
  Serial.print(" grados, Voltaje: ");
  Serial.print(volt);
  Serial.print(" V, Brillo del LED: ");
  Serial.print(brilloPorcentaje);
  Serial.println(" %");
}