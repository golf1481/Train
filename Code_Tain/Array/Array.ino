int myArray[6] = {1, 3, 5, 7, 8, 9};
String names[100] = {"Alice", "Bob", "Charlie", "Dave"};

int z;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop()
{
  Serial.print("names[2] : ");Serial.println(names[2]);
  delay(1000);
}
