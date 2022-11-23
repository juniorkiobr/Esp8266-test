#pragma once
#ifndef _SOCKETMANAGER_H_
#define _SOCKETMANAGER_H_

#include <iostream>
#include <string.h>
#include <ESP8266WiFi.h>
#include <ArduinoWebsockets.h>
#include <lwip/netdb.h>
// #include <ArduinoHandler.h>

using namespace websockets;

// Autenticação wi-fi - Coloque aqui a sua configuração
extern WebsocketsClient wsClient;
extern const char *ssid;
extern const char *password;
extern String websockets_server;

// Tratamento de eventos dos dados que vêm do cliente
void onMessageCallback(WebsocketsMessage message);
void onEventsCallback(WebsocketsEvent event, String data);
void ConfiguraSocketManager();
void ConectaSocketManager();

#endif
