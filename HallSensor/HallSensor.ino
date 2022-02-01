#include <WiFi.h>
#include <HTTPClient.h>

const char WIFI_SSID[] = "";
const char WIFI_PASSWORD[] = "";

String HOST_NAME = "http://29.11.97.165"; // change to your PC's IP address
String PATH_NAME   = "/insert_sensor_data.php";
String queryString = "";

int drehzahl = 0;
volatile int Wellendrehung = 0;
float Timestamp = 0;

void setup() {
  Serial.begin(9600); 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  attachInterrupt(34, functionCount, HIGH);
}

void functionCount() {
  Wellendrehung++;
}
  
void loop() {
   if ( millis()-Timestamp > 1000) // Wenn tausend Millisekunden vorüber...
  {
     noInterrupts();
     drehzahl = Wellendrehung*60;
     Wellendrehung = 0;
     Timestamp = millis();
     
     queryString = "?drehzahl=" + drehzahl;
  
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
      interrupts();
  }
}
