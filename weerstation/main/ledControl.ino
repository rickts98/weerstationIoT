//Naam: Rens Aerts
//Datum: 09-10-2018
//Aansturen van leds

const int NLEDS = 3;
const int PINARRAY[] = {5,6,7};
int ledStatus[] = {false, false, false};
//PIN 5 = Geel, PIN 6 = Groen, PIN 7 = Rood

void ledControlSetup(){    
  for(int i=0; i<getNrLeds(); i++){
    pinMode(PINARRAY[i], OUTPUT);
  }
}

boolean isLedOn(int led){
  if(ledStatus[led] == true) {
    return true;
  } else return false;
}

void ledControlOn(int led){
    digitalWrite(PINARRAY[led], HIGH);
}

void ledControlOff(int led){
    digitalWrite(PINARRAY[led], LOW);
}

int getNrLeds(){
  return NLEDS;  
}

void setLedStatus(int led, boolean status){
  ledStatus[led] = status;
}


