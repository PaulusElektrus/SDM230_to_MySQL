byte sensorPin = 2;
byte waterPin = 3;

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 6.5163;
float calibrationDifference = 2.7;

volatile byte pulseCount;
volatile byte waterCount;   

float flowRate;
float tmp;
float rpm;

float flowMilliLitres;
float totalMilliLitres;

unsigned long oldTime;

void setup()
{
  
  // Initialize a serial connection for reporting values to the host
  Serial.begin(9600);
   

  
  pinMode(sensorPin, INPUT);
  pinMode(waterPin, INPUT);

  pulseCount        = 0;
  waterCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  tmp               = 0;
  rpm               = 0;

  // The Hall-effect sensor is connected to pin 2 which uses interrupt 0. <-- Better to use digitalpintointerrupt
  // Configured to trigger on a FALLING state change (transition from HIGH
  // state to LOW state)
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, RISING);
  attachInterrupt(digitalPinToInterrupt(waterPin), waterCounter, RISING);
}

/**
 * Main program loop
 */
void loop()
{
   
   if((millis() - oldTime) > 1000)    // Only process counters once per second
  { 
    // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(digitalPinToInterrupt(sensorPin));
    detachInterrupt(digitalPinToInterrupt(waterPin));
        
    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    tmp = (1000.0 / (millis() - oldTime)) * waterCount;
    rpm = (1000.0 / (millis() - oldTime)) * pulseCount*60;

    // As we have a add operation we need to avoid the positive value when no pulse is found
    if (tmp > 0) {
      flowRate = tmp / calibrationFactor + calibrationDifference;
    }else {
      flowRate = 0;
    }
    
    // Note the time this processing pass was executed. Note that because we've
    // disabled interrupts the millis() function won't actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.
    oldTime = millis();
    
    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres = (flowRate / 60);
    
    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;
      
    unsigned int frac;
    
    // Print the flow rate for this second in litres / minute

    // this serial print was used to get the FREQUENCY value to calculate the other values.
//    Serial.print("F: ");
//    Serial.print(tmp);
//
//    Serial.print("Flow rate: ");
//    Serial.print(flowRate);  // Print the integer part of the variable
//    Serial.print("L/min");
//    Serial.print("\t");       // Print tab space
//
//    // Print the cumulative total of litres flowed since starting
//    Serial.print("Output Liquid Quantity: ");        
//    Serial.print(totalMilliLitres);
//    Serial.print("mL");
//    
//    Serial.print("\t");        // Print tab space
//    Serial.print(totalMilliLitres/1000);
//    Serial.println("L");

    Serial.print(rpm);
    Serial.print(" , ");
    Serial.print(flowRate);
    Serial.print(" , ");
    Serial.print(totalMilliLitres);
    Serial.print("\n");

    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;
    waterCount = 0;
    
    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, RISING);
    attachInterrupt(digitalPinToInterrupt(waterPin), waterCounter, RISING);
  }
}

/*
Insterrupt Service Routine
 */
void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}

void waterCounter()
{
  // Increment the pulse counter
  waterCount++;
}
