void setup() 
{
  Serial.begin(112500);
  Serial.begin(9600);
}

void loop() 
{
  Serial.print("MIC-SMART-Serial");
  Serial1.print("MIC-SMART-Serial1");
  delay(1000);
}
