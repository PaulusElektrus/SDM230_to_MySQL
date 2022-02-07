// Variablen für Drehzahlmessung

volatile int count = 0;                                            // Zähler für Reed-Kontakt
volatile int rpm = 0;                                              // Drehzahl in Umdrehungen pro Minute

void setup()
{
  Serial.begin(9600);                                              // Serielle Schnittstelle wird inititalisiert
  
  // Timer 1
  noInterrupts();                                                 // Alle Interrupts temporär abschalten
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 3036;                                                   // Timervorbelegung -> Overflow bei 4s
  TCCR1B |= (1 << CS12) | (1 <<CS10);                             // 1:1024 als Prescale-Wert spezifizieren
  TIMSK1 |= (1 << TOIE1);                                         // Timer Overflow Interrupt aktivieren
  
 
  Serial.print("Arduino-Setup erfolgreich!");
  Serial.println();

  interrupts();                                                   // alle Interrupts scharf schalten
  attachInterrupt(digitalPinToInterrupt(2), counter , RISING);    // Pin 2 als Interrupteingang, ISR counter(), steigende Flanke

}

// Selbstdefinierte Interruptbehandlungsroutine 
// alle 4s wird die Timer Overflow-ISR aufgerufen
ISR(TIMER1_OVF_vect)        
{

  rpm = count *15;                                             // Berechnung der Umdrehungen pro Minute, Overflow nach 4s
  
  Serial.print("Umdrehungen: ");
  Serial.print(rpm,DEC);
  Serial.print(" rpm");
  Serial.print("\n");

  count = 0;                                                  // Rücksetzen des Zählers
  rpm = 0;
  TCNT1 = 3036;                                               // Zählerregister Timer 1 erneut vorbelegen -> 4s bis zum Overflow
 
}

// Zähler Reed-Kontakt
void counter()
{
  count++;                                                      // Inkrementierung des Zählers für die Umdrehungszahl
}

void loop()
{

}
