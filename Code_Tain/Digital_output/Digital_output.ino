#define led_connection 5
#define led_run 6

void led_connect()
{
  digitalWrite(led_connection, HIGH);
  digitalWrite(led_run, LOW);
  delay(100);
  digitalWrite(led_connection, LOW);
  digitalWrite(led_run, HIGH);
  delay(100);
}
  
void setup() {
  pinMode(led_connection, OUTPUT);
  pinMode(led_run, OUTPUT);

}

void loop() {
  led_connect();
}
