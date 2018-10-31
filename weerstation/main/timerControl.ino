// Naam: Rens Aerts
// Datum: 09-10-2018
// zorgen dat op de juiste tijdstippen de waardes worden geprint

// Variabalen
unsigned long prevMillisLDR;
unsigned long prevMillisTemp;
int intervalLDR = 7000;  // interval van 7 seconden
int intervalTemp = 5000; // interval van 5 seconden

void timerSetup() {
  // dit zorgt ervoor dat de twee timers gelijk lopen
  prevMillisLDR = millis();
  prevMillisTemp = millis();
}

void timerLoop() {
  // tijd gelijk zetten met de tijd van nu
  unsigned long currentMillisLDR = millis();
  unsigned long currentMillisTemp = millis();

  // controle of de interval voorbij is
  if (currentMillisLDR - prevMillisLDR >= intervalLDR) {
    prevMillisLDR = currentMillisLDR;     // tijd resetten
    cbAdd(getBufferLux(), getLDRValue()); // LDR waarde aan buffer toevoegen
    Serial.print("Lux: ");
    Serial.println(cbRead(getBufferLux()));
  }

  // controleren of de interval voorbij is
  if (currentMillisTemp - prevMillisTemp >= intervalTemp) {
    prevMillisTemp = currentMillisTemp; // tijd resetten
    cbAdd(getBufferTemp(),
          actualGetTemperature()); // Temp waarde aan buffer toevoegen
    Serial.print("Temp: ");
    Serial.println(cbRead(getBufferTemp()));
  }
}
