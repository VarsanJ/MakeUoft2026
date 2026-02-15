#include <LiquidCrystal.h>
#include <DHT.h>

// Pin Definitions
const int ECHO1 = 4;
const int TRIGGER1 = 5;
const int xD4 = 6;
const int xD5 = 7;
const int xD6 = 8;
const int xD7 = 9;
const int RS = 12;
const int EN = 13;
const int LED1 = 11;
const int TEMPSIG = 2; // DHT11 on pin 2

// Variables for Measuring Readings
float distance = 0; .// Default to 0 cm until first reading
float temperature = 22.0; // Default to 22°C until first reading

// Initialize LCD and DHT
LiquidCrystal LCD(RS, EN, xD4, xD5, xD6, xD7); // LCD pins
DHT dht(TEMPSIG, DHT11); // DHT11 sensor on pin 2
unsigned long lastDHTRead = 0;

// Manual pulse measurement function was implemented since Uno Q does not have PulseIn functionality
unsigned long measurePulse(uint8_t pin) {
  unsigned long timeout = 50000;
  unsigned long startTime = micros(); // Micros defines # second since start, use at clock since we only care about delta versus abs value for time
  
  while (digitalRead(pin) == LOW) {
    if (micros() - startTime > timeout) return 0;
  }
  
  unsigned long pulseStart = micros();
  
  while (digitalRead(pin) == HIGH) {
    if (micros() - pulseStart > timeout) return 0;
  }
  
  return micros() - pulseStart;
}

void setup() {
    // Pin Modes
    pinMode(ECHO1, INPUT);
    pinMode(TRIGGER1, OUTPUT);
    pinMode(LED1, OUTPUT);

    // Startup Sequence
    LCD.begin(16, 2);
    LCD.clear();
    LCD.print("Initializing");
    dht.begin();
    delay(2000);
    LCD.clear();
    LCD.print("Ready!");
    delay(1000);
}

void loop() {
    digitalWrite(LED1, HIGH);
    measureDistance();
    
    // Read DHT11 every 2 seconds
    if (millis() - lastDHTRead >= 2000) {
        float newTemp = dht.readTemperature();
        if (!isnan(newTemp)) { // We only update if we got a valid reading
            temperature = newTemp;
        }
        lastDHTRead = millis();
    }
    
    displayInfo();
    delay(300);
}

void measureDistance() {
    digitalWrite(TRIGGER1, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIGGER1, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER1, LOW);
    
    unsigned long duration = measurePulse(ECHO1);
    
    if (duration == 0) {
        distance = 0;
    } else {
        distance = (duration * 0.0343) / 2;
    }
    
    // Filter noise
    if (distance < 2 || distance > 400) {
        distance = 0;
    }
}

void displayInfo() {
    // Update distance
    LCD.setCursor(0, 0);
    LCD.print("                ");
    LCD.setCursor(0, 0);
    
    if (distance == 0) {
        LCD.print("Dist: ---"); // No Distance Found
    } else {
        LCD.print("Dist: ");
        LCD.print(distance, 1);
        LCD.print(" cm");
    }
    
    // Update temperature
    LCD.setCursor(0, 1);
    LCD.print("                ");
    LCD.setCursor(0, 1);
    LCD.print("Temp: ");
    LCD.print(temperature, 1);
    LCD.print(" C");
}
