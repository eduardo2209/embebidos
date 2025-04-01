/*#define LED_BUILTIN 2*/
#define PB_PIN 5
bool nombre = false ;

void setup() {
  Serial.begin(115200);
  /*pinMode(LED_BUILTIN, OUTPUT);*/
  pinMode(PB_PIN,INPUT); 

}

void loop() {
  if(digitalRead(PB_PIN)==LOW && !nombre){
    Serial.println("Equipo 9");
    nombre=true;
    
  }
  
  if(digitalRead(PB_PIN)==HIGH ){
    nombre=false;
  }
}