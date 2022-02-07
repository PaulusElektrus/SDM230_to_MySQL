#include <Arduino.h>

byte DZM_InputPin = 34;
volatile unsigned long RPM_T2, RPM_Count;
unsigned long RPM , RPM_T1;

void setup() {

  Serial.begin(9600);
  pinMode(DZM_InputPin, INPUT_PULLUP);
  RPM_T1 = 0;
  RPM_T2 = 0;
  RPM_Count = 0;

  attachInterrupt(34, RPM_Meter, FALLING);    // Interrupt0 wird bei fallender Flanke auf Pin2

}

void loop() {
  if (RPM_T2 > RPM_T1) {
    RPM = (unsigned)(long)(60000 * RPM_Count / (RPM_T2 - RPM_T1));
    RPM_T1 = RPM_T2;
    RPM_Count = 0;
  }
  else {
    RPM = 0;
  }
  Serial.println(RPM);
  delay(1000);
}

void RPM_Meter () {

  RPM_Count++;
  RPM_T2 = millis();

}
