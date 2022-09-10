#include <ESP8266WiFi.h>
#include <ArduinoWebsockets.h>
using namespace websockets;

// Autenticação wi-fi - Coloque aqui a sua configuração
WebsocketsClient wsClient;
const char* ssid     = "Lilith-2G";
const char* password = "";
const char* websockets_server = "ws://192.168.100.132:3000/";
// Tratamento de eventos dos dados que vêm do cliente 


void onMessageCallback(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    Serial.println(message.data());
    switch(message){
    
    }
}

void onEventsCallback(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
    } else if(event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
    } else if(event == WebsocketsEvent::GotPong) {
        Serial.println("Got a Pong!");
    }
}

void setup() {
    Serial.begin(115200);
    delay(10);
    // Connect to wifi
    WiFi.begin(ssid, password);

    // Wait some time to connect to wifi
    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
        Serial.print(".");
        delay(1000);
    }

    // Setup Callbacks
    wsClient.onMessage(onMessageCallback);
    wsClient.onEvent(onEventsCallback);
    
    // Connect to server
    wsClient.connect(websockets_server);

    // Send a message
    wsClient.send("Hi Server!");
    // Send a ping
    wsClient.ping();
}

void loop() {
  wsClient.poll();

}
