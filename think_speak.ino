#include <ThingSpeak.h>

#include "ThingSpeak.h"
#include "DHT.h"                // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11           // DHT 11
#include <ESP8266WiFi.h>


#define dht_dpin D2             // D2
#define SECRET_SSID "vivo T2x 5G"  // your network SSID (name)
#define SECRET_PASS "12345678"        // replace MyPassword with your network password

#define SECRET_CH_ID 3034441
#define SECRET_WRITE_APIKEY "X35W0GQDD9B6BE3O"  // replace with your ThingSpeak Write API Key

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password 
int keyIndex = 0;            // your network key index number (needed only for WEP)

DHT dht(dht_dpin, DHTTYPE);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(100);

  WiFi.mode(WIFI_STA);

  ThingSpeak.begin(client);
}
void loop() {
  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line as needed.
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  int h = dht.readHumidity();
  int t = dht.readTemperature();

if (h <= 100 && t <= 100)
{
    Serial.print("Current Humidity = ");
    Serial.print(h);
    Serial.print("% ");
    Serial.print("Temperature = ");
    Serial.print(t);
    Serial.println("*C ");
}
ThingSpeak.writeField(myChannelNumber, 1, h, myWriteAPIKey);
delay(500);
ThingSpeak.writeField(myChannelNumber, 2, t, myWriteAPIKey);

// Wait 2 seconds to update the channel again
delay(2000);
}


