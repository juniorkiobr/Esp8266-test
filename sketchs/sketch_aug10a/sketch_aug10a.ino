#include <SocketManager.h>

void setup()
{
    ConfiguraSocketManager();
}

void loop()
{
    wsClient.poll();
    if (Serial.available())
    {
        String dados = Serial.readStringUntil('\n');
        wsClient.send(dados);
    }
}
