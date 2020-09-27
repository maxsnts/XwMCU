

#ifndef XwMcuM590_h
#define XwMcuM590_h

#include <Arduino.h>
#include "XwMcuATdevice.h"

//******************************************************************************
class XwMcuM590 : public XwMcuATdevice
{
    public:
        bool DisableEcho();
        bool SendSMS(String number, String content);
};

//******************************************************************************
bool XwMcuM590::DisableEcho()
{
    NextCommandTimeout = 2000;
    //if (SetCommand(F("AT+IPR=9600"), XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf(XW_AT_OK) != -1)
    //if (SetCommand(F("AT+IPR?"), XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf(XW_AT_OK) != -1)
    if (SetCommand(F("ATE0"), XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf(XW_AT_OK) == -1)
        return true;

    if (SetCommand(F("ATI"), XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf(XW_AT_OK) == -1)
        return true;

    return false;
}

//******************************************************************************
bool XwMcuM590::SendSMS(String number, String content)
{
    NextCommandTimeout = 2000;
    //if (SetCommand(F("AT+CPAS"), XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf(XW_AT_OK) == -1)
    //    return false;

    if (SetCommand(F("AT+CREG?"), XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf("+CREG: 0,1") == -1)
        return false;

    if (SetCommand(F("AT+CMGF=1"), XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf(XW_AT_OK) == -1)
        return false;

    delay(2000);
    if (SetCommand(F("AT+CSCS=\"GSM\""), XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf(XW_AT_OK) == -1)
        return false;
    
    delay(2000);
    if (SetCommand("AT+CMGS=\""+number+"\"", ">", XW_AT_FAIL, XW_AT_ERROR).indexOf(">") == -1)
        return false;

    delay(2000);
    if (SetCommand(content+"\x1A", XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf(XW_AT_OK) != -1)
        return true;
    
    return false;
}
      
//******************************************************************************
/*
void XwMcuM590::ReadSMS()
{
    byte index = 0;
    if(Serial2.available() >0)
    {
        for (int i=0; i <= 5; i++)
        {
            inchar = Serial2.read();
            insms[index] = inchar;
            index++;
            insms[index] = '\0';
        }
        return;
    }
}
*/
    
//******************************************************************************
/*
void XwMcuM590::ClearSMS()
{
    Serial2.print("AT+CMGF=1\r");  // set SMS mode to text
    delay(1000);
    
    Serial2.print("AT+CSCS=\"GSM\"");
    Serial2.print("\r");
    delay(1000);
    
    Serial2.print("AT+CMGF=1\r");  // set SMS mode to text
    delay(1000);
    
    // blurt out contents of new SMS upon receipt to the GSM shield's serial out
    Serial2.print("AT+CNMI=2,2,0,0,0\r"); 
    delay(1000);
    
    Serial2.println("AT+CMGD=1,4"); // delete all SMS
    delay(1000);  
}
*/

#endif
