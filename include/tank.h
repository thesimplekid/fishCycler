class tank
{
public:
    char tank_identity;
    void checkTank(bool floatState);
    void startFilling();
    void stopFilling();

    bool refill(bool floatState);

    int signalPin;

    unsigned long maxFillTime;
    unsigned long fillStartedAt;
    unsigned long lastFillEndedAt;
    unsigned long minDelayBetweenFills;
    unsigned long cycleFillTime;

    bool filling;

    tank(int signalPinPassed, char identity)
    {
        signalPin = signalPinPassed;
        tank_identity = identity;

        cycleFillTime = 0;
        filling = false;
        maxFillTime = 300000;
        minDelayBetweenFills = 5000;

        pinMode(signalPin, OUTPUT);
        digitalWrite(signalPin, HIGH);
    }
};

void tank::startFilling()
{
    Serial.print("___Started Filling___: ");
    Serial.println(tank_identity);

    fillStartedAt = millis();
    Serial.println(fillStartedAt);
    filling = true;
    digitalWrite(signalPin, LOW);
}

void tank::stopFilling()
{
    // TODO - return done to server with elapsed fill to server
    unsigned long elapsedFill = millis() - fillStartedAt;

    Serial.print("___Done Filling___: ");
    Serial.println(tank_identity);
    Serial.println(elapsedFill);

    filling = false;
    lastFillEndedAt = millis();
    cycleFillTime = 0;
    digitalWrite(signalPin, HIGH);
}

void tank::checkTank(bool floatState = false)
{
    if (filling)
    {
        if (!floatState && (millis() - fillStartedAt > cycleFillTime))
        {
            stopFilling();
        }
        else if (floatState && ((millis() - fillStartedAt) > maxFillTime))
        {
            stopFilling();
        }
    }

    else if (millis() - lastFillEndedAt > minDelayBetweenFills)
    {
        if (cycleFillTime > 0 || floatState)
        {
            startFilling();
        }
    }

    if (millis() - lastFillEndedAt < 0 || millis() - fillStartedAt < 0)
    {
        //TODO - idk if this is really needed
        Serial.println("__overflow check__");
        stopFilling();
    }
}
