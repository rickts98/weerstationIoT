const int BUTTONPIN = 8;

boolean buttonPressed;

void buttonSetup(){
  pinMode(BUTTONPIN, INPUT);
  buttonPressed = false;
}

void buttonLoop(){
  if(buttonDown()){
    buttonPressed = true;
  }
}

boolean getButtonPressed() {
  return buttonPressed;
}

boolean buttonDown(){
  return (digitalRead(BUTTONPIN) == LOW);
}

