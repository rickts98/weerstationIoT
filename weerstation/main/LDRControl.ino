//Functionaliteiten die te maken hebben met de lichtsensor (LDR)

//variabelen 
const int LDRPIN = A1;
int LDRValue;
int oldLDRValue;


//setup van LDR
void ldrSetup(){
  pinMode(LDRPIN, INPUT);
}

//returned LDR waarde
int getLDRValue() {

  
  int ldrValue = analogRead(LDRPIN);


  //
  for(int i=1; i<= 512; i++){
      if(ldrValue < 2*i){
        LDRValue = i;

       if(oldLDRValue != LDRValue){
        oldLDRValue = LDRValue;
       }
        break;  
      }
    }
    
    return LDRValue;
}

