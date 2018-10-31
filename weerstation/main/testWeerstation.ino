
//Herschrijven WERKT NIET MEER



unsigned long prevMillisTest;
int testInterval = 500;
int i = 0;
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
      Serial.println("jemoeder");
        prevMillisTest = currentMillisTest;

        if (isLedOn(i))
        {
            ledControlOff(i);
            setLedStatus(i, false);
            i++;
        }
        else
        {
            ledControlOn(i);
            setLedStatus(i, true);
        }
    }

    if (i >= getNrLeds())
    {
        Serial.println("--------------TestOutput-------------");
        Serial.print("Lichtsterkte: ");
        Serial.println(getLDRValue());
        Serial.print("Temperature: ");
        Serial.println(printTemperature());
        Serial.println("--------------------------------------");
        setTestWeerstation(false);
        i = 0;
    }
}

void setTestWeerstation(boolean value)
{
    testWeerstation = value;
}

boolean getTestWeerstation(){
  
  return testWeerstation;
  }
