void setup(){
    Serial.begin(9600);
}
 
void loop(){
    if (Serial.available()) {
        byte nr = Serial.read();
        Serial.print("Folgender char wurde empfangen: ");
        Serial.println(nr, DEC);
    }
}
