const byte interruptPin = 34;
volatile int interruptCounter = 0;
volatile int rpm = 0; 

hw_timer_t * timer = NULL; 
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
 
void IRAM_ATTR handleInterrupt() {
  portENTER_CRITICAL_ISR(&mux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&mux);
}

void IRAM_ATTR onTimer()      
{
  rpm = 0;  
  portENTER_CRITICAL(&mux);
  rpm = interruptCounter * 15;  
  interruptCounter = 0; 
  portEXIT_CRITICAL(&mux);
}
 
void setup() {
 
  Serial.begin(9600);
  Serial.println("Monitoring interrupts: ");

  timer = timerBegin(0, 80, true);

  /* Attach onTimer function to our timer */
  timerAttachInterrupt(timer, onTimer, true);

  /* Set alarm to call onTimer function every second 1 tick is 1us
  => 1 second is 1000000us */
  /* Repeat the alarm (third parameter) */
  timerAlarmWrite(timer, 1000000, true);

  /* Start an alarm */
  timerAlarmEnable(timer);
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, RISING);
 
}
 
void loop() {
   Serial.println(rpm);// Berechnung der Umdrehungen pro Minute, Overflow nach 4s
}
