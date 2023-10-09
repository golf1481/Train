#define in13 36
#define in2 11

#define led_run 6

#define out1 3

int buttonState1 = 0;
int buttonState2 = 0;

void setup()
{
  pinMode(in13, INPUT);
  pinMode(in2, INPUT);
  pinMode(led_run, OUTPUT);
  pinMode(out1, OUTPUT);
}


void loop()
{
  buttonState1 = digitalRead(in13);
  buttonState2 = digitalRead(in2);

  if ( buttonState1 == LOW || buttonState2 == LOW)
  {
    digitalWrite(led_run, HIGH);
    digitalWrite(out1, HIGH);
  } else
  {
    digitalWrite(led_run, LOW);
    digitalWrite(out1, LOW);
  }
}
