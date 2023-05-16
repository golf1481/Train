#define buzzer 7

void setup() 
{
  pinMode(buzzer, OUTPUT);
}

void loop() 
{
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(5000);
}
