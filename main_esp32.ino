// Created hardware timer

hw_timer_t * timer = NULL;

// Variablen für Drehzahlmessung

volatile int count = 0;                                            // Zähler für Reed-Kontakt
volatile int rpm = 0;                                              // Drehzahl in Umdrehungen pro Minute

void setup()
{
  Serial.begin(9600);                                              // Serielle Schnittstelle wird inititalisiert
  
  // Timer 1
  /* Use 1st timer of 4 */
  /* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
  timer = timerBegin(0, 80, true);

  /* Attach onTimer function to our timer */
  timerAttachInterrupt(timer, &onTimer, true);

  /* Set alarm to call onTimer function every second 1 tick is 1us
  => 1 second is 1000000us */
  /* Repeat the alarm (third parameter) */
  timerAlarmWrite(timer, 1000000, true);

  /* Start an alarm */
  timerAlarmEnable(timer);
 
  Serial.print("Arduino-Setup erfolgreich!");
  Serial.println();

  interrupts();                                                   // alle Interrupts scharf schalten
  attachInterrupt(34, counter , RISING);    // Pin 2 als Interrupteingang, ISR counter(), steigende Flanke

}

// Selbstdefinierte Interruptbehandlungsroutine 
// alle 1s wird die Timer Overflow-ISR aufgerufen
void IRAM_ATTR onTimer()      
{
  rpm = 0;                                                    // Zählerregister Timer 1 erneut vorbelegen -> 4s bis zum Overflow
  rpm = count * 60;                                           // Berechnung der Umdrehungen pro Minute, Overflow nach 4s
  count = 0;                                                  // Rücksetzen des Zählers
}

// Zähler Reed-Kontakt
void IRAM_ATTR counter()
{
  count++;                                                      // Inkrementierung des Zählers für die Umdrehungszahl
}

void loop()
{
  Serial.print("Umdrehungen: ");
  Serial.print(rpm,DEC);
  Serial.print(" rpm");
  Serial.print("\n");
}
