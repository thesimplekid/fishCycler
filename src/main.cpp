#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ezTime.h>

#include "Config.h"
#include "tank.h"
#include "floatSensor.h"

void setup_wifi();

Timezone myTZ;

int lastHour = 0;

tank tankA(13, 'A'),
    tankB(16, 'B');

floatSensor floatA('A', 14);

void setup()
{

    Serial.begin(9600);

    setup_wifi();

    waitForSync();

    myTZ.setLocation("America/New_York");
}

void loop()
{

    if (!tankB.filling)
    {
        tankA.checkTank(floatA.checkFloatState());
    }

    if (!tankA.filling)
    {
        tankB.checkTank();
    }

    //H for 24 00
    String currentHourString = myTZ.dateTime("H");
    int currentHour = currentHourString.toInt();
    if (lastHour != currentHour)
    {
        if (currentHour % 6 == 0)
        {
            //Fill tank for 1 Min
            tankA.cycleFillTime = 60000;
            Serial.println("Cycle A");
        }
        else if ((currentHour - 1) % 6 == 0)
        {
            tankB.cycleFillTime = 60000;
            Serial.println("Cycle B");
        }

        if (WiFi.status() != WL_CONNECTED)
        {
            setup_wifi();
            waitForSync();
        }
    }

    lastHour = currentHour;
}

void setup_wifi()
{

    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PW);

    int triedToConnect = 0;

    while (WiFi.status() != WL_CONNECTED && triedToConnect < 20)
    {
        delay(500);
        Serial.print(".");
        triedToConnect++;
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}