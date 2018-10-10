//Naam: Rens Aerts
//Datum: 09-10-2018
//Aansturen van leds

const int NLEDS = 3;
const int PINARRAY[] = {5,6,7};
const int GEEL = 5;
const int GROEN = 6;
const int ROOD = 7;
//5 = Geel, 6 = Groen, 7 = Rood

void ledControlSetup(){    
  for(int i=0; i<getNrLeds(); i++){
    pinMode(PINARRAY[i], OUTPUT);
  }
}

void ledControlAan(int led){
    digitalWrite(PINARRAY[led], HIGH);
}

void ledControlUit(int led){
    digitalWrite(PINARRAY[led], LOW);
}

int getNrLeds(){
  return NLEDS;  
}


