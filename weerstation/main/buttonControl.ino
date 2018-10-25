
//Variabelen
const int BUTTONPIN = 8;
boolean buttonPressed;

//setup van knop 
void buttonSetup(){
  pinMode(BUTTONPIN, INPUT);

  //waarde van buttonPressed aanpassen
  buttonPressed = false;
}

void buttonLoop(){
  //controleren of er op de knop gedrukt is
  if(buttonDown()){
    buttonPressed = true;
  }
}


//returned de waarde van buttonPressed
boolean getButtonPressed() {
  return buttonPressed;
}

//controleerd of er op de knop gedrukt is
boolean buttonDown(){
  return (digitalRead(BUTTONPIN) == LOW);
}

