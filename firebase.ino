#include <FB_Const.h>
#include <FB_Error.h>
#include <FB_Network.h>
#include <FB_Utils.h>
#include <Firebase.h>
#include <FirebaseFS.h>
#include <Firebase_ESP_Client.h>

#include <dummy.h>

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

// LIBRARIES
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h> // Modern Firebase library
#include "DHT.h"

// PROVIDE FIREBASE CREDENTIALS
#define FIREBASE_HOST "dhtgift-2ae98-default-rtdb.firebaseio.com"
// IMPORTANT: You need the Database Secret for authentication
#define FIREBASE_AUTH "ILyrLfRT3MjhqiLXQ0PQnk46dpAIajUYpm5whP7v" 

// WIFI CREDENTIALS
#define WIFI_SSID "realme C67 5G"
#define WIFI_PASSWORD "sonali17"

// DHT SENSOR SETUP
#define DHTTYPE DHT11
#define dht_dpin D2

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Define DHT object
DHT dht(dht_dpin, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Configure Firebase
  config.host = FIREBASE_HOST;
  // Assign the database secret (legacy token)
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Initialize Firebase
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true); // Handle auto-reconnection
}

void loop() {
  // Read sensor data
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Current Humidity = ");
  Serial.print(h);
  Serial.println("% ");
  Serial.print("temperature = ");
  Serial.print(t);
  Serial.println("C ");

  // Send data to Firebase, with error checking
  if (Firebase.RTDB.setFloat(&fbdo, "humidity", h)) {
    Serial.println("Humidity sent successfully");
  } else {
    Serial.println("Error sending humidity: " + fbdo.errorReason());
  }

  if (Firebase.RTDB.setFloat(&fbdo, "temperature", t)) {
    Serial.println("Temperature sent successfully");
  } else {
    Serial.println("Error sending temperature: " + fbdo.errorReason());
  }

  delay(500);

  // Remove data from Firebase, with error checking
  if (Firebase.RTDB.deleteNode(&fbdo, "humidity")) {
    Serial.println("Humidity removed successfully");
  } else {
    Serial.println("Error removing humidity: " + fbdo.errorReason());
  }

  delay(1000);

  if (Firebase.RTDB.deleteNode(&fbdo, "temperature")) {
    Serial.println("Temperature removed successfully");
  } else {
    Serial.println("Error removing temperature: " + fbdo.errorReason());
  }
  
  delay(1000);
}
