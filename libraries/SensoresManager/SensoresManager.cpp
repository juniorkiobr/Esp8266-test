#include "SensoresManager.h"

// DHT Config
// #define DHTPIN D2
// #define DHTTYPE DHT11

sensorInfo sensors[] = {
    {D2, "temperatura", DHT11, 0},
    {D3, "presenca", 0, LOW},
};

interactInfo interacoes[] = {
    {D4, "led", LOW},
    {D5, "led", LOW},
    {D6, "led", LOW},
    {D7, "led", LOW},

};

// PIR Config
// int sensor = D3; // PIR Out pin (interval between 1s - 247s)
// int state = LOW;
// int val = 0;

void setupSensores()
{
    for (int i = 0; i < (*(&sensors + 1) - sensors); i++)
    {
        if (sensors[i].name_sensor == "temperatura")
        {
            DHT dht(sensors[i].pin, sensors[i].type);
            dht.begin();
        }
        else
        {
            pinMode(sensors[i].pin, INPUT);
        }
    }
}

void setupInteracoes()
{
    for (int i = 0; i < (*(&interacoes + 1) - interacoes); i++)
    {
        pinMode(interacoes[i].pin, OUTPUT);
        digitalWrite(interacoes[i].pin, interacoes[i].default_value);
    }
}

void formatReturn(int status_code, int id_sensor, String value, String *return_value)
{
    *return_value = "{\"status_code\": " + String(status_code) + ", \"id_sensor\": " + String(id_sensor) + String(value) + "}";
}

void writeInteracao(int id_interacao, int value, int *status_code, String *status_message)
{
    digitalWrite(interacoes[id_interacao].pin, value);
    *status_code = 200;

    formatReturn(*status_code, (id_interacao + 1), ", value: " + String(value), status_message);
    status_message->replace("id_sensor", "id_interacao");
}

void readSensor(int id_sensor, int *status_code, String *status_message)
{
    if (sensors[id_sensor].name_sensor == "temperatura")
    {
        DHT dht(sensors[id_sensor].pin, sensors[id_sensor].type);
        dht.begin();
        float h = dht.readHumidity();
        float t = dht.readTemperature();

        if (isnan(h) || isnan(t))
        {
            *status_code = 500;
            formatReturn(*status_code, (id_sensor + 1), ", status_message: \"Falha ao ler o sensor\"", status_message);
            // *status_message = "Erro ao ler o sensor";
        }
        else
        {
            *status_code = 200;
            formatReturn(*status_code, (id_sensor + 1), ", temperatura: " + String(t) + ", umidade: " + String(h), status_message);

            // *status_message = "{\"status_code\": " + String(*status_code) + \", id_sensor\": " + String(id_sensor) + ", \"temperatura\": " + String(t) + ", \"umidade\": " + String(h);
        }
    }
    else
    {
        int val = digitalRead(sensors[id_sensor].pin);
        *status_code = 200;
        formatReturn(*status_code, (id_sensor + 1), ", estado: " + String(val), status_message);
        // *status_message = ", id_sensor\": " + String(id_sensor) + ", \"estado\": " + String(val);
    }
}

void ConfigurarSensoresManager()
{
    setupSensores();
    setupInteracoes();
    Serial.println("Configurando SensoresManager");
}