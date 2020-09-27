// XwMcuLibrary
// RotaryEncoder example

#include <Arduino.h>
#include <XwMcuRotaryEncoder.h>

// declare the Encoder
XwMcuRotaryEncoder encoder;

// this will be called when encoder is rotated
// it works both with interrupt or without them
void encoderRotatedLeft()
{
    Serial.println("rotated left");
}

// this will be called when encoder is rotated
// it works both with interrupt or without them
void encoderRotatedRight()
{
    Serial.println("rotated right");
}

// interrupt function for both phases
// this is the actual interrupt function
void encoderInterrupt()
{
    encoder.OnRotate(encoderRotatedLeft, encoderRotatedRight);
}

void setup()
{
    Serial.begin(9600);
    while(!Serial);

    Serial.println("### BOOTING... ###");

    // you don't need to use the interrupt pins
    // but lets face it, a encoder works best with them
    // without interrupt you are at the mercy of the loop time
    // param 1: phase A
    // param 2: phase B
    // param 3: pullup phase pins internally
    // (connect encoder to GND)
    encoder.Begin(3,4,true);

    // use with interrupt?
    // if not... remove this line and the function "encoderInterrupt"
    encoder.SetInterrupt(encoderInterrupt);

    // you can decrease the debounce check time
    // these will make the encoder more responsive
    // but you may get some bounce
    // this is not set in the "begin" method
    // because you may want to change it at runtime
    // default: (100 microseconds)
    encoder.DebounceTime(10000);

    Serial.println("### ...BOOTED ###");
}

void loop()
{
    // if not using interrupts, then you need to call this in the loop
    //encoder.OnRotate(encoderRotatedLeft, encoderRotatedRight);

    // the longer the loop takes to run
    // the worst it will be
    // if you can, just use the interrupts
    delay(5);
}
