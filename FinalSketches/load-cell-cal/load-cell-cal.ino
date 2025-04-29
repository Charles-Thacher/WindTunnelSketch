#include "HX711.h"

HX711 hx;

const float CALIBRATION_WEIGHT = 500.0; // keep below load cell max
const int AVERAGE_SAMPLES = 10; // hx711 will average this number of samples

// Define the pins for the HX711 communication
const uint8_t DATA_PIN = 6;  // Can use any pins!
const uint8_t CLOCK_PIN = 5; // Can use any pins!

void setup() {
    // 1. Connect to serial
  Serial.begin(115200);

  // wait for serial port to connect. Needed for native USB port only
  while (!Serial) {
    delay(10);
  }

  hx.begin(DATA_PIN, CLOCK_PIN);

  // Load cell callibration
  hx.set_scale();


  while (Serial.available()) Serial.read(); // clear user inputs

  Serial.println("Clear all weight from load cell.\nPress enter to continue.");

  while (true) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == '\n' || c == '\r') {break;}
    }
  }

  hx.tare();

  Serial.println("Place 500g on the load cell.\nPress enter to continue.");

  while (true) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == '\n' || c == '\r') {break;}
    }
  }

  float units = hx.get_units(AVERAGE_SAMPLES);

  float set_factor = units / CALIBRATION_WEIGHT;

  hx.set_scale(set_factor);

  Serial.println("Unit: " + String(units, 20));
  Serial.println("Set factor is " + String(set_factor, 20));

}

void loop() {
  // Loop does nothing
}
