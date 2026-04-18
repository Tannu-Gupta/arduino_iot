#include <ESP8266WiFi.h>

#define led1 D2

WiFiClient client;
WiFiServer server(80);

//const char* ssid = "AR5513_89EEB7";
//const char* password = "bj8q5h9yzx";

const char* ssid = "IOTCC_LAB";
const char* password = "iot_iiit";
String command = ""; // Command received from Android device

// Set Relay Pins
//int led1 = 0;//D2

void setup()
{
    Serial.begin(115200);

    pinMode(led1, OUTPUT);
    digitalWrite(led1, LOW);

    connectWiFi();
    server.begin();
}

void loop()
{
    client = server.available();
    if (!client) return;
        command = checkClient();

    if (command == "r1on" || command == "on" || command == "onn")
        digitalWrite(led1, HIGH);
    else if (command == "r1off" || command == "off" || command == "of")
        digitalWrite(led1, LOW);

    if (command == "alloff" || command == "turn off all" || command == "turn-off all")
    {
        digitalWrite(led1, LOW);
    }

    sendBackEcho(command); // send command echo back to android device
    command = "";
}

/* connecting WiFi */
void connectWiFi()
{
    Serial.println("Connecting to WIFI");
    WiFi.begin(ssid, password);
    while ((WiFi.status() == WL_CONNECTED) == false)
    {
        delay(300);
        Serial.print("..");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("NodeMCU Local IP is : ");
    Serial.print(WiFi.localIP());
}
/* check command received from Android Device */
String checkClient(void)
{
    while (!client.available()) delay(1);
    String request = client.readStringUntil('\r');
    request.remove(0, 5);
    request.remove(request.length() - 9, 9);
    return request;
}

/* send command echo back to android device */
void sendBackEcho(String echo)
{
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(echo);
    client.println("</html>");
    client.stop();
    delay(1);
}  




