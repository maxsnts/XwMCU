// Simple class to handle communication with generic AT devices

#ifndef XwMcuATdevice_h
#define XwMcuATdevice_h

#include <Arduino.h>
#include <SoftwareSerial.h>

#define XW_AT_COMMAND_DEFAULT_TIMEOUT 30000

// common response markers
#define XW_AT_OK F("OK")
#define XW_AT_FAIL F("FAIL")
#define XW_AT_ERROR F("ERROR")
#define XW_AT_ready F("ready")


//******************************************************************************
class XwMcuATdevice
{
    public:
        void Begin(HardwareSerial *serial, byte enablePin, bool ShowDebug = false);
        void Begin(SoftwareSerial *serial, byte enablePin, bool ShowDebug = false);
        String SetCommand(String command, String check1="", String check2="", String check3="", String check4="");
        void Enable();
        void Disable();
        uint32_t NextCommandTimeout = XW_AT_COMMAND_DEFAULT_TIMEOUT;
    private:
        Stream *SerialPort = NULL;
         bool IsSoftwareSerial;
        byte EnablePin = 255;
        String GetResponse(String check1="", String check2="", String check3="", String check4="");
        bool Debug = true;
};

//******************************************************************************
void XwMcuATdevice::Begin(HardwareSerial *serial, byte enablePin, bool ShowDebug)
{
    SerialPort = serial;
    EnablePin = enablePin;
    pinMode(EnablePin, OUTPUT);
    IsSoftwareSerial = false;
    Debug = ShowDebug;
}

//******************************************************************************
void XwMcuATdevice::Begin(SoftwareSerial *serial, byte enablePin, bool ShowDebug)
{
    SerialPort = serial;
    EnablePin = enablePin;
    pinMode(EnablePin, OUTPUT);
    IsSoftwareSerial = true;
    Debug = ShowDebug;
}

//******************************************************************************
String XwMcuATdevice::SetCommand(String command, String check1, String check2, String check3, String check4)
{
    if (Debug)
        Serial.println(command);
    SerialPort->println(command);
    String a = GetResponse(check1, check2, check3, check4);
    if (Debug)
        Serial.println(a);
    return a;
}

//******************************************************************************
String XwMcuATdevice::GetResponse(String check1, String check2, String check3, String check4)
{
    if (IsSoftwareSerial)
        ((SoftwareSerial*)SerialPort)->listen();
    
    String data;
    char a;
    unsigned long start = millis();
    while (millis() - start < NextCommandTimeout)
    {
        if(SerialPort->available() > 0)
        {
            a = SerialPort->read();
            if(a == '\0') continue;
            data += a;
        }
        yield();
        
        if ((check1!="" && data.indexOf(check1) != -1) ||
            (check2!="" && data.indexOf(check2) != -1) ||
            (check3!="" && data.indexOf(check3) != -1) ||
            (check4!="" && data.indexOf(check4) != -1) )
            break;
    }
    NextCommandTimeout = XW_AT_COMMAND_DEFAULT_TIMEOUT;
    return data;
}

//******************************************************************************
void XwMcuATdevice::Enable()
{
    digitalWrite(EnablePin, HIGH);
}

//******************************************************************************
void XwMcuATdevice::Disable()
{
    digitalWrite(EnablePin, LOW);
}

#endif
