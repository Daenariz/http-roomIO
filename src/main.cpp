#include <WiFi.h>
#include <HTTPClient.h> 
#include <credentials.h>

#define LED_BUILTIN 2
#define buttonPin 13

int lastButtonState = HIGH; // pull-up-resistor (HIGH == unpressed button) 

void setup() {
  Serial.begin(115200); 

  pinMode(buttonPin, INPUT_PULLUP); 
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PW);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println("\nSuccess!");
} 

void loop() {
  HTTPClient http;
  int httpCode = 0;
  int buttonState = digitalRead(buttonPin); 


  if(WiFi.status() == WL_CONNECTED) {

  if(buttonState == LOW && lastButtonState == HIGH) { 
    Serial.println("Button state changed");
    delay(50); 
    http.begin(TOGGLE_URL);
    httpCode = http.POST("");
    if(httpCode > 0) {
      Serial.print("Toggle-POST Response Code: ");
      Serial.println(httpCode);
      String payload = http.getString();
      Serial.println("Toggle-POST Response: " + payload);
    } else {
      Serial.println("Toggle-POST failed: " + http.errorToString(httpCode));
    }
    http.end(); 
  }
    
    lastButtonState = buttonState; 

    http.begin(STATE_URL);  
    httpCode = http.GET(); 
    if(httpCode > 0) {
      Serial.printf("HTTP Response code: %d\n", httpCode);
      String payload = http.getString();
      Serial.println("Response: " + payload);
        if(payload == "closed") {
          digitalWrite(LED_BUILTIN, HIGH); 
        } else {
          digitalWrite(LED_BUILTIN, LOW); 
        }
    } 
    else {
      Serial.printf("GET failed: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end(); 
   
  } 
      else {
        Serial.println("Wifi not connected!");
      }
} 
