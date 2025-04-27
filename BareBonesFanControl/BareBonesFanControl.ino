#define PWM 5     // Arduino pin connected to PWM pin on 4-pin server fan
#define TACH 3


void setup() {

  Serial.begin(9600); 
  Serial.print("\n"); // cause it's annoying to start printing on the bootup line
  Serial.println("Begin setup");

  // callibrateSpeed();

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

  fanSpeed(150);

  lastmillis = millis();

}

void loop() {
  // put your main code here, to run repeatedly:

  tachometer();

}


void fanSpeed(uint8_t speed) {
  // Sets speed of 4-pin fan by analogWriting a duty cycle, speed, to the PWM pin
  analogWrite(PWM, speed); // write "speed" to "PWM"
  // Serial.println("Fan speed set to " + String(speed));
}

void callibrateSpeed() {
  Serial.println("Begin callibration. User must measure wind speed and input these values.");

  for (int i = 0; i < points; i++) {
    int writePWM = pwmLevels[i]; // iterate over points times; PWM set to 
    fanSpeed(writePWM);

    Serial.print("PWM set to ");
    Serial.print(writePWM);
    Serial.println(". Measure current speed and enter value: ");

    while (Serial.available() == 0) {
      // wait for user
    }

    inputSpeed[i] = Serial.parseInt();
    Serial.print("Recorded speed at PWM ");
    Serial.print(writePWM);
    Serial.print(": ");
    Serial.println(inputSpeed[i]);
  }

  fanSpeed(0);
  Serial.println("Callibration finished.");
  Serial.println("Callibration points:");
  Serial.println("inputSpeed");
}