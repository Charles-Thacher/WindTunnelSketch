#include <LiquidCrystal.h>

//LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
LiquidCrystal lcd(9, 8, 10, 11, 12, 13);      // put your pin numbers here

void setup()
  {
  int test = 420;
  lcd.begin(8, 2);  // 8 characters, 2 lines; the mode of operation
                    // Text████
                    // █Display
  lcd.print(test);  // prints the value of the variable
  lcd.print("m/s"); // Prints the text immediately after last line
  }

void loop() {
}