#define flamePin 2
#define led1 0
#define led2 1

void setup() {

  Serial.begin(115200);
  pinMode(flamePin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
   // put your setup code here, to run once:
}

void loop() {
  int Flame = digitalRead(flamePin);
  Serial.print("\nFlame value: ");
  Serial.print(Flame);
  delay(1000);

  if(Flame == 0){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);

  }
  else{
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
  }


  // put your main code here, to run repeatedly:

}
