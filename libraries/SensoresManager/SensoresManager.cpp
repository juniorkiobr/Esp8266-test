#include "SensoresManager.h"

// DHT Config
#define DHTPIN A1
#define DHTTYPE DHT11

// PIR Config
int sensor = 2; // PIR Out pin (interval between 1s - 247s)
int state = LOW;
int val = 0;

DHT dht(DHTPIN, DHTTYPE);

void ConfigurarSensoresManager()
{
    pinMode(sensor, INPUT);
    dht.begin();
}

void LerSensorTemp(int *status_code, float *temperatura, float *umidade)
{
    *temperatura = dht.readTemperature();
    *umidade = dht.readHumidity();
    if (isnan(*umidade) || isnan(*temperatura))
    {
        *status_code = 500;
        return;
    }
    else
    {
        *status_code = 200;
        return;
    }
}

void LerSensorPir(int *status_code, int *estado)
{
    *estado = digitalRead(sensor); // read sensor value
    if (isnan(*estado))
    {
        *status_code = 500;
        return;
    }
}