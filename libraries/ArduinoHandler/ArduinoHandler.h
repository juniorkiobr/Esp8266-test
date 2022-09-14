#pragma once
#ifndef _ARDUINOHANDLER_H_
#define _ARDUINOHANDLER_H_

#include <SoftwareSerial.h>
#include <iostream>
#include <string>
using namespace std;

extern const int txPin;
extern const int rxPin;

extern SoftwareSerial mySerial;

void ConfiguraArduinoHandler();
void EnviaDadosArduinoHandler(String dados);
String RecebeDadosArduinoHandler(String id_sensor);

#endif