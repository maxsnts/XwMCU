// Simple class to handle the simple client operations of a WiFi module
// Only does GET at the moment
// Tested with:
// * ESP-01 (8266)

#ifndef XwMcuEsp8266_h
#define XwMcuEsp8266_h

#include <Arduino.h>
#include <XwMcuATdevice.h>

//******************************************************************************
class XwMcuEsp8266 : public XwMcuATdevice
{
    public:
        bool Reset();
        bool DisableEcho();
        bool GetVersion(String *result);
        bool SetAsStation();
        bool ListAPs(String *result);
        bool Connect(String apName, String password);
        bool GetIP(String *result);
        bool Disconnect();
        bool GetRequest(String *result, String host, uint16_t port, String url);
};

//******************************************************************************
bool XwMcuEsp8266::Reset()
{
    NextCommandTimeout = 2000;
    String result = SetCommand(F("AT+RST"), XW_AT_ready, XW_AT_ERROR, XW_AT_FAIL);
    if (result.indexOf(XW_AT_ready) != -1)
    {
        DisableEcho();
        SetAsStation();
        delay(500);
        return true;
    }
    return false;
}

//******************************************************************************
bool XwMcuEsp8266::DisableEcho()
{
    NextCommandTimeout = 2000;
    if (SetCommand(F("ATE0"), XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf(XW_AT_OK) != -1)
        return true;
    return false;
}

//******************************************************************************
bool XwMcuEsp8266::GetVersion(String *result)
{
    NextCommandTimeout = 2000;
    String version = SetCommand(F("AT+GMR"), XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR);
    if (version.indexOf(XW_AT_OK) != -1)
    {
        *result = version;
        return true;
    }
    return false;
}

//******************************************************************************
bool XwMcuEsp8266::SetAsStation()
{
    NextCommandTimeout = 2000;
    if (SetCommand(F("AT+CWMODE=1"), XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf(XW_AT_OK) != -1)
        return true;
    return false;
}

//******************************************************************************
bool XwMcuEsp8266::ListAPs(String *result)
{
    String list = SetCommand(F("AT+CWLAP"), XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR);
    if (list.indexOf(XW_AT_OK) != -1)
    {
        *result = list;
        return true;
    }
    return false;
}

//******************************************************************************
bool XwMcuEsp8266::Connect(String apName, String password)
{
    String command = F("AT+CWJAP=\"");
    command += apName;
    command += F("\",\"");
    command += password;
    command += F("\"");

    if (SetCommand(command, XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf(XW_AT_OK) != -1)
    {
        delay(500);
        return true;
    }
    return false;
}

//******************************************************************************
bool XwMcuEsp8266::GetIP(String *result)
{
    String ip = SetCommand(F("AT+CIFSR"), XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR);
    if (ip.indexOf(XW_AT_OK) != -1)
    {
        ip.replace(F("\r"), "");
        ip.replace(F("\n"), "");
        ip.replace(F("\""), "");
        ip.replace(F("+CIFSR:STAIP,"), "");
        ip = ip.substring(0,ip.indexOf(F("+")));
        if (ip == F("0.0.0.0"))
            return false;
        *result = ip;
        return true;
    }
    return false;
}

//******************************************************************************
bool XwMcuEsp8266::Disconnect()
{
    NextCommandTimeout = 2000;
    if (SetCommand(F("AT+CWQAP"), XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf(XW_AT_OK) != -1)
        return true;
    return false;
}

//******************************************************************************
bool XwMcuEsp8266::GetRequest(String *result, String host, uint16_t port, String url)
{
    String cmd1 = F("AT+CIPSTART=\"TCP\",\"");
    cmd1 += host;
    cmd1 += F("\",");
    cmd1 += port;
    if (SetCommand(cmd1, XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf(XW_AT_OK) != -1)
    {
        String cmd3 = F("GET ");
        cmd3 += url;
        cmd3 += F(" HTTP/1.1");
        cmd3 += F("\r\n");
        cmd3 += F("Host: ");
        cmd3 += host;
        cmd3 += F("\r\n\r\n");
        String cmd2 = F("AT+CIPSEND=");
        cmd2 += cmd3.length();
        bool ok = false;
        if (SetCommand(cmd2, XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR).indexOf(XW_AT_OK) != -1)
        {
            String content = SetCommand(cmd3, XW_AT_OK, XW_AT_FAIL, XW_AT_ERROR);
            if (content.indexOf(XW_AT_OK) != -1)
            {
                *result = content;
                ok = true;
            }
        }

        String cmdClose = F("AT+CIPCLOSE");
        SetCommand(cmdClose, F("CLOSED\r\n"));
        return ok;
    }
    return false;
}

#endif
