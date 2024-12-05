#include <ESP32Encoder.h>

// Definições de pinos do motor e encoder
#define L_PWM_PIN 25
#define R_PWM_PIN 26
#define ENCODER_GREEN_PIN 5
#define ENCODER_WHITE_PIN 18
#define H_BRIDGE_FREQUENCY 5000
#define H_BRIDGE_RESOLUTION 12

// Instância do encoder
ESP32Encoder encoder;

// Controle PID
double kp = 2.0, ki = 0.0, kd = 0.5; // Ganhos PID
double targetAngle = 0.0;           // Ângulo de equilíbrio (0 graus)
double previousError = 0.0;
double integral = 0.0;

// Variáveis do motor
int motorDutyCycle = 0;

void setup() {
  // Configuração do encoder
  pinMode(ENCODER_GREEN_PIN, INPUT_PULLUP);
  pinMode(ENCODER_WHITE_PIN, INPUT_PULLUP);
  encoder.attachFullQuad(ENCODER_GREEN_PIN, ENCODER_WHITE_PIN);
  encoder.clearCount();

  // Configuração do PWM para o motor
  ledcSetup(0, H_BRIDGE_FREQUENCY, H_BRIDGE_RESOLUTION);
  ledcSetup(1, H_BRIDGE_FREQUENCY, H_BRIDGE_RESOLUTION);
  ledcAttachPin(L_PWM_PIN, 0);
  ledcAttachPin(R_PWM_PIN, 1);
}

void loop() {
  // Leitura do ângulo do pêndulo (em graus)
  double currentAngle = readAngle();

  // Cálculo do erro (diferença entre o ângulo atual e o alvo)
  double error = targetAngle - currentAngle;

  // Controle PID
  integral += error;
  double derivative = error - previousError;
  motorDutyCycle = kp * error + ki * integral + kd * derivative;

  // Saturação do duty cycle
  motorDutyCycle = constrain(motorDutyCycle, -4095, 4095);

  // Controle do motor
  controlMotor(motorDutyCycle);

  // Atualização do estado
  previousError = error;
}

// Função para controle do motor
void controlMotor(int value) {
  if (value > 0) {
    ledcWrite(0, value);
    ledcWrite(1, 0);
  } else {
    value = -value;
    ledcWrite(0, 0);
    ledcWrite(1, value);
  }
  Serial.println(value);
}

// Função para leitura do ângulo usando o encoder
double readAngle() {
  int32_t count = encoder.getCount();
  return (count / 600.0) * 360.0; // Conversão de pulsos para graus
}
