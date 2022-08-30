#include <ESP8266WiFi.h>
#define LoadPin 2 //GPIO02

const char* ssid = "Lilith-2G";
const char* password = "";
WiFiServer server(80);//Service Port
int value = LOW;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);
  pinMode(LoadPin, OUTPUT);
  digitalWrite(LoadPin, LOW);
  // Connect to WiFi network
  Serial.println();
  Serial.print("Conectando na rede: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  delay(500);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado!");
  //Inicializa o servidor
  server.begin();
  Serial.println("Servidor Inicializado");
  // Imprime o endereco IP
  Serial.print("Utilize essa URL: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Updated!!");

}
