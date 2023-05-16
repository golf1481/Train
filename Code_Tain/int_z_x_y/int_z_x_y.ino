int x=10;
int y-20;
int z;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop()
{
  z = x+y;
  Serial.print("X : ");Serial.println(x);
  Serial.print("Y : ");Serial.println(y);
  Serial.print("X+Y : ");Serial.println(z);
  Serial.println("----------");
  delay(1000);
}
