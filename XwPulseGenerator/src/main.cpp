
#include <Arduino.h>

#define PULSE_PIN 13
#define PULSE_INTERVAL 1000
#define PULSE_WIDTH 10
#define PULSE_COMPENSATION 1

void setup()
{
  pinMode(PULSE_PIN, OUTPUT);
}

void loop()
{
  digitalWrite(PULSE_PIN, HIGH);
  delay(PULSE_WIDTH);
  digitalWrite(PULSE_PIN, LOW);
  delay(PULSE_INTERVAL - PULSE_WIDTH - PULSE_COMPENSATION);
  delayMicroseconds(8);
}
