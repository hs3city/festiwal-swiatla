/*
 Example using the SparkFun HX711 breakout board with a scale
 By: Nathan Seidle
 SparkFun Electronics
 Date: November 19th, 2014
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 This example demonstrates basic scale output. See the calibration sketch to get the calibration_factor for your
 specific load cell setup.
 This example code uses bogde's excellent library: https://github.com/bogde/HX711
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE
 The HX711 does one thing well: read load cells. The breakout board is compatible with any wheat-stone bridge
 based load cell which should allow a user to measure everything from a few grams to tens of tons.
 Arduino pin 2 -> HX711 CLK
 3 -> DAT
 5V -> VCC
 GND -> GND
 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
*/

#include "HX711.h"

// Include the Wire library for I2C
#include <Wire.h>

#define calibration_factor -3050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define DOUT  3
#define CLK  2

HX711 scale;
#define ledPin 10
#define hotLedPin 11

int wire_status = 0;

void setup() {
  // Join I2C bus as slave with address 2
  Wire.begin(0x9);
  
  // Call receiveEvent when data received                
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  
  Serial.begin(9600);
  Serial.println("HX711 scale demo");
  pinMode(ledPin, OUTPUT);

  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  digitalWrite(hotLedPin, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)  

  Serial.println("Readings:");
}

// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  Serial.print("The Pi is calling!");
}

void requestEvent() {
  Wire.write(wire_status);
}

void loop() {
  float value = scale.get_units();
  Serial.print("Reading: ");
  Serial.print(value, 1); //scale.get_units() returns a float
  Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
  if(value <= 20){
    // Neutral
    wire_status = 0;
    digitalWrite(hotLedPin, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)  
  } else {
    // Pressed
    wire_status = 1;
    Serial.println("Pressed");
    digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(hotLedPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  delay(100);
}
