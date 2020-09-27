#ifndef XwMcuRotaryEncoder_h
#define XwMcuRotaryEncoder_h

#include <Arduino.h>

typedef void (*XwMcuRotaryEncoderCallback)();

//******************************************************************************
class XwMcuRotaryEncoder
{
  public:
    void Begin(byte pinA, byte pinB, bool pullUp);
    void DebounceTime(long milliseconds);
    void OnRotate(XwMcuRotaryEncoderCallback left, XwMcuRotaryEncoderCallback right);
    void SetInterrupt(XwMcuRotaryEncoderCallback intr);

  private:
    byte PinA;
    byte PinB;
    bool PullUp;
    bool UseInterrupt;
    char Encoder_A;
    char Encoder_B;
    char Encoder_A_prev;
    unsigned long Time = 0;
    unsigned long DebounceTimeOut = 100;
    XwMcuRotaryEncoderCallback OnLeft;
    XwMcuRotaryEncoderCallback OnRight;
};

//******************************************************************************
void XwMcuRotaryEncoder::Begin(byte pinA, byte pinB, bool pullUp)
{
    PinA = pinA;
    PinB = pinB;
    PullUp = pullUp;
    UseInterrupt = false;
    Encoder_A_prev = 0;
    pinMode (PinA, (pullUp) ? INPUT_PULLUP : INPUT);
    pinMode (PinB, (pullUp) ? INPUT_PULLUP : INPUT);
}

//******************************************************************************
void XwMcuRotaryEncoder::DebounceTime(long microseconds)
{
    DebounceTimeOut = microseconds;
}

//******************************************************************************
void XwMcuRotaryEncoder::OnRotate(XwMcuRotaryEncoderCallback left, XwMcuRotaryEncoderCallback right)
{
    unsigned long T = micros();
    if(T >= (Time + DebounceTimeOut))
    {
        Time = T;
        Encoder_A = digitalRead(PinA);
        Encoder_B = digitalRead(PinB);
        if((!Encoder_A) && (Encoder_A_prev))
        {
            if(Encoder_B)
            {
                right();
            }
            else
            {
                left();
            }
        }
        Encoder_A_prev = Encoder_A;
    }
}

//******************************************************************************
void XwMcuRotaryEncoder::SetInterrupt(XwMcuRotaryEncoderCallback intr)
{
    attachInterrupt (0, intr, CHANGE);
    attachInterrupt (1, intr, CHANGE);
    UseInterrupt = true;
}

#endif
