//Naam: Rens Aerts
//Datum: 09-10-2018
//Aansturen van leds


//variabelen
const int NLEDS = 3; //aantal leds
const int PINARRAY[] = {5,6,7}; //Pin nummer van de leds
int ledStatus[] = {false, false, false}; //status van de leds
//PIN 5 = Geel, PIN 6 = Groen, PIN 7 = Rood


//Setup van de leds
void ledControlSetup(){    
  for(int i=0; i<getNrLeds(); i++){
    pinMode(PINARRAY[i], OUTPUT);
  }
}
//conbtroleerd of led aan is
boolean isLedOn(int led){
  if(ledStatus[led] == true) {
    return true;
  } else return false;
}

//zet de led aan die meegegeven word
void ledControlOn(int led){
    digitalWrite(PINARRAY[led], HIGH);
}

//zet de led uit die meegegeven word
void ledControlOff(int led){
    digitalWrite(PINARRAY[led], LOW);
}


//returned aantal leds
int getNrLeds(){
  return NLEDS;  
}


//pas de status van de led aan in de araay ledStatus
void setLedStatus(int led, boolean status){
  ledStatus[led] = status;
}


