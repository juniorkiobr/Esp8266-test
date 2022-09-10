#pragma once
#ifndef _SOCKETMANAGER_H_
#define _SOCKETMANAGER_H_

#include <iostream>
#include <string.h>
#include <ESP8266WiFi.h>
#include <ArduinoWebsockets.h>

using namespace websockets;

// Autenticação wi-fi - Coloque aqui a sua configuração
extern WebsocketsClient wsClient;
extern const char *ssid;
extern const char *password;
extern const char *websockets_server;

// Tratamento de eventos dos dados que vêm do cliente
void onMessageCallback(WebsocketsMessage message);
void onEventsCallback(WebsocketsEvent event, String data);
void ConfiguraSocketManager();

#endif
