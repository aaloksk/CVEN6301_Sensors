#include "DHT.h"  // Include the DHT sensor library
#include <Wire.h>  // Include the Wire library for I2C communication

#define DHTPIN 2     // Define the digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // Define the type of DHT sensor (DHT 11 in this case)
#define LDRPIN A3    // Define the analog pin connected to the Light Dependent Resistor (LDR)

DHT dht(DHTPIN, DHTTYPE);  // Create a DHT object with the defined pin and type

void setup() {
  // Start the I2C bus as a master
  Wire.begin();

  // Start serial communication at 9600 baud rate for output
  Serial.begin(9600);

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Print a message to the serial monitor
  Serial.println("I am Master");

  // Read the temperature from the DHT sensor
  float tempMaster = dht.readTemperature();
  // Print the temperature to the serial monitor
  Serial.print("Temperature = ");
  Serial.println(tempMaster);

  // Read the light intensity from the LDR
  int lightIntensityMaster = analogRead(LDRPIN);
  // Print the light intensity to the serial monitor
  Serial.print("Light Intensity = ");
  Serial.println(lightIntensityMaster);

  // Start an I2C transmission to the slave with address 0x14
  Wire.beginTransmission(0x14);
  // Send the temperature over the I2C bus
  Wire.write((byte)tempMaster);
  // Send the light intensity over the I2C bus
  Wire.write((byte)lightIntensityMaster);
  // End the I2C transmission
  Wire.endTransmission();
   
  // Wait for 1 second before the next loop iteration
  delay(1000);
}
