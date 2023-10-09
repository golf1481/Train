#define buzzer 7
void setup() 
{
  pinMode(buzzer, OUTPUT);
}

void loop() 
{
  analogWrite(buzzer, 0);
  delay(1000);
  analogWrite(buzzer, 0);
  delay(1000);
}
