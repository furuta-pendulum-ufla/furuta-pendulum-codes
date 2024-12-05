#define ENCODER_MOTOR_PIN_A 32
#define ENCODER_MOTOR_PIN_B 33

#define ENCODER_PENDULO_PIN_A 26
#define ENCODER_PENDULO_PIN_B 27

ESP32Encoder encoderMotor;
ESP32Encoder encoderPendulo;

void setupEncoderMotor() {
  pinMode(ENCODER_MOTOR_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER_MOTOR_PIN_B, INPUT_PULLUP);
  
  encoderMotor.attachFullQuad(ENCODER_MOTOR_PIN_A, ENCODER_MOTOR_PIN_B);
  encoderMotor.clearCount(); // Zera a contagem inicial

}

void setupEncoderPendulo() {
  pinMode(ENCODER_PENDULO_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER_PENDULO_PIN_B, INPUT_PULLUP);
  
  // Define os pinos do encoder
  encoderPendulo.attachFullQuad(ENCODER_PENDULO_PIN_A, ENCODER_PENDULO_PIN_B);
  encoderPendulo.clearCount(); // Zera a contagem inicial
  //encoderPendulo.setCount(180/0.15);

  
}

float leituraEncoderMotor() {
  // Obtém a contagem atual do encoder
  float count = encoderMotor.getCount() * 0.15 * 0.16;

  if (count > 360) {
    count = fmod(count, 360.0);
  }

  if (count > 180) {
    count -= 360; // [-180, 180]
  }

  else if (count < -180.0) {
    count += 360; // [-180, 180]
  }

  return count;
}

float leituraEncoderPendulo() {
  // Obtém a contagem atual do encoder
  float count = encoderPendulo.getCount() * 0.15 ;

  if (count > 360) {
    count = fmod(count, 360.0);
  }

  if (count > 180) {
    count -= 360; // [-180, 180]
  }

  else if (count < -180) {
    count += 360; // [-180, 180]
  }

  return count;
}
