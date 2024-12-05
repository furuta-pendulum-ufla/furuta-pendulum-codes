const int freq = 5000;       // Frequência do PWM
const int canalRPWM = 0;     // Canal PWM para RPWM
const int canalLPWM = 1;     // Canal PWM para LPWM
const int resolucao = 8;     // Resolução do PWM (8 bits = 0 a 255)
const int pinoRPWM = 18;     // Pino de saída PWM para RPWM
const int pinoLPWM = 19;     // Pino de saída PWM para LPWM

void setupMotor() {
  // Configuração dos canais PWM no ESP32
  ledcAttach(pinoRPWM, freq, resolucao);
  // ledcAttachPin(pinoRPWM, canalRPWM);

  ledcAttach(pinoLPWM, freq, resolucao);
  // ledcAttachPin(pinoLPWM, canalLPWM);
}

void tensaoMotor(int tensao) {
  int pwmValor;

  if (tensao >= 0) {
    // Para tensões positivas, ativa RPWM e desativa LPWM
    // Mapeia 0 a 12V para 0 a 255
    pwmValor = map(tensao, 0, 12, 0, 255);
    ledcWrite(pinoRPWM, pwmValor);
    ledcWrite(pinoLPWM, 0);
  } else {
    // Para tensões negativas, ativa LPWM e desativa RPWM
    // Mapeia -12 a 0 para 255 a 0
    pwmValor = map(tensao, -12, 0, 255, 0); // Mapeia -12 a 0V para 255 a 0
    ledcWrite(pinoRPWM, 0);
    ledcWrite(pinoLPWM, pwmValor);
  }

}
