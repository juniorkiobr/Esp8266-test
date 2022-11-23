#pragma once
#ifndef _SENSORESMANAGER_H_
#define _SENSORESMANAGER_H_

#include "Arduino.h"
#include <DHT.h>

struct sensorInfo
{
    int pin;
    String name_sensor;
    int type;
    int default_value;
};

struct interactInfo
{
    int pin;
    String name_interacao;
    int default_value;
};

extern sensorInfo sensors[];
extern interactInfo interacoes[];

void readSensor(int id_sensor, int *status_code, String *status_message);
void writeInteracao(int id_interacao, int value, int *status_code, String *status_message);
void ConfigurarSensoresManager();
void LerSensorTemp(int *status_code, float *temperatura, float *umidade);
void LerSensorPir(int *status_code, int *estado);

#endif