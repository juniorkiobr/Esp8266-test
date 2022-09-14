#pragma once
#ifndef _SENSORESMANAGER_H_
#define _SENSORESMANAGER_H_

#include "Arduino.h"
#include <DHT.h>

void ConfigurarSensoresManager();
void LerSensorTemp(int *status_code, float *temperatura, float *umidade);
void LerSensorPir(int *status_code, int *estado);

#endif