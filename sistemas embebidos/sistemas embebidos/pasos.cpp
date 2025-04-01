//DECLARACIONES
#include <Arduino.h>

//DEFINICIONES
int bobina[]={23,22,21,19};

int retraso=50;
int i,j=0;

int fase[4][4]={  {1,0,0,0},    //valor 0
                  {0,1,0,0},    //valor 1
                  {0,0,1,0},    //valor 2
                  {0,0,0,1}  }; //valor 3

//FUNCIONES
void paso(int valor){
  for(j=0;j<4;j++){
    digitalWrite(bobina[j], fase[valor][j]);
  }
}

//CONFIGURACIONES
void setup() {
  for(i=0;i<4;i++){
    pinMode(bobina[i], OUTPUT);
  }  
}

//PRINCIPAL
void loop() {
  for(i=0;i<4;i++){
    paso(i);
    delay(retraso);
  }
  
}