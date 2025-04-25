#include "HX711.h"
#include <LiquidCrystal.h>

// used the wrong library and switched to a different one; this just substitutes the keyword for now
HX711 hx;

// Define the pins for the HX711 communication
const uint8_t DATA_PIN = 6;  // Can use any pins!
const uint8_t CLOCK_PIN = 5; // Can use any pins!

const float CALIBRATION_WEIGHT = 500.0; // keep below load cell max
const int AVERAGE_SAMPLES = 10; // hx711 will average this number of samples


//LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
LiquidCrystal lcd(9, 8, 10, 11, 12, 13);      // put your pin numbers here


void setup() {
  // 1. Connect to serial
  Serial.begin(115200);

  // wait for serial port to connect. Needed for native USB port only
  while (!Serial) {
    delay(10);
  }
  
  // 1. Set up LCD
  lcd_set_up();

  // 2. Set up Load Cell and hx711
  hx711.begin(DATA_PIN, CLOCK_PIN);

  // 3. calibrate load cell
  load_cell_calibrate();


} 

void loop() {
  float measurement = hx.get_units();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String(measurement, 2)+"raw");
  
}

void lcd_set_up() {
  lcd.begin(8, 2);  // 8 characters, 2 lines; the mode of operation. 
                    // How it looks:
                    
                    // Text████
                    // █Display

  lcd.print("Initiate");  // prints the value of the variable

  Serial.println("LCD Initialized.");
  
  // See the README on this sketch's GitHub repository for detailed wiring guide
  // https://github.com/Charles-Thacher/WindTunnelSketch
}


void  load_cell_calibrate() {
  hx.set_scale();

  while (Serial.available() Serial.read()); // clear user inputs

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
}