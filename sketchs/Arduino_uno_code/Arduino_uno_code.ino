#include "Arduino.h"
#include <SoftwareSerial.h>
#include "SensoresManager.h"

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
  espSerial.begin(115200);
  ConfigurarSensoresManager();
}

void loop()
{
  int status_code = 200;
  float temperatura = 0;
  float umidade = 0;
  LerSensorTemp(&status_code, &temperatura, &umidade);
  espSerial.println("{\"status_code\": " + String(status_code) + ", \"id_sensor\": " + String(01) +  ", \"temperatura\": " + String(temperatura) + ", \"umidade\": " + String(umidade) + "}");
  Serial.println("{\"status_code\": " + String(status_code) + ", \"id_sensor\": " + String(01) +  ", \"temperatura\": " + String(temperatura) + ", \"umidade\": " + String(umidade) + "}");
  delay(1000);
  int estado = 0;
  LerSensorPir(&status_code, &estado);
  espSerial.println("{\"status_code\": " + String(status_code) + ", \"id_sensor\": " + String(02) + ", \"estado\": " + String(estado) + "}");
  Serial.println("{\"status_code\": " + String(status_code) + ", \"id_sensor\": " + String(02) + ", \"estado\": " + String(estado) + "}");
}
