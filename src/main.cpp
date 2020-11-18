#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "Config.h"
#include "tank.h"
#include "floatSensor.h"

int relaySignalPinA = 15; //15
int relaySignalPinB = 16; //16
int floatPin = 13;

bool refilling = false;
bool fillingA;
bool fillingB;
bool lastFillingAState;
bool lastFillingBState;

unsigned long refillStart;
unsigned long killFillAt;
unsigned long triedToConnect;
unsigned long delayForReconnect = 10000;

void connectToWifi();
void getSettings();
unsigned long checkACycle();
unsigned long checkBCycle();

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

    pinMode(relaySignalPinA, OUTPUT);
    pinMode(relaySignalPinB, OUTPUT);
    pinMode(floatPin, INPUT);

    digitalWrite(relaySignalPinA, LOW);
    digitalWrite(relaySignalPinB, LOW);
}

void loop()
{
    digitalWrite(tankA.signalPin, tankA.refill(floatA.checkFloatState()));
}

/* void connectToWifi()
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

void getSettings()
{
    //TODO put in gets but for now
    bool getMaxFillTime = false;
    bool getCanFIllAgian = false;

    if (!getMaxFillTime && maxFillTime == 0)
    {
        Serial.println("Using default max Fill");
        maxFillTime = 5000;
    }

    if (!getCanFIllAgian && canFillAgian == 0)
    {
        Serial.println("Using default can fill");
        canFillAgian = 5000;
    }
}

unsigned long checkACycle()
{
    //TODO get from server
    return millisecodsToFillA;
}

unsigned long checkBCycle()
{
    //TODO get from server
    return millisecodsToFillB;
} */
