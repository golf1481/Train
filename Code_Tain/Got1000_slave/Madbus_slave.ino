#include "ModbusRtu.h"
#define ID   1

Modbus slave(ID, Serial1, 0);

int8_t state = 0;

int num = 2;

uint16_t au16data[20];

void setup()
{
  pinMode(42, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  slave.start();
}

void loop()
{

  state = slave.poll( au16data ,num );

  if (state == 7) {
    Serial.print("-----Waiting...------- ");
  }
  if (state == 8)
  {
    Serial.println("-----START ------- ");
    for (int i = 0; i < (num * 2); i++)
    {
      slave.poll( au16data, num  );
      delay(100);
    }
    
      digitalWrite(42, LOW );
      Serial.print("1.D200 : "); Serial.println(au16data[0]);
      Serial.print("2.D201 : "); Serial.println(au16data[1]);
   
      Serial.println("------------------------");
      Serial.println(" ");
      delay(5000);
      
  }
}
  
}
