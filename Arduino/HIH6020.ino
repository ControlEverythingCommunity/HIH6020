// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// HIH6020
// This code is designed to work with the HIH6020_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=HIH6020_I2CS#tabs-0-product_tabset-2

#include<Wire.h>

// HIH6020 I2C address is 0x27(39)
#define Addr 0x27

void setup()
{
  // Initialise I2C communication
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);

  delay(300);
}
void loop()
{
  unsigned int data[4];

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 4 bytes of data
  Wire.requestFrom(Addr, 4);

  // Read 4 bytes of data
  // humidity msb, humidity lsb, temp msb, temp lsb
  if (Wire.available() == 4)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
  }

  // Convert the data to 14-bits
  float humidity = ((((data[0] & 0x3F) * 256.0) + data[1]) * 100.0) / 16382.0;
  int temp = ((data[2] * 256) + (data[3] & 0xFC)) / 4;
  float cTemp = (temp / 16382.0) * 165.0 - 40.0;
  float fTemp = cTemp * 1.8 + 32;

  // Output data to serial monitor
  Serial.print("Relative humidity : ");
  Serial.print(humidity);
  Serial.println(" %RH");
  Serial.print("Temperature in Celsius : ");
  Serial.print(cTemp);
  Serial.println(" C");
  Serial.print("Temperature in Fahrenheit :");
  Serial.print(fTemp);
  Serial.println(" F");
  delay(500);
}

