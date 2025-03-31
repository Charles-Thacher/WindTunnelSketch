#define PWM 3     // Arduino pin connected to PWM pin on 4-pin server fan
#define TACH 5

volatile fanpulse = 0;
unsigned long lastMillis = 0;

const int measureInterval = 5000; // milliseconds per fan speed measurement
const int pulsesPerRevolution = 2; // number of tachometer pulses per revolution
// can check by manually rotating fan??

void setup() {

  Serial.begin(9600);
    Serial.print("\n"); // cause it's annoying to start printing on the bootup line

  // interrupt for fan speed calculation
  // number of counts for the fan's tachometer
  // useful for counting the RPM
  attacchInterrupt(digitalPinToInterrupt(TACH), fanCount, RISING);

  // put your setup code here, to run once:
  pinMode(PWM, OUTPUT);
  pinMode(TACH, INPUT_PULLUP);

  digitalWrite(PWM, LOW);

  
  for (int i = 0; i < 5; i++) {
    Serial.println("Booting.");
    delay(1000);
  }

  lastMillis = millis();

}

void loop() {
  // put your main code here, to run repeatedly:

  for (int speed = 0; speed <= 150; speed += 50) {
  fanSpeed(speed);
  if (millis() - lastMillis >= measureInterval) {
    tachometer();
  }
  delay(5000);
  }

}

void tachometer() {
  if (millis() - lastMillis > measureInternval;) {
    // Calculate the speed of the fan
    noInterrupts(); // turn off interupts while transfering pulseCount
    int pulses = pulseCount;  // Copy value to prevent changes
    pulseCount = 0;  // Reset counter
    interrupts();

    float rpm = (pulses*60.0)/(interval/1000.0)/pulsesPerRevolution;
    Serial.print("Fan Speed: ");
    Serial.print(rpm);
    Serial.println(" RPM");

    lastMillis = millis();
  }
}

void fanCount() {
  // This function is called by attachInterrupt() whenever a transition is detected on the TACH pin 
  fanPulse +=;
}

void fanSpeed(uint8_t speed) {
  // Sets speed of 4-pin fan by analogWriting a duty cycle, speed, to the PWM pin
  analogWrite(PWM, speed);
  Serial.println("Fan speed set to " + String(speed));
}