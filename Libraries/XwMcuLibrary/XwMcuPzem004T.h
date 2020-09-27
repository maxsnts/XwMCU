#ifndef XwMcuPzem004T_h
#define XwMcuPzem004T_h

#include <Arduino.h>
#include <IPAddress.h>
#include <SoftwareSerial.h>

#define XW_PZEM_CMD_TIMEOUT 1000
#define XW_PZEM_DATA_SIZE 7

//******************************************************************************
class XwMcuPzem004T
{
    public:
        void Begin(HardwareSerial *serial, bool ShowDebug = false, String addr = "192.169.1.1");
        void Begin(SoftwareSerial *serial, bool ShowDebug = false, String addr = "192.169.1.1");
        bool SetAddress();
        float GetVoltage();
        float GetPower();
        float GetEnergy();
        float GetCurrent();
    private:
        Stream *SerialPort = NULL;
        IPAddress deviceAddr;
        bool IsSoftwareSerial;
        uint32_t NextCommandTimeout = XW_PZEM_CMD_TIMEOUT;
        byte Checksum(byte *data, byte len);
        void SetCommand(byte command);
        bool GetCommand(byte *data);
        bool Debug = false;
};

//******************************************************************************
void XwMcuPzem004T::Begin(HardwareSerial *serial, bool ShowDebug, String addr)
{
    deviceAddr.fromString(addr);
    SerialPort = serial;
    IsSoftwareSerial = false;
    Debug = ShowDebug;
}

//******************************************************************************
void XwMcuPzem004T::Begin(SoftwareSerial *serial, bool ShowDebug, String addr)
{
    deviceAddr.fromString(addr);
    SerialPort = serial;
    IsSoftwareSerial = true;
    Debug = ShowDebug;
}

//******************************************************************************
bool XwMcuPzem004T::SetAddress()
{
    SetCommand(0xB4);
    byte data[XW_PZEM_DATA_SIZE];
    return GetCommand(data);
}

//******************************************************************************
float XwMcuPzem004T::GetVoltage()
{
    SetCommand(0xB0);
    byte data[XW_PZEM_DATA_SIZE]; 
    if (GetCommand(data))
        return (data[1] << 8) + data[2] + (data[3] / 10.0);
    else
        return -1;
}
        
//******************************************************************************
float XwMcuPzem004T::GetPower()
{
    SetCommand(0xB2);
    byte data[XW_PZEM_DATA_SIZE]; 
    if (GetCommand(data))
        return (data[1] << 8) + data[2];
    else
        return -1;
}
  
//******************************************************************************
float XwMcuPzem004T::GetEnergy()
{
    SetCommand(0xB3);
    byte data[XW_PZEM_DATA_SIZE]; 
    if (GetCommand(data))
        return ((uint32_t)data[1] << 16) + ((uint16_t)data[2] << 8) + data[3];
    else
        return -1;
}

//******************************************************************************
float XwMcuPzem004T::GetCurrent()
{
    SetCommand(0xB1);
    byte data[XW_PZEM_DATA_SIZE]; 
    if (GetCommand(data))
        return (data[1] << 8) + data[2] + (data[3] / 100.0);
    else
        return -1;
}

//******************************************************************************
void XwMcuPzem004T::SetCommand(byte command)
{
    byte data[XW_PZEM_DATA_SIZE];
    data[0] = command;
    memcpy(&data[1], &deviceAddr[0], 4);
    data[5] = 0x00;
    data[6] = Checksum(data, XW_PZEM_DATA_SIZE-1);
    SerialPort->write(data, XW_PZEM_DATA_SIZE);
    
    if (Debug)
    {
        Serial.print("\n---- SetCommand ----\n");
        for(int n=0; n<XW_PZEM_DATA_SIZE ; n++)
        {
            Serial.print(data[n], HEX);
            Serial.print(" ");
        }
        Serial.print("\n--------------------\n");
    }
}

//******************************************************************************
bool XwMcuPzem004T::GetCommand(byte *data)
{
    if (IsSoftwareSerial)
        ((SoftwareSerial*)SerialPort)->listen();
        
    int index = 0;
    unsigned long start = millis();
    while (index < XW_PZEM_DATA_SIZE && (millis() - start < NextCommandTimeout))
    {
        if(SerialPort->available() > 0)
            data[index++] = (byte)SerialPort->read();
        yield();
    }

    if (Debug)
    {
        Serial.print("\n---- GetCommand ----\n");
        for(int n=0; n<XW_PZEM_DATA_SIZE ; n++)
        {
            Serial.print(data[n], HEX);
            Serial.print(" ");
        }
        Serial.print("\n--------------------\n");
    }

    if(data[XW_PZEM_DATA_SIZE-1] != Checksum(data, XW_PZEM_DATA_SIZE-1))
        return false;

    return true;    
}

//******************************************************************************
byte XwMcuPzem004T::Checksum(byte *data, byte len)
{
    uint16_t sum = 0;
    for(byte i=0; i<len; i++)
        sum += *data++;
    return (byte)(sum & 0xFF);
}

#endif
