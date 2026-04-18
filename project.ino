#define BLYNK_TEMPLATE_ID "TMPL3CGKWhAoQ"
#define BLYNK_TEMPLATE_NAME "Water Level Indicator 1"
#define BLYNK_AUTH_TOKEN "OTFsOCOM3e5bx0NHXVDI9xU1Y7hgzHMj"



#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// ========== Ultrasonic Sensor Pins ==========
#define trig D1    // Trigger Pin
#define echo D0    // Echo Pin

// ========== User Settings ==========
char ssid[] = "realme C67 5G";        // Your WiFi name
char pass[] = "88888888";      // Your WiFi password

int tankDepth = 4;              // Tank depth in CM (change as needed)

BlynkTimer timer;

// ========== Function to Calculate Water Level ==========
long getDistanceCM() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  long distance = duration * 0.034 / 2;   // Convert to CM

  return distance;
}

// ========== Send Data to Blynk ==========
void sendWaterLevel() {
  long distance = getDistanceCM();

  if (distance > tankDepth) distance = tankDepth;

  int waterLevel = map(distance, 0, tankDepth, 100, 0); // % full

  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.println("%");

  Blynk.virtualWrite(V1, waterLevel);  // Send % to Blynk
  Blynk.virtualWrite(V2, distance);    // Send distance to Blynk
}

// ========== Setup ==========
void setup() {
  Serial.begin(9600);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  // Start Blynk
  Blynk.begin("OTFsOCOM3e5bx0NHXVDI9xU1Y7hgzHMj"
," realme C67 5G"," 88888888");

  // Send data every 1 second
  timer.setInterval(1000L, sendWaterLevel);
}

// ========== Loop ==========
void loop() {
  Blynk.run();
  timer.run();
}
