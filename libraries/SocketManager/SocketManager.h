#include <ESP8266WiFi.h>
#include <ArduinoWebsockets.h>
using namespace websockets;

// Autenticação wi-fi - Coloque aqui a sua configuração
WebsocketsClient wsClient;
const char *ssid = "Lilith-2G";
const char *password = "";
const char *websockets_server = "ws://192.168.100.132:3000/";

// Tratamento de eventos dos dados que vêm do cliente
void onMessageCallback(WebsocketsMessage message);
void onEventsCallback(WebsocketsEvent event, String data);
void ConfiguraSocketManager();