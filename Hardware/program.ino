/* Pin Allocation for Arduino Uno Q
Last Modified: 2026-02-14, 3:00 PM
File Owner: Varsan Jeyakkumar
 */

// #include <Arduino.h> for Arduino IDE FOR VS CODE USE
#include <LiquidCrystal.h> // for LCD Display
#include <DHT.h> // for DHT11 Temperature Sensor

// Digital Pins

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

// LCD
LiquidCrystal LCD(RS, EN, D4, D5, D6, D7); // Initialize the LCD with the specified pins

// Set up the DHT11 Sensor
DHT dht(TEMPSIG, DHT11);

// Function Prototypes
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

    // Set up LCD
    LCD.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows

    // Set up DHT11 Sensor
    dht.begin(); // Initialize the DHT11 sensor

    
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
    LCD.clear(); // Clear the LCD before displaying new information

    // Distance
    LCD.setCursor(0, 0); // Set cursor to the first row
    LCD.print("Dist: "); // Print label for distance
    LCD.print(distance, 2); // Print the distance value on the LCD with 2 decimal places
    LCD.print(" cm "); // Print unit for distance

    // Temperature
    float temperature = dht.readTemperature(); // Read temperature from DHT11 sensor
    LCD.setCursor(0, 1); // Set cursor to the second row
    LCD.print("Temp: ");
    LCD.print(temperature, 1); // Print the temperature value on the LCD with 1 decimal place
    LCD.print(" C ");

}

