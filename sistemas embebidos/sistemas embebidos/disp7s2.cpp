//DECLARACIONES

//DEFINICIONES
//definimos los pines que se usarán para los segmentos del display
#define potenciometro 14
int LEDS[]={23,22,21,19,18,5,4};
int i,j=0; //variable global i
int valor=0; //variable global para compartir valores
int lectura=0;
                          //a b c d e f g
int arreglo[16][7] = {    { 1,1,1,1,1,1,0 },    // 0
                          { 0,1,1,0,0,0,0 },    // 1
                          { 1,1,0,1,1,0,1 },    // 2
                          { 1,1,1,1,0,0,1 },    // 3
                          { 0,1,1,0,0,1,1 },    // 4
                          { 1,0,1,1,0,1,1 },    // 5
                          { 1,0,1,1,1,1,1 },    // 6
                          { 1,1,1,0,0,0,0 },    // 7
                          { 1,1,1,1,1,1,1 },    // 8
                          { 1,1,1,0,0,1,1 },    // 9
                          { 1,1,1,0,1,1,1 },    // A
                          { 0,0,1,1,1,1,1 },    // B
                          { 1,0,0,1,1,1,0 },    // C
                          { 0,1,1,1,1,0,1 },    // d
                          { 1,0,0,1,1,1,1 },    // E
                          { 1,0,0,0,1,1,1 }};   // F

//FUNCIONES
void escribirNumero(int valor){
  for (j=0; j<7; j++){
    //recorrer cada pin y asignarle los valores correspondientes
    digitalWrite(LEDS[j], arreglo[valor][j]);
  }
}

//CONFIGURACIONES
void setup() {
  for (i=0; i<7; i++){
    //recorrer cada pin y configurarlo como salida
    pinMode(LEDS[i], OUTPUT);
  }
}

void loop() {
  escribirNumero(3);
}
