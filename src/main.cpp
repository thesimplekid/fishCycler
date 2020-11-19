#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "Config.h"
#include "tank.h"
#include "floatSensor.h"

void connectToWifi();
void getSettings();

tank tankA(15, 5000, 'A'), tankB(16, 10000, 'B');
floatSensor floatA('A', 13);

void setup()
{
    Serial.begin(9600);

    /* #ifndef ESP8266
    while (!Serial)
        ; // wait for serial port to connect. Needed for native USB
#endif */

    //getSettings();
}

void loop()
{
    tankA.checkTank(floatA.checkFloatState());
    tankB.checkTank();
}
void connectToWifi()
{
    WiFi.begin(WIFI_SSID, WIFI_PW);

    int wifiConnectTries = 0;

    while (WiFi.status() != WL_CONNECTED && wifiConnectTries < 10)
    {
        delay(500);
        Serial.print(".");
        wifiConnectTries++;
    }

    if (WiFi.status())
    {
        Serial.println("Connected to Wifi");
    }
    else
    {
        Serial.println("Cant connect to WiFi");
    }
}
