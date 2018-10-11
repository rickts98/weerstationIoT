unsigned long prevMillisTest;
int testInterval = 500;
int index = 0;
boolean testWeerstation = false;

void testSetup()
{
    prevMillisTest = millis();
}

void testLoop()
{
    if (testWeerstation)
    {
        testComponents();
    }
}

void testComponents()
{
    unsigned long currentMillisTest = millis();

    if (currentMillisTest - prevMillisTest >= testInterval)
    {
        prevMillisTest = currentMillisTest;

        if (isLedOn(i))
        {
            ledControlOff(i);
            setLedStatus(i, false);
            index++;
        }
        else
        {
            ledControlOn(i);
            setLedStatus(i, true);
        }
    }

    if (index >= getNrLeds())
    {
        Serial.println("--------------TestOutput-------------");
        Serial.print("Lichtsterkte: ");
        Serial.println(getLDRValue());
        Serial.print("Temperaturr: ");
        Serial.println(readTempValue());
        Serial.println("--------------------------------------");
        setTestWeerstation(false);
        index = 0;
    }
}

void setTestWeerstation(boolean value)
{
    testWeerstation = value;
}