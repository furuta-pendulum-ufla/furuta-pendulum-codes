// Definição de pinos para RPWM e LPWM
const int pinoRPWM = 18;     // Pino de saída PWM para RPWM
const int pinoLPWM = 5;     // Pino de saída PWM para LPWM

// Definição da frequência, canal e resolução do PWM
const int freq = 5000;       // Frequência do PWM
const int canalRPWM = 0;     // Canal PWM para RPWM
const int canalLPWM = 1;     // Canal PWM para LPWM
const int resolucao = 8;     // Resolução do PWM (8 bits = 0 a 255)

float tensao;                // Variável de tensão (-12V a +12V)
int pwmValor;                // Valor do PWM (0 a 255)

// Função de setup
void setup() {
  // Configuração dos canais PWM no ESP32
  ledcAttach(pinoRPWM, freq, resolucao);
  // ledcAttachPin(pinoRPWM, canalRPWM);

  ledcAttach(pinoLPWM, freq, resolucao);
  // ledcAttachPin(pinoLPWM, canalLPWM);

  Serial.begin(115200);
}

void loop() {
  // Suponha que 'tensao' seja fornecida pelo sistema de controle e varia de -12V a +12V
  tensao = -12;/* Aqui você coloca o valor de entrada de -12 a +12 */;

  // Converte a tensão para um valor PWM
  if (tensao >= 0) {
    // Para tensões positivas, ativa RPWM e desativa LPWM
    pwmValor = map(tensao, 0, 12, 0, 255); // Mapeia 0 a 12V para 0 a 255
    ledcWrite(pinoRPWM, pwmValor);
    ledcWrite(pinoLPWM, 0);
  } else {
    // Para tensões negativas, ativa LPWM e desativa RPWM
    pwmValor = map(tensao, -12, 0, 255, 0); // Mapeia -12 a 0V para 255 a 0
    ledcWrite(pinoRPWM, 0);

    ledcWrite(pinoLPWM, pwmValor);
  }

  delay(100); // Aguarda um pouco antes de atualizar novamente
}
