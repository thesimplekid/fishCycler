#include <Arduino.h>
class tank
{
public:
    char tank_identity;
    void checkCycle();
    void doneFilling();
    bool refill(bool floatState);

    int signalPin;

    unsigned long milliSecondsToFill;
    unsigned long millisStartedFilling;
    unsigned long maxFillTime;
    unsigned long fillStartedAt;
    unsigned long lastFillEndedAt;
    unsigned long minDelayBetweenFills;

    bool filling;
    bool lastFillingState;

    tank(int signalPinPassed, unsigned long millisSeconds, char identity)
    {
        signalPin = signalPinPassed;
        milliSecondsToFill = millisSeconds;
        tank_identity = identity;
        filling = false;
        maxFillTime = 100000;
        minDelayBetweenFills = 5000;
    }
};

void tank::doneFilling()
{
    unsigned long elapsedFill = millis() - fillStartedAt;
    Serial.println("Done Filling");
    Serial.println(tank_identity);
    Serial.println(elapsedFill);

    filling = false;
    lastFillEndedAt = millis();
}

bool tank::refill(bool floatState)
{

    if (floatState && (millis() - lastFillEndedAt >= minDelayBetweenFills))
    {
        if (filling)
        {
            if ((millis() - fillStartedAt) > maxFillTime)
            {
                doneFilling();
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            filling = true;
            fillStartedAt = millis();
            return true;
        }
    }
    else if (filling)
    {
        doneFilling();
        return false;
    }
    else
    {
        return false;
    }
}
