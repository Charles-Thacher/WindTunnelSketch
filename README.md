# WindTunnelSketch
This repository stores the relevant Sketch files for the Wind Tunnel project created by Charles Thacher and Isiah Karitanyi as a part of their Senior Coda in Spring 2025.

# Libraries
Adafruit_HX711.h by Robert Tillart

LiquidCrystal.h - https://docs.arduino.cc/libraries/liquidcrystal/

# Credits
Evan Halstead, Project Advisor

Student Opportunity Fund, Skidmore College

# Wiring Guide
Connecting all 3 parts may be a tangled mess. It is reccommended to use a breadboard. These are just the "absolute" connections you must abide by, assuming the code on the Arduino sketch has not been altered. Ensure that the constants in the sketch match with the correct pins, in any case.

## LCD to Arduino
The LCD panel has 14 pins.

Pin 1, GND, is connected to GND on the Aruino. Pin 2, VDD, is connected to 5V on the Arduino.

Pin 3, V0, controls contrast and can be connected across a resistor to ground. A potentiometer may be connected, in which case wire the V0 to the center pin. Then, short it across the 3rd pin and connect the 1st pin to ground. [I think. Might be wrong.]

Pin 4, Register Select, on LCD is connected to digital pin 9 on Arduino.

Pin 5, Read/Write moded, on LCD is grounded to always be in write mode.

Pin 6, Enable, is connected to digital pin 8.

Data pins 11-14 on the LCD are connected to the 10-13 digital pins on the Arduino.

All other LCD pins unused.

Pins mmust be defined and changed in sketch.

## HX711 to Arduino
E+ wired to strain gauge red wire
E- wired to strain gauge black wire
A+ wired to strain gauge green wire
A- wired to strain gauge white wire

HX711 VCC to Arduino VCC
HX711 GND to Arduino GND
HX711 DT to Arduino 6 (customizable)
HX711 SCK to Arduino 5 (customizable)

## Server fan to Arduino
Reference: There are two rails on the 4 prong connector for the Artic fan positioned assymetrically. This wiring guide assumes you are looking at the connector so this feature is on the LEFT. Pins are numbered 1 to 4 from left to right.

Pin 1, GND, is connected to the Arduino GND.

Pin 2, +12V DC, must be connected to a separate power source. The power source must be grounded in common with the Arduino.

Pin 3,Tachometer, connects to the 2nd pin on the Arduino. A 1M Ohm resistor is used as a pull up resistor between the tachometer pin and the 12V power.

Pin 4, PWM, is connected to a valid Arudino pwm ~ pin, in this case pin 3.
