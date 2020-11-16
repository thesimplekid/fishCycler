#include <Arduino.h>
#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

const char *ssid = "DustyTrail";
const char *password = "RankerSmell";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial1.println("here");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  timeClient.begin();
}

void loop()
{
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());

  delay(1000);
}