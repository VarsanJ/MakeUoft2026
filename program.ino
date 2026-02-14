/* Pin Allocation for Arduino Uno Q
Last Modified: 2026-02-14, 11:47 AM
File Owner: Varsan Jeyakkumar
 */

#include <Arduino.h> // for Arduino IDE


// Digital Pins
int blah = 30;
// Ultrasonic
const int ECHO1 = 4;
const int TRIGGER1 = 5;
// Lighting
const int LED1 = 10;
const int LED2 = 11;
// Display
const int D4 = 6;
const int D5 = 7;
const int D6 = 8;
const int D7 = 9; // 4 Bits for Display 
const int RS = 12;
const int EN = 13; // Control Pins for Display
// Temperature
const int TEMPSIG = 3;

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

    // Set up the display
    lc.shutdown(0, false); // Wake up the display
    lc.setIntensity(0, 8); // Set brightness level
    lc.clearDisplay(0); // Clear the display

    // Set up the DHT11 Sensor
    DHT dht(DHTPIN, DHT11);
}

void loop() {
    distance(); // Call the distance function to measure and display distance, and also control LED
    information(); // Call the information function to display additional information on the display
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
    
    
}

