//DECLARACIONES
#include <WiFi.h>

//CONFIGURACIONES
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);  // configurar la ESP32 como Estación WiFi
  WiFi.disconnect();    // desconectar el módulo de WiFi por si estuviera conectado
  delay(100);
  Serial.println("Terminan configuraciones\n");
}

//BUCLE PRINCIPAL
void loop() {
  Serial.println("Inicia escaneo");
  // guardar en la variable "n" el número de redes WiFi detectadas
  int n=WiFi.scanNetworks();
  Serial.println("Termina escaneo");
  if (n==0){  // si no se encontraron redes...
    Serial.println("No se encontraron redes inalámbricas");
  }
  else{ //si se encontraron redes...
    Serial.print(n);  //imprimir el número de redes encontradas
    Serial.println(" redes encontradas");
    for (int i=0; i<n; ++i){  //iterar sobre las redes encontradas
      Serial.print(i+1);  //imprimir el número de la red
      Serial.print(": ");
      Serial.print(WiFi.SSID(i)); // imprimir el nombre de la red
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i)); // imprimir la potencia de la señal
      Serial.print(" )");
      //imprimir un asterisco si la red está protegida con contraseña
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");

  delay(5000);
}
