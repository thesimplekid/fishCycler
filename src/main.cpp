#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Config.h>
//#include <time.h>
#include <Wire.h>
//#include <ezTime.h>

int relaySignalPinA = 15;
int relaySignalPinB = 16;
int floatPin = 13;

int currentFloatPin;
int floatState;
int lastFloatState;

bool refilling;

unsigned long currentMillis;
unsigned long lastDebounceTime;
unsigned long debounceDelay = 50;
unsigned long refillStart;
unsigned long killFillAt;

unsigned long maxFillTime = 5000;
unsigned long canFillAgian = 5000;

//Timezone myTZ;

void setup()
{
    /*clear water levels and such by using time greater then   */
    Serial.begin(9600);

    /* #ifndef ESP8266
    while (!Serial)
        ; // wait for serial port to connect. Needed for native USB
#endif */

    WiFi.begin(WIFI_SSID, WIFI_PW);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    // waitForSync();

    //myTZ.setLocation(F("America/New_York"));
    //Serial.println(myTZ.dateTime());

    pinMode(relaySignalPinA, OUTPUT);
    pinMode(relaySignalPinB, OUTPUT);
    pinMode(floatPin, INPUT);
    digitalWrite(relaySignalPinA, LOW);
    refilling = false;

    //configTime(0, 0, "0.north-america.pool.ntp.org");
    //Serial.println("\nWaiting for time");
}

void loop()
{
    currentMillis = millis();

    currentFloatPin = digitalRead(floatPin);
    Serial.println(currentFloatPin);

    if (currentFloatPin != lastFloatState)
    {
        lastDebounceTime = millis();
    }

    if ((currentMillis - lastDebounceTime) > debounceDelay)
    {
        if (currentFloatPin == HIGH && (currentMillis - killFillAt >= canFillAgian))
        {
            if (refilling)
            {
                if ((currentMillis - refillStart) >= maxFillTime)
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
        else
        {
            digitalWrite(relaySignalPinA, LOW);
            refilling = false;
        }
    }

    //Serial.println(myTZ.dateTime("H:i"));
    lastFloatState = currentFloatPin;
}