//Naam: Rens Aerts
//Datum: 09-10-2018
//Functionaliteiten die te maken hebben met de lichtsensor (LDR)

const int LDRPIN = A1;
int LDRValue;
int oldLDRValue;

void ldrSetup(){
  pinMode(LDRPIN, INPUT);
}

char getLDRValue() {
  int ldrValue = analogRead(LDRPIN);
  
  for(int i=1; i<=256; i++){
      if(ldrValue < 4*i){
        LDRValue = i;

       if(oldLDRValue != LDRValue){
        oldLDRValue = LDRValue;
       }
        break;  
      }
    }
    return LDRValue;
}
