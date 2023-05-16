#define led_connection 5
#define led_run 6

void led_connect()
{
  digitalWrite(led_connection, HIGH);
  delay(1000);
  digitalWrite(led_connection, LOW);
  delay(1000);
}

void setup() {
  pinMode(led_connection, OUTPUT);
  pinMode(led_run, OUTPUT);
}

void loop()
{
  led_connect();
}
