#define led_connection 5
#define led_run 6
int counter = 0;

void led_connect()
{
  digitalWrite(led_connection, HIGH); delay(1000); digitalWrite(led_connection, LOW); delay(1000);
}

void setup()
{
  Serial.begin(9600);
  pinMode(led_connection, OUTPUT);
  pinMode(led_run, OUTPUT);
}

void loop()
{

  counter++;   //counter = counter + 1;
  //led_connect();
  Serial.print("counter : "); Serial.println(counter);
  if(counter > 10 || counter < 20)
  {
    digitalWrite(led_run, HIGH);
    Serial.println("led_run");
    
  }else{
    digitalWrite(led_run, LOW);
  }
  delay(1000);
}
