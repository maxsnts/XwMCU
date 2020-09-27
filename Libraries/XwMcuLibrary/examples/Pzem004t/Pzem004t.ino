// XwMcuLibrary

//PZEM 004T Energy Meter example

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <XwMcuPzem004T.h>

SoftwareSerial softSerial(5,6);
XwMcuPzem004T pzem;

void setup()
{
    Serial.begin(9600);
    while (!Serial);
    softSerial.begin(9600);
    while (!softSerial);

    Serial.println("### BOOTING... ###");

    pzem.Begin(&softSerial);
    pzem.SetAddress();

    Serial.println("### ...BOOTED ###");
}

void loop()
{
    Serial.print(pzem.GetVoltage());
    Serial.println("V");

    Serial.print(pzem.GetEnergy());
    Serial.println("Kwh");

    Serial.print(pzem.GetPower());
    Serial.println("Kw");

    Serial.print(pzem.GetCurrent());
    Serial.println("A");

    delay(10000);
}
