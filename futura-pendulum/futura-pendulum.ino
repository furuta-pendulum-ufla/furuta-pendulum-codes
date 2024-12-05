#include <ESP32Encoder.h>

bool alteraDirecao = false;
bool zona = false;
float tensaoAtual = 3;
bool paraControle = false;

void setup() {
  setupSystem();
  setupEncoderMotor();
  setupEncoderPendulo();
  setupMotor();
  tensaoMotor(0);
}

void loop() {
  float posPendulo = leituraEncoderPendulo();
  float posMotor = leituraEncoderMotor();

//  if (posMotor < 0 || posMotor > 90) {
//    if (!zona) {
//      alteraDirecao = true;
//    }
//    zona = true;
//  } else {
//    zona = false;
//  }
//
//  if (alteraDirecao) {
//    tensaoAtual = tensaoAtual * -1;
//    alteraDirecao = false;
//    tensaoMotor(tensaoAtual);
//  }

  Serial.println(posMotor);
}
