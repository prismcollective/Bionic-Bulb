#include <Adafruit_NeoPixel.h>
#include <AccelStepper.h>

// Define pins
#define MIC_PIN A0          // MAX9814 microphone analog pin
#define STEP_PIN 2          // Stepper motor step pin
#define DIR_PIN 3           // Stepper motor direction pin

// Define LED strip pins (one pin per strip)
#define STRIP_1_PIN 6       // Data pin for LED strip 1
#define STRIP_2_PIN 7       // Data pin for LED strip 2
#define STRIP_3_PIN 8       // Data pin for LED strip 3
#define STRIP_4_PIN 9       // Data pin for LED strip 4
#define STRIP_5_PIN 10      // Data pin for LED strip 5

#define LEDS_PER_STRIP 8    // Number of LEDs per strip
#define NUM_STRIPS 5        // Number of LED strips

// Initialize NeoPixel strips (one object per strip)
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(LEDS_PER_STRIP, STRIP_1_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(LEDS_PER_STRIP, STRIP_2_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(LEDS_PER_STRIP, STRIP_3_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(LEDS_PER_STRIP, STRIP_4_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(LEDS_PER_STRIP, STRIP_5_PIN, NEO_GRB + NEO_KHZ800);

// Initialize stepper motor
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// Variables
int micValue = 0;           // Microphone input value
int threshold = 500;        // Threshold for sound detection
int ledBrightness = 50;     // LED brightness (0-255)

void setup() {
  // Initialize all NeoPixel strips
  strip1.begin();           // Initialize strip 1
  strip1.show();            // Turn off all LEDs on strip 1
  strip2.begin();           // Initialize strip 2
  strip2.show();            // Turn off all LEDs on strip 2
  strip3.begin();           // Initialize strip 3
  strip3.show();            // Turn off all LEDs on strip 3
  strip4.begin();           // Initialize strip 4
  strip4.show();            // Turn off all LEDs on strip 4
  strip5.begin();           // Initialize strip 5
  strip5.show();            // Turn off all LEDs on strip 5

  // Initialize stepper motor
  stepper.setMaxSpeed(1000); // Set maximum speed for the stepper motor
  stepper.setAcceleration(500); // Set acceleration for the stepper motor

  // Start serial for debugging
  Serial.begin(9600);
}

void loop() {
  // Read microphone input
  micValue = analogRead(MIC_PIN);

  // Debug: Print microphone value to serial monitor
  Serial.println(micValue);

  // Control stepper motor based on microphone input
  if (micValue > threshold) {
    // If sound is detected above the threshold, move the stepper motor
    stepper.move(100);      // Move stepper motor 100 steps
    stepper.run();          // Run the stepper motor
  }

  // Control LED strips based on microphone input
  if (micValue > threshold) {
    // If sound is detected above the threshold, light up all LED strips
    lightUpStrips(strip1, 0, LEDS_PER_STRIP); // Light up strip 1
    lightUpStrips(strip2, 0, LEDS_PER_STRIP); // Light up strip 2
    lightUpStrips(strip3, 0, LEDS_PER_STRIP); // Light up strip 3
    lightUpStrips(strip4, 0, LEDS_PER_STRIP); // Light up strip 4
    lightUpStrips(strip5, 0, LEDS_PER_STRIP); // Light up strip 5
  } else {
    // If no sound is detected, turn off all LED strips
    turnOffStrips(strip1, 0, LEDS_PER_STRIP); // Turn off strip 1
    turnOffStrips(strip2, 0, LEDS_PER_STRIP); // Turn off strip 2
    turnOffStrips(strip3, 0, LEDS_PER_STRIP); // Turn off strip 3
    turnOffStrips(strip4, 0, LEDS_PER_STRIP); // Turn off strip 4
    turnOffStrips(strip5, 0, LEDS_PER_STRIP); // Turn off strip 5
  }

  // Add a small delay to avoid overwhelming the Arduino
  delay(10);
}

// Function to light up a strip of LEDs
void lightUpStrips(Adafruit_NeoPixel &strip, int startLed, int endLed) {
  for (int i = startLed; i < endLed; i++) {
    strip.setPixelColor(i, strip.Color(ledBrightness, 0, 0)); // Set LED to red
  }
  strip.show(); // Update the strip to show the new colors
}

// Function to turn off a strip of LEDs
void turnOffStrips(Adafruit_NeoPixel &strip, int startLed, int endLed) {
  for (int i = startLed; i < endLed; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // Set LED to off
  }
  strip.show(); // Update the strip to show the new colors
}