
#include <Arduino.h>
#include <XwMcuRunningAverage.h>

int PulseInterruptPin = 19;
XwMcuRunningAverage avgPulseDuration(5);
unsigned long lastPulseTime;

//******************************************************************************
void onPulse()
{
    unsigned long now = millis();
    avgPulseDuration.Update(now - lastPulseTime);
    lastPulseTime = now;
}


//******************************************************************************
void setup()
{
    Serial.begin(9600);
    while (!Serial);

    Serial.println("### BOOTING... ###");
    pinMode(PulseInterruptPin, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(PulseInterruptPin), onPulse, FALLING);

    Serial.println("### ...BOOTED ###");
}

//******************************************************************************
void loop()
{
    double rmp = (double)60000 / avgPulseDuration.Get();
    Serial.println(rmp);
    delay(1000);
}
