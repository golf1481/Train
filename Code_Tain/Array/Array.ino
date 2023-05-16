int myArray[6] = {1, 3, 5, 7, 8, 9};

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop()
{
  Serial.print("myArray[2] : ");Serial.println(myArray[2]);
  delay(1000);
}
