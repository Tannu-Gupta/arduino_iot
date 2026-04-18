#include "DHT.h"



#define DHTPIN 7
#define DHTTYPE DHT11

int led = 6;

DHT dht(DHTPIN, DHTTYPE);




void setup() {
  Serial.begin(9600);
  dht.begin();
  // put your setup code here, to run once:

}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.println("Temperature = ");
  Serial.println(t);
  Serial.print("Humidity = ");
  Serial.println(h);
  delay(2000);

  if (h>32){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led , LOW);
  }
  // put your main code here, to run repeatedly:

}
