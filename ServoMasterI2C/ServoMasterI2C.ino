
/**
 * Simple illustration how to remotely controll 'smaer servo' vi I2C
 */

#include <Wire.h>

void setup()
{
  Wire.begin(); // join i2c bus
  Serial.begin(115200);
}

byte x = 0;

void loop()
{
  Wire.beginTransmission(4); // transmit to device #4
  Serial.print("Set Remote Servo to: ");
  Serial.println(x);
  Wire.write(x); // sends one byte  
  Wire.endTransmission(); // stop transmitting  

  x+=15;
  if(x > 180) x = 0;
   
  delay(500);

  // Request servo position
  Wire.requestFrom(4, 1);

  // Read servo position
  while(Wire.available())
  { 
    char c = Wire.read();
    Serial.print("Current Remote Servo Position: ");
    Serial.println(c, DEC);
  }

  delay(500);
}
