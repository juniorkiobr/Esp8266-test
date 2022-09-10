#include <SocketManager.h>

void setup()
{
    Serial.begin(115200);
    delay(10);
    ConfiguraSocketManager();
}

void loop()
{
    wsClient.poll();
}
