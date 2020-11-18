#include <Arduino.h>
#include <Wire.h>

class floatSensor
{
public:
    char floatIdentity;
    bool checkFloatState();

    int floatPin;

    unsigned long debounceDelay = 50;
    unsigned long lastDebounceTime;

    floatSensor(char floatIdentityPassed, int floatPinPassed)
    {
        floatIdentity = floatIdentityPassed;
        floatPin = floatPinPassed;
    }
};

bool floatSensor::checkFloatState()
{
    //TODO debounce maybe but seems to work

    return digitalRead(floatPin);
}
