#include <WiFi.h>
#include <HTTPClient.h>

const char WIFI_SSID[] = "";
const char WIFI_PASSWORD[] = "";

String HOST_NAME = "http://"; // change to your PC's IP address
String PATH_NAME   = "/data.php";
String queryString = "";
String php = "";

volatile unsigned int counts = 0;
unsigned long rpm = 0; //unsigned gives only positive values
unsigned long previoustime = 0;

void IRAM_ATTR count_function ()
{
counts++;
}

void setup() {
  Serial.begin(9600); 
  pinMode(34, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500); 
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  attachInterrupt(34, count_function, RISING);
}
  
void loop() {
     delay(1000);//Update RPM every second
     detachInterrupt(34); //Interrupts are disabled
     rpm = 60*1000/(millis() - previoustime)*counts;
     
     rpm = 1234;
     php = String(rpm);
     queryString = "?drehzahl=" + php;
     
     HTTPClient http;
     http.begin(HOST_NAME + PATH_NAME + queryString); //HTTP
     int httpCode = http.GET();
      // httpCode will be negative on error
      if(httpCode > 0) {
        // file found at server
        if(httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
        } else {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();

      counts= 0; //Resets the counter
      Serial.println("RPM = ");
      Serial.println(rpm); //Calculated values are displayed
      previoustime = millis(); //Resets the clock
      attachInterrupt(34, count_function, RISING); //Counter restarted
}
