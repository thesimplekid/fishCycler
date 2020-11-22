
class floatSensor
{
public:
    char floatIdentity;
    bool checkFloatState();

    int floatPin;

    floatSensor(char floatIdentityPassed, int floatPinPassed)
    {
        floatIdentity = floatIdentityPassed;
        floatPin = floatPinPassed;

        pinMode(floatPin, INPUT_PULLUP);
    }
};

bool floatSensor::checkFloatState()
{
    //TODO debounce maybe but seems to work
    return digitalRead(floatPin);
}
