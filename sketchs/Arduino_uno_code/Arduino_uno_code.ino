#include "Arduino.h"
#include <SoftwareSerial.h>
#include "SensoresManager.h"
#include <SocketManager.h>

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

const int ESP01Rx = 6;
const int ESP01Tx = 5;

SoftwareSerial espSerial(ESP01Rx, ESP01Tx);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Connected to Serial");
  ConfiguraSocketManager();
  ConfigurarSensoresManager();
}

void loop()
{
  int status_code = 200;
  String status_message = "";
  float temperatura = 0;
  float umidade = 0;
  // String dados = "";
  // LerSensorTemp(&status_code, &temperatura, &umidade);
  // dados = "{\"status_code\": " + String(status_code) + ", \"id_sensor\": " + String(01) + ", \"temperatura\": " + String(temperatura) + ", \"umidade\": " + String(umidade) + "}";
  // int inputVal = analogRead (A0);
  // Serial.println(inputVal);
  // Serial.println(dados);
  // wsClient.send(dados);
  // delay(1000);
  // int estado = 0;
  // LerSensorPir(&status_code, &estado);
  // dados = "{\"status_code\": " + String(status_code) + ", \"id_sensor\": " + String(02) + ", \"estado\": " + String(estado) + "}";
  // Serial.println(dados);
  // wsClient.send(dados);
  readSensor(0, &status_code, &status_message);
  Serial.println(status_message);
  wsClient.send(status_message);
  readSensor(1, &status_code, &status_message);
  Serial.println(status_message);
  wsClient.send(status_message);
}
