#define PWM 5     // Arduino pin connected to PWM pin on 4-pin server fan
#define TACH 3

volatile float fanPulse = 0.0;
unsigned long lastmillis = 0;
float rpm = 0.0;

const long interval = 500; // milliseconds per fan speed measurement
const int pulsesPerRevolution = 2; // number of tachometer pulses per revolution
// can check by manually rotating fan??


void setup() {

  Serial.begin(9600); 
  Serial.print("\n"); // cause it's annoying to start printing on the bootup line

  // interrupt for fan speed calculation
  // number of counts for the fan's tachometer
  // useful for counting the RPM
  attachInterrupt(digitalPinToInterrupt(TACH), fanCount, RISING);

  // put your setup code here, to run once:
  pinMode(PWM, OUTPUT);
  pinMode(TACH, INPUT_PULLUP);

  digitalWrite(PWM, LOW);

  
  for (int i = 0; i < 2; i++) {
    Serial.println("Booting.");
    delay(1000);
  }

  fanSpeed(255);

  lastmillis = millis();

}

void loop() {
  // put your main code here, to run repeatedly:

  tachometer();




  // for (int speed = 0; speed <= 150; speed += 50) {
  //   fanSpeed(0);
  //     if (millis() - lastmillis >= interval) {
  //       tachometer();
  //     }
  //   delay(5000);
  // }


}

float tachometer() {

  if (millis() - lastmillis > interval) {
    // Calculate the speed of the fan
    noInterrupts(); // turn off interupts while transfering pulseCount
    float pulses = fanPulse;  // Copy value to prevent changes
    fanPulse = 0;  // Reset counter
    interrupts();

    rpm = (pulses*60.0)/(interval/1000.0)*(1.0/pulsesPerRevolution);

    lastmillis = millis();

    Serial.print("Pulses: ");
    Serial.print(pulses);
    Serial.print(", ");
    Serial.print("FanSpeed: ");
    Serial.println(rpm);

  }
  return rpm;
}

void fanCount() {
  // This function is called by attachInterrupt() whenever a transition is detected on the TACH pin 
  fanPulse += 1;
}

void fanSpeed(uint8_t speed) {
  // Sets speed of 4-pin fan by analogWriting a duty cycle, speed, to the PWM pin
  analogWrite(PWM, speed);
  // Serial.println("Fan speed set to " + String(speed));
}