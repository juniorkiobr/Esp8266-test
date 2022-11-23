#include <SocketManager.h>

void setup()
{
    ConfiguraSocketManager();
}

void loop()
{
    if (Serial.available())
    {
        String dados = Serial.readStringUntil('\n');
        wsClient.send(dados);
    }
}
