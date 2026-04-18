#include <FB_Const.h>
#include <FB_Error.h>
#include <FB_Network.h>
#include <FB_Utils.h>
#include <Firebase.h>
#include <FirebaseFS.h>
#include <Firebase_ESP_Client.h>

#include <FB_Const.h>
#include <FB_Error.h>
#include <FB_Network.h>
#include <FB_Utils.h>
#include <Firebase.h>
#include <FirebaseFS.h>
#include <Firebase_ESP_Client.h>

#include <FB_Const.h>
#include <FB_Error.h>
#include <FB_Network.h>
#include <FB_Utils.h>
#include <Firebase.h>
#include <FirebaseFS.h>
#include <Firebase_ESP_Client.h>

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>



// FirebaseDemo_ESP8266 is a sample that demonstrates the different functions
// of the FirebaseArduino API.

#include "DHT.h"              // Including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11         // Define sensor type as DHT 11
#define dht_dpin D2           // DHT data pin connected to D2

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>

// Set these to run example
#define FIREBASE_HOST "dhtgift-5984f-default-rtdb.firebaseio.com"
//#define FIREBASE_AUTH "17GH2UktbcooTveDUSayqQktZDSaK0PK32AAeeJW"   // Uncomment if authentication is required
#define WIFI_SSID "Pankhudi"
#define WIFI_PASSWORD "Kardah6387"

DHT dht(dht_dpin, DHTTYPE);


void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }

  Serial.println();
  Serial.print("Connected! IP Address: ");
  Serial.println(WiFi.localIP());

  //Firebase.begin(FIREBASE_HOST , FIREBASE_AUTH);
  Firebase.begin(FIREBASE_HOST);
}



//int n = 0;


void loop() {
  // Read Humidity and Temperature
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Print to Serial Monitor
  Serial.print("Current Humidity = ");
  Serial.print(h);
  Serial.println("%");
  Serial.print("Temperature = "); 
  Serial.print(t);
  Serial.println(" C");

  // Send values to Firebase
  Firebase.setFloat("humidity", h);
  Firebase.setFloat("temperature", t);
  delay(500);  
  Firebase.remove("humidity");
  delay(100);
  Firebase.remove("temperture");

  delay(1000);
}








  

 
