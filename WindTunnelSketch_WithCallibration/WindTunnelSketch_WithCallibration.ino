#include "HX711.h"
#include <LiquidCrystal.h>

// used the wrong library and switched to a different one; this just substitutes the keyword for now
HX711 hx711;

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
  lcdSetUp();

  // 2. Set up Load Cell and hx711
  hx711.begin(DATA_PIN, CLOCK_PIN);

  // 3. calibrate load cell
  calibrate();


} 

void loop() {
  float measurement = hx711.read_average(5);

  Serial.print(measurement);
  Serial.println("g");
  lcd.clear();
  lcd.setCursor(0,0);
  String lcdprint = String(measurement, 2) + "g";
  lcd.print(lcdprint);

}

void lcdSetUp() {
  lcd.begin(8, 2);  // 8 characters, 2 lines; the mode of operation. 
                    // How it looks:
                    
                    // Text████
                    // █Display

  lcd.print("Initiate");  // prints the value of the variable

  Serial.println("LCD Initialized.");
  
  // See the README on this sketch's GitHub repository for detailed wiring guide
  // https://github.com/Charles-Thacher/WindTunnelSketch
}


void  calibrate() {
  Serial.println("\n\nCALIBRATION\n===========");
  Serial.println("remove all weight from the loadcell");
  //  flush Serial input
  while (Serial.available()) Serial.read();

  Serial.println("and press enter\n");
  while (Serial.available() == 0);

  Serial.println("Determine zero weight offset");
  //  average measurements
  hx711.tare(AVERAGE_SAMPLES);
  int32_t offset = hx711.get_offset();

  Serial.print("OFFSET: ");
  Serial.println(offset);
  Serial.println();

  Serial.println("place a weight on the loadcell");
  //  flush Serial input
  while (Serial.available()) Serial.read();

  Serial.println("enter the weight in (whole) grams and press enter");
  uint32_t weight = 0;
  while (Serial.peek() != '\n')
  {
    if (Serial.available())
    {
      char ch = Serial.read();
      if (isdigit(ch))
      {
        weight *= 10;
        weight = weight + (ch - '0');
      }
    }
  }
  Serial.print("WEIGHT: ");
  Serial.println(weight);
  hx711.calibrate_scale(weight, 20);
  float scale = hx711.get_scale();

  Serial.print("SCALE:  ");
  Serial.println(scale, 6);

  Serial.print("\nuse scale.set_offset(");
  Serial.print(offset);
  Serial.print("); and scale.set_scale(");
  Serial.print(scale, 6);
  Serial.print(");\n");
  Serial.println("in the setup of your project");

  Serial.println("\n\n");
}