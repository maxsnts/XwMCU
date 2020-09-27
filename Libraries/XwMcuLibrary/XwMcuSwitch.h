#ifndef XwMcuSwitch_h
#define XwMcuSwitch_h

#include <Arduino.h>

typedef void (*XwMcuSwitchCallback)();

//******************************************************************************
class XwMcuSwitch
{
    public:
        void Begin(byte pin, bool pullUp);
        void DebounceTime(long milliseconds);
        byte Changed();
        bool IsPressed();
        void OnChange(XwMcuSwitchCallback onPress, XwMcuSwitchCallback onRelease);

    private:
        byte Pin;
        bool PullUp;
        bool Status;   // current status
        bool On;       // is ON VCC or GND?
        unsigned long Time = 0;
        unsigned long DebounceTimeOut = 20000;
};

//******************************************************************************
void XwMcuSwitch::Begin(byte pin, bool pullUp)
{
    Pin = pin;
    PullUp = pullUp;
    Status = pullUp;
    On = (pullUp)?0:1;
    pinMode(Pin, (pullUp) ? INPUT_PULLUP : INPUT);
}

//******************************************************************************
void XwMcuSwitch::DebounceTime(long microseconds)
{
    DebounceTimeOut = microseconds;
}

//******************************************************************************
byte XwMcuSwitch::Changed()
{
    unsigned long T = micros();
    if(T > (Time + DebounceTimeOut))
    {
        Time = T;
        if (digitalRead(Pin) == On && Status != On)
        {
            Status = On;
            return 1;
        }
        else
        if (digitalRead(Pin) != On && Status == On)
        {
            Status = !On;
            return 2;
        }
    }
    return 0;
}

//******************************************************************************
void XwMcuSwitch::OnChange(XwMcuSwitchCallback onPress, XwMcuSwitchCallback onRelease)
{
  int st = Changed();
  if (st == 1)
    onPress();
  else if (st == 2)
    onRelease();
}

#endif
