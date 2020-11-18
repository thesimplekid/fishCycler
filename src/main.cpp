#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Config.h>
#include <Wire.h>

int relaySignalPinA = 15; //15
int relaySignalPinB = 16; //16
int floatPin = 13;

int currentFloatPin;
int floatState;
int lastFloatState;

bool refilling = false;
bool fillingA;
bool fillingB;
bool lastFillingAState;
bool lastFillingBState;

unsigned long lastDebounceTime;
unsigned long debounceDelay = 50;
unsigned long refillStart;
unsigned long killFillAt;
unsigned long triedToConnect;
unsigned long delayForReconnect = 10000;

unsigned long timeToFillA;
unsigned long startedFillingA;

unsigned long timeToFillB;
unsigned long startedFillingB;

unsigned long millisecodsToFillA = 5000;
unsigned long millisecodsToFillB = 10000;

unsigned long maxFillTime = 0;
unsigned long canFillAgian = 0;

void connectToWifi();
void getSettings();
void checkIfNeedRefill();
unsigned long checkACycle();
unsigned long checkBCycle();
void doneFilling(unsigned long elapsedFill, int tankID);

void setup()
{
    Serial.begin(9600);

    /* #ifndef ESP8266
    while (!Serial)
        ; // wait for serial port to connect. Needed for native USB
#endif */

    getSettings();

    pinMode(relaySignalPinA, OUTPUT);
    pinMode(relaySignalPinB, OUTPUT);
    pinMode(floatPin, INPUT);

    digitalWrite(relaySignalPinA, LOW);
    digitalWrite(relaySignalPinB, LOW);
}

void loop()
{

    if (!WiFi.status() && millis() - triedToConnect > delayForReconnect)
    {
        connectToWifi();
    }

    if (!fillingA)
    {
        timeToFillA = checkACycle();
        if (timeToFillA > 0)
        {
            fillingA = true;
            startedFillingA = millis();
            digitalWrite(relaySignalPinA, HIGH);
        }
        else
        {
            checkIfNeedRefill();
        }
    }
    else
    {
        unsigned long elapsedFillA = (millis() - startedFillingA);
        if (elapsedFillA > timeToFillA && lastFillingAState == true)
        {
            fillingA = false;
            digitalWrite(relaySignalPinA, LOW);
            doneFilling(elapsedFillA, 1);
        }
    }
    if (!fillingB)
    {
        timeToFillB = checkBCycle();

        if (timeToFillB > 0)
        {
            fillingB = true;
            startedFillingB = millis();
            digitalWrite(relaySignalPinB, HIGH);
        }
    }
    else
    {
        unsigned long elapsedFillB = (millis() - startedFillingB);
        if (elapsedFillB > timeToFillB && lastFillingBState == true)
        {
            fillingB = false;
            digitalWrite(relaySignalPinB, LOW);
            doneFilling(elapsedFillB, 2);
        }
    }

    lastFillingAState = fillingA;
    lastFillingBState = fillingB;
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

void checkIfNeedRefill()
{
    currentFloatPin = digitalRead(floatPin);

    if (currentFloatPin != lastFloatState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        if (currentFloatPin == HIGH && (millis() - killFillAt >= canFillAgian))
        {
            if (refilling)
            {
                if ((millis() - refillStart) >= maxFillTime)
                {
                    refilling = false;
                    killFillAt = millis();
                    digitalWrite(relaySignalPinA, LOW);
                }
                else
                {
                    refilling = true;
                    digitalWrite(relaySignalPinA, HIGH);
                }
            }
            else
            {
                refilling = true;
                refillStart = millis();
                digitalWrite(relaySignalPinA, HIGH);
            }
        }
        else if (currentFloatPin == LOW)
        {
            digitalWrite(relaySignalPinA, LOW);
            refilling = false;
        }
    }

    lastFloatState = currentFloatPin;
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
}

void doneFilling(unsigned long elapsedFill, int tankID)
{

    Serial.println(tankID);
    Serial.println(elapsedFill);
    //TODO tell server done 

    if (tankID == 1)
    {
        millisecodsToFillA = 0;
    }
    else if (tankID == 2)
    {
        millisecodsToFillB = 0;
    }
    else
    {
        Serial.println("Invalid ID");
    }
}