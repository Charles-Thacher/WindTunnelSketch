#include "Adafruit_HX711.h"
#include <LiquidCrystal.h>

// Define the pins for the HX711 communication
const uint8_t DATA_PIN = 6;  // Can use any pins!
const uint8_t CLOCK_PIN = 5; // Can use any pins!

//LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
LiquidCrystal lcd(9, 8, 10, 11, 12, 13);      // put your pin numbers here

Adafruit_HX711 hx711(DATA_PIN, CLOCK_PIN);

void setup() {
  // 1. Connect to serial
  Serial.begin(115200);

  // wait for serial port to connect. Needed for native USB port only
  while (!Serial) {
    delay(10);
  }
  
  // 1. Set up LCD
  lcdSetUp();

  // 3. Set up Load Cell and hx711
  hx711.begin();

  // read and toss 3 values each
  Serial.println("Taring....");
  for (uint8_t t=0; t<3; t++) {
    hx711.tareA(hx711.readChannelRaw(CHAN_A_GAIN_128));
    hx711.tareA(hx711.readChannelRaw(CHAN_A_GAIN_128));
    hx711.tareB(hx711.readChannelRaw(CHAN_B_GAIN_32));
    hx711.tareB(hx711.readChannelRaw(CHAN_B_GAIN_32));
  }
  
} 

void loop() {
  // Read from Channel A with Gain 128, can also try CHAN_A_GAIN_64 or CHAN_B_GAIN_32
  // since the read is blocking this will not be more than 10 or 80 SPS (L or H switch)
  int32_t weightA128 = hx711.readChannelBlocking(CHAN_A_GAIN_128);
  Serial.print("Channel A (Gain 128): ");
  Serial.println(weightA128);

  // Print to the LCD
  lcd.setCursor(0,0); // first row, first column
  lcd.print("A ");
  lcd.print(weightA128);

  // Read from Channel A with Gain 128, can also try CHAN_A_GAIN_64 or CHAN_B_GAIN_32
  int32_t weightB32 = hx711.readChannelBlocking(CHAN_B_GAIN_32);
  Serial.print("Channel B (Gain 32): ");
  Serial.println(weightB32);

  // repeat prints to LCD
  lcd.setCursor(0,1); //second row, first column
  lcd.print("B ");
  lcd.print(weightB32);

  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("END LOOP");
  lcd.setCursor(0,1);
  lcd.print("END LOOP");
  delay(1000);
  lcd.clear();
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


// # Running tests here
// a running average function which takes the n most recent readings (determined with SIZE) and averages them
int runningAverage() {
  const int SIZE = 5; // number of readings that will be averaged

  // Initialize the array
  int runningArray[SIZE] = {}; // creates a 0 array with length SIZE

  int32_t latestValue = hx711.readChannelBlocking(CHAN_A_GAIN_128);

  // shift all elements in runningArray 1 position down
  for (int j = SIZE - 1; j > 0; j--) {
    runningArray[j] = runningArray[j - 1];
  }

  // append the latest value to the array
  runningArray[0] = latestValue;

  // average the array contents
  int32_t arraySum = 0;
  int32_t arrayAvg = 0;

  for (int i = 0; i < SIZE; i++) {
    arraySum += runningArray[i];
  }

  arrayAvg = arraySum/SIZE;

  Serial.println(arrayAvg);
  return arrayAvg;
}

// callibration

