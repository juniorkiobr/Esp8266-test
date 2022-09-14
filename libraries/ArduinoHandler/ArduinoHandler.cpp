#include <ArduinoHandler.h>

const int txPin = 1;
const int rxPin = 3;

// SoftwareSerial mySerial(rxPin, txPin);

void ConfiguraArduinoHandler()
{
    // mySerial.begin(115200);
    // Serial1.begin(9600, SERIAL_8N1, txPin, rxPin);
}

void EnviaDadosArduinoHandler(String dados)
{
    // mySerial.println(dados.c_str());
}

String RecebeDadosArduinoHandler(String id_sensor)
{
    String dados = "";
    if (mySerial.available())
    {
        dados = "Received from arduino: " + mySerial.readStringUntil('\n');
    }
    return dados;
}