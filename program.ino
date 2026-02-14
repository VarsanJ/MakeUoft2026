/* Pin Allocation for Arduino Uno Q
Last Modified: 2026-02-14, 11:47 AM
File Owner: Varsan Jeyakkumar
 */

#include <Arduino.h> // for Arduino IDE
#include <LedControl.h>

// Digital Pins

// Ultrasonic
const int ECHO1 = 4;
const int TRIGGER1 = 5;
// Lighting
const int LED1 = 11;
const int LED2 = 12;
// Display
LedControl lc = LedControl(7, 9, 8, 1); // DIN, CLK, CS, number of devices
const int DIN = 7;
const int CS = 8;
const int CLOCK = 9;

// Analog Pins
const int TEMPSIG = A1;

// Variable Declaration for Calculation Variables
float Xtime = 0;
float distance = 0;

void distance();
void information();

void setup() {
    // Initialize Serial Communication
    Serial.begin(9600);
    
    // Set pin modes for Ultrasonic Sensor
    pinMode(ECHO1, INPUT);
    pinMode(TRIGGER1, OUTPUT);
    
    // Set pin modes for LEDs
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    
    // Set pin modes for Display
    pinMode(DIN, OUTPUT);
    pinMode(CS, OUTPUT);
    pinMode(CLOCK, OUTPUT);
}

void loop() {
    distance(); // Call the distance function to measure and display distance, and also control LED
}

void distance() {
    // Trigger the Ultrasonic Sensor
    digitalWrite(TRIGGER1, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER1, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER1, LOW);
    
    // Read the Echo Pin
    Xtime = pulseIn(ECHO1, HIGH);
    
    // Calculate Distance (in cm)
    distance = (Xtime * 0.034) / 2;
    
    // Print Distance to Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    // Control LEDs based on distance
    if (distance < 20) {
        digitalWrite(LED1, HIGH); // Turn on LED1 if object is closer than 20 cm
        digitalWrite(LED2, HIGH);  // Turn on LED2 if object is closer than 20 cm
    } else {
        digitalWrite(LED1, LOW);  // Turn off LED1 if object is farther than 20 cm
        digitalWrite(LED2, LOW); // Turn off LED2 if object is farther than 20 cm
    }
    
    delay(1000); // Wait for 1 second before the next measurement
}

void information() {
    // This function can be used to display additional information on the display
    
}

