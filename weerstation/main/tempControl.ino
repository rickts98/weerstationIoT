//Naam: Rick ter Steege
//Datum: 9-10-2018
//functionaliteiten die te maken hebben met de temperatuur 
//Bron: https://git.icaprojecten.nl/stash/pages/~CHRIS.VANUFFELEN_HAN.NL/iot-software-pub/master/browse/#Thermistor%20code



//IO pins
const int thermistorPin = A0;

// Thermistor calculation values
#define RESISTOR 33000  //voltage divider resistor
#define THERMISTOR 1001 //thermistor value at 25 degrees PTC = 1010

//Steinhart-Hart parameter a, b, c and d (from datasheet, NTC 4.7kohm)
#define SHa 0.003354016
#define SHb 0.0002569850
#define SHc 0.000002620131
#define SHd 0.00000006383091

unsigned int readTempValueRAW()
{
    return analogRead(thermistorPin);
}

//returns the current resistor value of the thermistor (temperature dependend)
float thermistorValue()
{
    return (1024.0 * RESISTOR / (float)readTempValueRAW()) - RESISTOR; //voltage divider Rtherm = ((Ui/Uo)*R)-R
}

//returns the actual temperature
float readTempValue()
{
    // using the Steinhart-Hart equation http://en.wikipedia.org/wiki/Thermistor
    // 1/T= a + b*ln(R/Rt) + c*ln(R/Rt)^2 + d*ln(R/Rt)^3
    float logR;
    float temp;
    logR = log(thermistorValue() / THERMISTOR);
    temp = 1 / (SHa + (SHb * logR) + (SHc * logR * logR) + (SHd * logR * logR * logR)); //Temperature in Kelvin
    temp = temp - 273.15;                                                               // Convert Kelvin to Celsius
    return temp;
}

void sendTempString()
{
    Serial.print("Temperatuur : ");
    Serial.print(readTempValue(), 1);
    Serial.println(" graden Celsius");
}
 
