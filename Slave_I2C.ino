#include "DHT.h"  // Include the DHT sensor library
#include <Wire.h>  // Include the Wire library for I2C communication

#define DHTPIN 2     // Define the digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // Define the type of DHT sensor (DHT 11 in this case)
#define LDRPIN A3    // Define the analog pin connected to the Light Dependent Resistor (LDR)

DHT dht(DHTPIN, DHTTYPE);  // Create a DHT object with the defined pin and type

byte tempMaster;  // Variable to store the temperature received from the master
byte lightIntensityMaster;  // Variable to store the light intensity received from the master

void setup() {
  // Start serial communication at 9600 baud rate for output
  Serial.begin(9600);

  // Initialize the DHT sensor
  dht.begin();

  // Start the I2C bus as a slave with address 0x14
  Wire.begin(0x14);
    
  // Register the function to call when data is received
  Wire.onReceive(DataReceive);
}

void loop() {
  // Nothing to do in the main loop
}

void DataReceive(int numBytes) {
  // Read the temperature and light intensity from the I2C bus
  if(Wire.available()) {
    tempMaster = Wire.read();
    lightIntensityMaster = Wire.read();

    // Print the received temperature and light intensity
    Serial.print("Temperature from Master: ");
    Serial.println(tempMaster);
    Serial.print("Light Intensity from Master: ");
    Serial.println(lightIntensityMaster);

    // Read the temperature and light intensity from the slave's own sensors
    float tempSlave = dht.readTemperature();
    int lightIntensitySlave = analogRead(LDRPIN);

    // Print the temperature and light intensity from the slave's own sensors
    Serial.print("Temperature from Slave: ");
    Serial.println(tempSlave);
    Serial.print("Light Intensity from Slave: ");
    Serial.println(lightIntensitySlave);
  }
}
