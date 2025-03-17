# WindTunnelSketch
This repository stores the relevant Sketch files for the Wind Tunnel project created by Charles Thacher and Isiah Karitanyi as a part of their Senior Coda in Spring 2025.

# Libraries
Adafruit_HX711.h

LiquidCrystal.h - https://docs.arduino.cc/libraries/liquidcrystal/

# Credits
Evan Halstead, Project Advisor

Student Opportunity Fund, Skidmore College

# Wiring Guide
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

