#include <Arduino.h>
#include <Wire.h>

class floatSensor
{
public:
    char floatIdentity;
    bool checkFloatState();

    int floatPin;
    bool lastFloatState;

    floatSensor(char floatIdentityPassed, int floatPinPassed)
    {
        floatIdentity = floatIdentityPassed;
        floatPin = floatPinPassed;
        pinMode(floatPin, INPUT);
        lastFloatState = checkFloatState();
    }
};

bool floatSensor::checkFloatState()
{
    //TODO debounce maybe but seems to work
    return digitalRead(floatPin);
}
