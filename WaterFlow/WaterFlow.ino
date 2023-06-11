#include <WiFi.h>
#include <HTTPClient.h>

const char WIFI_SSID[] = "";
const char WIFI_PASSWORD[] = "";

String HOST_NAME = "http://192.168.0.100"; // change to your PC's IP address
String PATH_NAME   = "/data.php";
String queryString1 = "";
String queryString2 = "";
String queryString3 = "";
String rpms = "";
String flowRates = "";
String totalMilliLitress = "";

byte waterPin = 34;
byte drehzahlPin = 35;

float calibrationFactor = 6.5163;
float calibrationDifference = 2.7;

volatile byte pulseCountRPM;
volatile byte pulseCountWater;  

float flowRate;
float rpm;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;

void setup()
{
  Serial.begin(9600);
  
  pinMode(waterPin, INPUT);
  digitalWrite(waterPin, HIGH);
  pinMode(drehzahlPin, INPUT);
  digitalWrite(drehzahlPin, HIGH);

  pulseCountRPM     = 0;
  pulseCountWater   = 0;
  flowRate          = 0.0;
  rpm               = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  attachInterrupt(waterPin, pulseCounterwater, FALLING);
  attachInterrupt(drehzahlPin, pulseCounterrpm, FALLING);
}

void loop()
{
   if((millis() - oldTime) > 1000)
  { 
    detachInterrupt(drehzahlPin);
    detachInterrupt(waterPin);
    
    float tmp = (1000.0 / (millis() - oldTime)) * pulseCountWater;
    float rpm = (1000.0 / (millis() - oldTime)) * pulseCountRPM * 60;

    if (tmp > 0) {
      flowRate = tmp / calibrationFactor + calibrationDifference;
    }else {
      flowRate = 0;
    }
    
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;

    rpms = String(rpm);
    flowRates = String(flowRate);
    totalMilliLitress = String(totalMilliLitres);
      
    queryString1 = "?drehzahl=" + rpms;
    queryString2 = "&flowRate=" + flowRates;
    queryString3 = "&total=" + totalMilliLitress;
     
     HTTPClient http;
     http.begin(HOST_NAME + PATH_NAME + queryString1 + queryString2 + queryString3);
     int httpCode = http.GET();
      if(httpCode > 0) {
        if(httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
        } else {
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    
    pulseCountRPM = 0;
    pulseCountWater = 0;
    oldTime = millis();
    
    attachInterrupt(waterPin, pulseCounterwater, FALLING);
    attachInterrupt(drehzahlPin, pulseCounterrpm, FALLING);
  }
}

void pulseCounterwater()
{
  pulseCountWater++;
}

void pulseCounterrpm()
{
  pulseCountRPM++;
}
