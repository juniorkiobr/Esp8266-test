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
  if(hasConnectedWS){
    wsClient.poll();
  }

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
}
