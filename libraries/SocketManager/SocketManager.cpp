#include <SocketManager.h>

WebsocketsClient wsClient;
const char *ssid = "Lilith-2G";
const char *password = "23201709";
const char *websockets_server = "ws://192.168.100.132:3000/";

bool insensitiveCompare(const String &a, const String &b)
{
    if (a.length() != b.length())
        return false;
    for (int i = 0; i < a.length(); i++)
    {
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    }
    return true;
}

bool isSubString(const String &a, const String &b)
{
    if (a.length() > b.length())
        return false;
    for (int i = 0; i < b.length(); i++)
    {
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    }
    return true;
}

void onMessageCallback(WebsocketsMessage message)
{
    String dados = (message.data());
    Serial.print("Got Message: ");
    Serial.println(dados);
    if (insensitiveCompare(dados, "ping"))
    {
        wsClient.send("pong");
    }
    else if (isSubString(dados, "cmd_ard_uno:>"))
    {
        dados.replace("cmd_ard_uno:>", "");
        // EnviaDadosArduinoHandler(dados);
    }
}

void onEventsCallback(WebsocketsEvent event, String data)
{
    if (event == WebsocketsEvent::ConnectionOpened)
    {
        Serial.println("Connnection Opened");
    }
    else if (event == WebsocketsEvent::ConnectionClosed)
    {
        Serial.println("Connnection Closed");
    }
    else if (event == WebsocketsEvent::GotPing)
    {
        Serial.println("Got a Ping!");
    }
    else if (event == WebsocketsEvent::GotPong)
    {
        Serial.println("Got a Pong!");
    }
}

void ConfiguraSocketManager()
{
    // ConfiguraArduinoHandler();
    Serial.begin(115200);
    delay(10);

    // Connect to wifi
    WiFi.begin(ssid, password);

    // Wait some time to connect to wifi
    for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++)
    {
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