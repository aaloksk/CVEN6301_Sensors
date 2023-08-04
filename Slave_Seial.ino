// Code by Aalok Sharma Kafle and Kushum K C
// Code for Peripheral (Slave)
// Data is collected for temperature from DHT11 and phototresistor form A3.

#include "DHT.h"  // Include the DHT sensor library

#define DHTPIN 2     // Define the digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // Define the type of DHT sensor (DHT 11 in this case)
#define LDRPIN A3    // Define the analog pin connected to the Light Dependent Resistor (LDR)

DHT dht(DHTPIN, DHTTYPE);  // Create a DHT object with the defined pin and type

void setup() {  // Setup function runs once when the device is powered on or reset
  Serial.begin(9600);  // Start serial communication at 9600 baud rate for output
  dht.begin();  // Initialize the DHT sensor
}

void loop() {  // Main loop function runs repeatedly after setup
  float t = dht.readTemperature();  // Read the temperature from the DHT sensor
  int ldrReading = analogRead(LDRPIN); // Read the LDR value from the LDR sensor

  Serial.print(t); // Print the temperature value
  Serial.print(","); // Print a comma for separating the temperature and light intensity values
  Serial.println(ldrReading); // Print the light intensity value and move to the next line

  delay(1000);  // Wait for 1 second before the next loop iteration
}
