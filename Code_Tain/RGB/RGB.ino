#define rgb_red 41
#define rgb_green 45
#define rgb_blue 42

void setup() 
{
  pinMode(rgb_red, OUTPUT);
  pinMode(rgb_green, OUTPUT);
  pinMode(rgb_blue, OUTPUT);

}

void loop() 
{
  led_red();
  delay(1000);
  led_green();
  delay(1000);
  led_blue();
  delay(1000);
  led_off();
  delay(1000);

}

void led_red()
{
  digitalWrite(rgb_red, LOW); digitalWrite(rgb_green, HIGH); digitalWrite(rgb_blue, HIGH);
}

void led_green()
{
  digitalWrite(rgb_red, HIGH); digitalWrite(rgb_green, LOW); digitalWrite(rgb_blue, HIGH);
}

void led_blue()
{
  digitalWrite(rgb_red, HIGH); digitalWrite(rgb_green, HIGH); digitalWrite(rgb_blue, LOW);
}

void led_off()
{
  digitalWrite(rgb_red, HIGH); digitalWrite(rgb_green, HIGH); digitalWrite(rgb_blue, HIGH);
}
