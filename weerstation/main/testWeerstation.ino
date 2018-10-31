//variabelen
unsigned long prevMillisTest;
int testInterval = 500;
int i = 0;
//status van testen 
boolean testWeerstation = false;


void testSetup()
{
    //zetten van de timer
    prevMillisTest = millis();
}

void testLoop()
{
  //controle of test gedaan mag worden
    if (testWeerstation)
    {
      //test uitvoeren
        testComponents();
    }
}

void testComponents()
{
  //tijd gelijk zetten
    unsigned long currentMillisTest = millis();
    if (currentMillisTest - prevMillisTest >= testInterval)
    {
        prevMillisTest = currentMillisTest;

        if (isLedOn(i))
        {
          //led uit zetten
            ledControlOff(i);
            setLedStatus(i, false);
            i++;
        }
        else
        {
          //led aanzetten
            ledControlOn(i);
            setLedStatus(i, true);
        }
    }

    if (i >= getNrLeds())
    {

      //uitprinten op serial van alle waardes
        Serial.println("--------------TestOutput-------------");
        Serial.print("Lichtsterkte: ");
        Serial.println(getLDRValue());
        Serial.print("Temperature: ");
        Serial.println(printTemperature());
        Serial.println("--------------------------------------");
        setTestWeerstation(false); //resetten van boolean
        i = 0;// resetten van i
    }
}

void setTestWeerstation(boolean value)
{
    testWeerstation = value;
}

boolean getTestWeerstation(){
  
  return testWeerstation;
  }
