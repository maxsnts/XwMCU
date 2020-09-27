// XwMcuLibrary
// Esp8266 example (ESP-01)

// Incomplete Example

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <XwMcuEsp8266.h>

SoftwareSerial softSerial(10,11);
XwMcuEsp8266 wifi;

void setup()
{
    Serial.begin(9600);
    while (!Serial);
    softSerial.begin(9600);
    while (!softSerial);

    Serial.println("### BOOTING... ###");

    wifi.Begin(&softSerial, 4);

    Serial.println("### ...BOOTED ###");
}

void loop()
{
    wifi.Enable();

    delay(5000);

    if (wifi.Reset())
    {
        String version;
        wifi.GetVersion(&version);

        String list;
        wifi.ListAPs(&list);
        Serial.println(list);

        Serial.print("Connecting...");
        if (wifi.Connect("PEGASUS 2.4GHz", "********"))
        {
            Serial.println("Connected");
            //delay(5000);

            String ip;
            wifi.GetIP(&ip);
            Serial.println(ip);

            String content;
            wifi.GetRequest(&content, "emoncms.org", 80, "/input/post.json?apikey=5c79589c64b9d4afbdf7f551c628363d&json={power:150}");
            Serial.println(content);

            //delay(10000);

            wifi.Disconnect();
        }
        else
            Serial.println("Not connected");
    }
    else
        Serial.println("Not reseted");

    wifi.Disable();

    delay(10000);
}
