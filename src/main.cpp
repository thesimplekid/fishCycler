#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <ezTime.h>

#include "Config.h"
#include "tank.h"
#include "floatSensor.h"

void setup_wifi();

Timezone myTZ;

int lastHour = 0;

tank tankA(15, 'A'),
    tankB(16, 'B');
floatSensor floatA('A', 13);

void setup()
{
    Serial.begin(9600);

    setup_wifi();

    waitForSync();

    myTZ.setLocation("America/New_York");

    /* #ifndef ESP8266
    while (!Serial)
        ; // wait for serial port to connect. Needed for native USB
#endif */
}

void loop()
{

    tankA.checkTank(floatA.checkFloatState());
    tankB.checkTank();

    //H for 24 00
    String test = myTZ.dateTime("H");
    int currentHour;
    currentHour = test.toInt();
    if (lastHour != currentHour)
    {

        if (currentHour == 6 || currentHour == 12 || currentHour == 18 || currentHour == 0)
        {
            tankA.cycleFillTime = 60000;
        }
        else if (currentHour == 7 || currentHour == 13 || currentHour == 19 || currentHour == 1)
        {
            tankB.cycleFillTime = 60000;
        }
        Serial.println("funning this");
    }
    lastHour = currentHour;
}

void setup_wifi()
{

    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PW);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}