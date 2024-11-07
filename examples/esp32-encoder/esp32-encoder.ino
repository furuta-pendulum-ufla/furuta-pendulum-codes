#include <ESP32Encoder.h>

#define ENCODER_GREEN_PIN 5
#define ENCODER_WHITE_PIN 18

ESP32Encoder encoder;

void setup() {
  Serial.begin(115200);
  
  pinMode(ENCODER_GREEN_PIN, INPUT_PULLUP);
  pinMode(ENCODER_WHITE_PIN, INPUT_PULLUP);

  encoder.attachFullQuad(ENCODER_GREEN_PIN, ENCODER_WHITE_PIN);
  encoder.clearCount();
}

void loop() {
  int32_t count = encoder.getCount();

  float degrees = (count / 600.0) * 360.0;

  Serial.print("Pulsos: ");
  Serial.print(count);
  Serial.print("\tRotação (graus): ");
  Serial.println(degrees);
}
