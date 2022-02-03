#include <TimerOne.h>        // für Timings und Interrupts

#define PinData 34           // wo ist Data angeschlossen?

void setup() {
  TimerOne.initialize();
  pinMode (PinData, INPUT_PULLUP);
}


void loop() {

  long mic=0;
  long micBef=micros();
  long micDelta=0;
  byte stateBef=HIGH;
  byte state=HIGH;
  float upm=0;

  while (1) {
    state=digitalRead(PinData);
    
    // wenn Statusänderung
    if (state != stateBef) {
      // Zählbeginn, wenn Flanke auf LOW (=geschlossen) wechselt 
      if (state == LOW) { 
        mic=micros();
        micDelta=mic-micBef;
        micBef=mic;
        upm=1./(micDelta/1000000.)*60.;
        Serial.println(upm);
      }
    }
    stateBef=state;
  }
}
