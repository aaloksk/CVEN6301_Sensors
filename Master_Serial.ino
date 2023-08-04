// Code by Aalok Sharma Kafle and Kushum K C
// Code for Controller (Master)


#include "DHT.h"  // Include the DHT sensor library

#define DHTPIN 2     // Define the digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // Define the type of DHT sensor (DHT 11 in this case)
#define LDRPIN A5    // Define the analog pin connected to the Light Dependent Resistor (LDR)

DHT dht(DHTPIN, DHTTYPE);  // Create a DHT object with the defined pin and type


void setup() {  // Setup function runs once when the device is powered on or reset
  Serial.begin(9600);  // Start serial communication at 9600 baud rate for output
  dht.begin();  // Initialize the DHT sensor
}

void loop() {  // Main loop function runs repeatedly after setup
  if (Serial.available()) {  // Check if there is serial data available
    String data = Serial.readStringUntil('\n');  // Read the incoming data until newline character

    int commaIndex = data.indexOf(',');  // Find the index of the comma in the data string
    float t_slave = data.substring(0, commaIndex).toFloat();  // Extract the temperature data from the slave device
    int ldrReading_slave = data.substring(commaIndex + 1).toInt();  // Extract the LDR reading from the slave device

    float t_master = dht.readTemperature();  // Read the temperature from the master device's DHT sensor
    int ldrReading_master = analogRead(LDRPIN);  // Read the LDR value from the master device's LDR sensor

    Serial.print("Temperature_slave: ");  // Print the label for the slave device's temperature
    Serial.print(t_slave);  // Print the temperature value from the slave device
    Serial.print(" *C\t");  // Print the unit for the temperature
    Serial.print("Light intensity_slave: ");  // Print the label for the slave device's light intensity
    Serial.print(ldrReading_slave);  // Print the light intensity value from the slave device
    Serial.print("\t");  // Print a tab space
    Serial.print("Temperature_master: ");  // Print the label for the master device's temperature
    Serial.print(t_master);  // Print the temperature value from the master device
    Serial.print(" *C\t");  // Print the unit for the temperature
    Serial.print("Light intensity_master: ");  // Print the label for the master device's light intensity
    Serial.println(ldrReading_master);  // Print the light intensity value from the master device and move to the next line
    }
}
