#define L_PWM_PIN 5
#define R_PWM_PIN 18
#define H_BRIDGE_FREQUENCY 5000
#define H_BRIDGE_RESOLUTION 12

int motorDutyCycle = 0;

void setup() {
  Serial.begin(115200);

  ledcAttach(L_PWM_PIN, H_BRIDGE_FREQUENCY, H_BRIDGE_RESOLUTION);
  ledcAttach(R_PWM_PIN, H_BRIDGE_FREQUENCY, H_BRIDGE_RESOLUTION);
}

void loop() {
  if (Serial.available() > 0) {
    int newMotorDutyCycle = Serial.parseInt();
    if (newMotorDutyCycle != 0) {
      motorDutyCycle = newMotorDutyCycle;
    }
  }
  motorControl(motorDutyCycle);
  Serial.println(motorDutyCycle);
  delay(100);
}

void controlMotor(int value) {
  if (value > 0) {
    ledcWrite(L_PWM_PIN, value);
    ledcWrite(R_PWM_PIN, 0);
  } else {
    value = -value;
    ledcWrite(L_PWM_PIN, 0);
    ledcWrite(R_PWM_PIN, value);
  }
}
