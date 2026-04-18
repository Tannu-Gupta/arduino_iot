int trigPin = 9;
int echoPin = 10;
int led = 7;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(trigPin , OUTPUT);
  pinMode(echoPin, INPUT);

  // put your setup code here, to run once:

}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin , LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2)/29.1;
  Serial.print(distance);
  Serial.println("CM");
  delay(100); 

  // put your main code here, to run repeatedly:



if((distance <= 15)){
  digitalWrite(led, HIGH);
  delay(300);
  digitalWrite(led,LOW);
}
else if(distance > 15){
  digitalWrite(led, LOW);
}
}




