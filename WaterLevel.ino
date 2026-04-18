/***************************************************
   WATER LEVEL IOT PROJECT USING NODEMCU + THINGSPEAK
****************************************************/

#include <ESP8266WiFi.h>

#define TRIG D5     // Trigger pin of ultrasonic sensor
#define ECHO D6    // Echo pin of ultrasonic sensor
#define BUZZER D3   // Buzzer pin

// ------- WiFi Credentials -------
const char* ssid = "sonali";
const char* pass = "88888888";

unsigned long mychannelNumber = 3197222;

// ------- ThingSpeak Credentials -------
String apiKey = "RPOITMJ2XGI7TJ99";
const char* server = "api.thingspeak.com";

WiFiClient client;

// ------- Tank Setting (Change according to tank height) -------
int tankDepth = 20;     // in CM → Your tank height

// Measure distance from ultrasonic sensor
long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);
  long distance = duration * 0.034 / 2;  // Convert to cm
  return distance;
}

void setup() {
  Serial.begin(19200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(BUZZER, LOW);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

void loop() {

  long distance = getDistance();

  if (distance > tankDepth) 
      distance = tankDepth;

  int waterLevel = map(distance, 0, tankDepth, 100, 0);

  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.println("%");

  // ---------- BUZZER ALERT ----------
  if (waterLevel < 20) {        // Water very low  
    digitalWrite(BUZZER, HIGH);
  } 
  else if (waterLevel > 90) {   // Tank full  
    digitalWrite(BUZZER, HIGH);
  } 
  else {
    digitalWrite(BUZZER, LOW);  // Normal condition
  }

  // ---------- SEND DATA TO THINGSPEAK ----------
  if (client.connect(server, 80)) {
    String url = "/update?api_key=" + apiKey;
    url += "&field1=" + String(waterLevel);
    url += "&field2=" + String(distance);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + server + "\r\n" +
                 "Connection: close\r\n\r\n");

    Serial.println("Uploaded to ThingSpeak!");
  }

  delay(20000);    // ThingSpeak minimum delay = 15 sec
}
