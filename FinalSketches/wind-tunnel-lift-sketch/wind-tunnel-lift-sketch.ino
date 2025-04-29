// See the README on this sketch's GitHub repository for detailed wiring guide
// https://github.com/Charles-Thacher/WindTunnelSketch

#include "HX711.h"
#include <LiquidCrystal.h>

// used the wrong library and switched to a different one; this just substitutes the keyword for now
HX711 hx;

// Define the pins for the HX711 communication
const uint8_t DATA_PIN = 6;  // Can use any pins!
const uint8_t CLOCK_PIN = 5; // Can use any pins!
// pins for fan
const uint8_t TACH_PIN = 2;
const uint8_t PWM_PIN = 3; // pins for server fan


// wind speed constants
const uint8_t SET_SPEED = 150; // PWM: set speed of fan from 0 to 255
const float WIND_ZERO = 0.1050; // use "fitWindSpeed.m" to find
const float WIND_SLOPE = 0.1500; // use "fitWindSpeed.m" to find


// load cell calibration constants
float LOAD_CELL_SET = 1.0; // generate with "load-cell-cal.ino"
float GRAVITY = 9.81; // gravity of Earth; m/s^2


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

  // 2. Set up Load Cell and calibrate
  hx.begin(DATA_PIN, CLOCK_PIN);
  hx.set_scale(LOAD_CELL_SET);

  // 3. Set the fan speed
  analogWrite(SET_SPEED, PWM_PIN);

} 

void loop() {
  long mass_offset = hx.get_units();
  // do some math here to convert to Newtons
  float lift = mass_offset*GRAVITY;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String(lift, 2) + "N");
  Serial.println(lift);

  float current_wind_speed = pwm_speed(SET_SPEED);
  lcd.setCursor(1,0);
  lcd.print(String(current_wind_speed) + "m/s");

  delay(1000);
  
}

void lcd_set_up() {
  lcd.begin(8, 2);  // 8 characters, 2 lines; the mode of operation. 
                    // How it looks:
                    
                    // Text████
                    // █Display

  lcd.setCursor(0, 0);
  lcd.print("Initiate");  // prints the value of the variable

  delay(5000);
  lcd.clear();
  Serial.println("LCD Initialized.");

}

float pwm_speed(float set_speed) {
  // calculates the wind speed based off a best fit function
  // constants determined using MATLAB script in repo
  float wind_speed = WIND_SLOPE*set_speed + WIND_ZERO;

  return wind_speed;
}


