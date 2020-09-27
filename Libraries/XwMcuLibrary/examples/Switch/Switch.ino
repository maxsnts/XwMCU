// XwMcuLibrary
// Switch example

#include <Arduino.h>
#include <XwMcuSwitch.h>

// declare the Button
XwMcuSwitch button;

// if you are using "onChange"
// this will be called on Button ON
void buttonON()
{
    Serial.println("buttonON");
}

// if you are using "onChange"
// this will be called on Button OFF
void buttonOFF()
{
    Serial.println("buttonOFF");
}

void setup()
{
    Serial.begin(9600);
    while(!Serial);

    Serial.println("### BOOTING... ###");

    // initializes switch
    // first param: digital pin
    // second param: pullup pin internally
    // (if true button will be ON when connected to GND)
    button.Begin(6, true);

    // you can decrease the debounce check time
    // these will make the switch more responsive
    // but you may get some bounce
    // this is not set in the "begin" method
    // because you may want to change it at runtime
    // default: 20 milliseconds (20000 microseconds)
    button.DebounceTime(10000);

    Serial.println("### ...BOOTED ###");
}

void loop()
{
    // if you want to use callbacks
    button.OnChange(buttonON, buttonOFF);

    // if you want yo use it inline
    // 0=No Change, 1=ON, 2=OFF
    // 0 is "no change" so that we can do this -> "if (!button.changed())"
    /*
    switch(button.Changed())
    {
        case 1:
            Serial.println("buttonON");
            break;
        case 2:
            Serial.println("buttonOFF");
            break;
    }
    */
}
