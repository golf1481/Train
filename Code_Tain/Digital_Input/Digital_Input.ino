#define in1 10
#define in2 11

#define led_run 6

int buttonState1 = 0;
int buttonState2 = 0;

void setup()
{
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(led_run, OUTPUT);
}


void loop()
{
  buttonState1 = digitalRead(in1);
  buttonState2 = digitalRead(in2);

  if ( buttonState1 == LOW || buttonState2 == LOW)
  {
    digitalWrite(led_run, HIGH);
  } else
  {
    digitalWrite(led_run, LOW);
  }
}
