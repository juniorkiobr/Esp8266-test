#include <SocketManager.h>

WebsocketsClient wsClient;
const char *ssid = "Lilith-2G";
const char *password = "23201709";
bool hasConnectedWS = false;

// const char *ssid = "Dafy";
// const char *password = "12123434";
String websockets_server = "ws://192.168.100.132:2053/";
// const char *websockets_server = "ws://179.104.55.71:2053/";
// String websockets_server = "ws://192.168.43.43:2053/";

// void getIpFromHostname(const char *hostname, char &ip)
// {
//     struct hostent *he;
//     struct in_addr **addr_list;
//     int i;

//     if ((he = lwip_gethostbyname(hostname)) == NULL)
//     {
//         // get the host info
//         Serial.println("Failed to resolve hostname");
//         return;
//     }

//     addr_list = (struct in_addr **)he->h_addr_list;

//     for (i = 0; addr_list[i] != NULL; i++)
//     {
//         // Return the first one;
//         strcpy(ip, inet_ntoa(*addr_list[i]));
//         return;
//     }

//     return;
// }

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

// bool isSubString(const String &a, const String &b)
// {
//     if (a.length() > b.length())
//         return false;
//     for (int i = 0; i < b.length(); i++)
//     {
//         if (tolower(a[i]) != = tolower(b[i]))
//             return false;
//     }
//     return true;
// }
int isSubString(const String &a, const String &b)
{
    if (a.length() > b.length())
        return -2;
    for (int i = 0; i < b.length(); i++)
    {
        if (tolower(a[i]) != tolower(b[i]))
            return -1;
    }
    return 0;
}

void callCommand(String command)
{
    if (strstr(command.c_str(), "readSensor:") != NULL)
    {
        command = command.substring(12);
        int id_sensor = command.toInt();
        int status_code;
        String status_message;
        readSensor(id_sensor, &status_code, &status_message);
        Serial.println(status_message);
        wsClient.send(status_message);
    }
    if (strstr(command.c_str(), "writeInteraction:") != NULL)
    {
        command = command.substring(18);
        int status_code;
        String status_message;

        int id_interacao = command.substring(0, command.indexOf(";")).toInt();
        int value = command.substring(command.indexOf(";") + 1).toInt();
        writeInteracao(id_interacao, value, &status_code, &status_message);
        Serial.println(status_message);
        wsClient.send(status_message);
    }
}

void onMessageCallback(WebsocketsMessage message)
{
    String dados = message.data();
    Serial.print("Got Message: ");
    Serial.println(dados);
    // Serial.println(isSubString("cmd_ard_uno:>", dados));
    // Serial.println(strstr(dados.c_str(), "cmd_ard_uno:>") != NULL);

    if (insensitiveCompare("ping", dados))
    {
        wsClient.send("pong");
    }
    else if (strstr(dados.c_str(), "cmd_ard_uno:>") != NULL)
    {
        dados = dados.substring(12);
        // Serial.println(dados);
        callCommand(dados);
    }
}

void onEventsCallback(WebsocketsEvent event, String data)
{
    if (event == WebsocketsEvent::ConnectionOpened)
    {
        Serial.println("Connnection Opened");
        hasConnectedWS = true;
    }
    else if (event == WebsocketsEvent::ConnectionClosed)
    {
        Serial.println("Connnection Closed");
        hasConnectedWS = false;
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

    // char *ipHost = "";
    // getIpFromHostname("marcelogonzaga.dev.br", *ipHost);
    // websockets_server = ("ws://" + String(ipHost) + ":2053/");

    ConectaSocketManager();

    // Setup Callbacks
    wsClient.onMessage(onMessageCallback);
    wsClient.onEvent(onEventsCallback);

    // Connect to server
    while (!wsClient.connect(websockets_server))
    {
        Serial.println("Connection Failed! " + String(websockets_server) + " Retrying...");
        delay(1000);
    }

    // Send a message
    wsClient.send("Hi Server!");
    // Send a ping
    wsClient.ping();
}

void ConectaSocketManager()
{
    // Connect to wifi
    WiFi.begin(ssid, password);

    // Wait some time to connect to wifi
    for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++)
    {
        Serial.print(".");
        delay(1000);
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Failed to connect to wifi");
        return;
    }
    else
    {
        Serial.println("Connected to wifi");
    }
}