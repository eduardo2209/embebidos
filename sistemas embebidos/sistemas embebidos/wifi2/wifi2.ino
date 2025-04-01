//DECLARACIONES
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

//DEFINICIONES
#define LED 2

const char *ssid = "Equipo 4";
const char *password = "mi contraseña";

WiFiServer server(80);


//CONFIGURACIONES
void setup() {
  pinMode(LED, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configurando punto de acceso...");

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Direccion IP: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Servidor iniciado");
}

//BUCLE PRINCIPAL
void loop() {
  WiFiClient client = server.available();   //Esperar clientes entrantes

  if (client) {                             // si se conecta un cliente,
    Serial.println("Nuevo Cliente.");       // imprimir un mensaje en el puerto serial
    String currentLine = "";                // crear cadena vacia para guardar datos del cliente
    while (client.connected()) {            // ciclar mientras el cliente esta conectado
      if (client.available()) {             // si hay bytes para leer del cliente,
        char c = client.read();             // leer un byte, entonces
        Serial.write(c);                    // imprimirlo en el monitor serial
        if (c == '\n') {                    // si el byte es una nueva linea...

          // si el caracter actual es un final de linea, se tienen dos finales de linea seguidos
          // ese es el final de la petición HTTP del cliente, entonces se debe enviar respuesta:
          if (currentLine.length() == 0) {
            // Los encabezados HTTP siempre inician con un código de respuesta (HTTP/1.1 200 OK)
            client.println("HTTP/1.1 200 OK");
            // y un tipo de contenido para que el cliente sepa el contenido que le enviarán, luego una línea en blanco:
            client.println("Content-type:text/html");
            client.println();

            // el contenido de la respuesta HTTP va después de la respuesta:
            // mostrar un texto con un hipervinculo para encender el LED
            client.print("Click <a href=\"/H\">aqui</a> para encender el LED.<br>");
            // mostrar un texto con un hipervinculo para apagar el LED
            client.print("Click <a href=\"/L\">aqui</a> para apagar LED.<br>");

            // La respuesta HTTP termina con otra linea en blanco:
            client.println();
            // romper el bucle
            break;
          } else {    // si se detecta una nueva linea, limpiarla:
            currentLine = "";
          }
        } else if (c != '\r') {  // si se detecta cualquier cosa, excepto un retorno de carro,
          currentLine += c;      // añadirlo a la línea actual
        }

        // Revisar si la petición del cliente fue "GET /H" o "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED, HIGH);               // GET /H enciende el LED
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED, LOW);                // GET /L apaga el LED
        }
      }
    }
    // cerrar la conexión:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
