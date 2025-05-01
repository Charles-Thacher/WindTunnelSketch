// See the README on this sketch's GitHub repository for detailed wiring guide
// https://github.com/Charles-Thacher/WindTunnelSketch

// Calibration values
// PWM:         10 , 50,  100, 150, 200
// Middle SPD:  1.0, 2.5, 3.6, 4.4, 5.3

// End Spd:     , , 4.9, ,
// Front SPD:   , , 1.4, ,
#define PWM_PIN 3
#define TACH_PIN 2

#include "HX711.h"
#include <LiquidCrystal.h>

// used the wrong library and switched to a different one; this just substitutes the keyword for now
HX711 hx;

// Define the pins for the HX711 communication
const uint8_t DATA_PIN = 6;  // Can use any pins!
const uint8_t CLOCK_PIN = 5; // Can use any pins!
// pins for fan
//const uint8_t TACH_PIN = 2;
//const uint8_t PWM_PIN = 3; // pins for server fan


// wind speed constants
const uint8_t SET_SPEED = 250; // PWM: set speed of fan from 0 to 255
const float WIND_ZERO = 1.1441; // use "fitWindSpeed.m" to find
const float WIND_SLOPE = 0.021724; // use "fitWindSpeed.m" to find


// load cell calibration constants
float LOAD_CELL_SCALE = -751.710; // generate with "load-cell-cal.ino"
float LOAD_CELL_OFFSET = 273818.000;
float GRAVITY = -9.81; // gravity of Earth; m/s^2


//LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
LiquidCrystal lcd(9, 8, 10, 11, 12, 13);      // put your pin numbers here


void setup() {
  // 1. Connect to serial
  Serial.begin(115200);

  // wait for serial port to connect. Needed for native USB port only
  while (!Serial) {
    delay(10);
  }

  // 0. Pin Modes
  pinMode(PWM_PIN, OUTPUT);
  pinMode(TACH_PIN, INPUT_PULLUP);
  
  // 1. Set up LCD
  lcd_set_up();

  // 2. Set up Load Cell and calibrate
  hx.begin(DATA_PIN, CLOCK_PIN);
  hx.tare();
  
  hx.set_offset(LOAD_CELL_OFFSET);
  hx.set_scale(LOAD_CELL_SCALE);

  // 3. Set the fan speed
  analogWrite(PWM_PIN, SET_SPEED);
  Serial.println("End setup.");
  Serial.println();

} 

void loop() {
  Serial.print("Loop");
  Serial.println();

  float mass_offset = hx.get_units();
  // do some math here to convert to Newtons
  float kilograms = mass_offset*(1.0/1000.0);
  Serial.println("Mass: " + String(kilograms) + "kg");

  float lift = (mass_offset/1000.0)*GRAVITY;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String(lift, 2) + "N");
  Serial.println("LIFT: " + String(lift,2));

  float current_wind_speed = pwm_speed(SET_SPEED);
  lcd.setCursor(0, 1);
  lcd.print(String(current_wind_speed) + "m/s");
  Serial.println(String(current_wind_speed) + "m/s");
  delay(1000);
  lcd.clear();

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


