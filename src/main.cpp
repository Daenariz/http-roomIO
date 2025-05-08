#include <WiFi.h>
#include <HTTPClient.h>
#include <credentials.h>

#define LED_BUILTIN 2
#define buttonPin 13

int lastButtonState = HIGH;  // pull-up-resistor (HIGH == unpressed button)

// Connects to WiFi
void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PW);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);  // Prevents excessive debug printing
  }
  Serial.println("\nSuccess!");
}

// Sends a POST request to the TOGGLE_URL
void sendToggleRequest() {
  HTTPClient http;
  int httpCode;

  http.begin(TOGGLE_URL);
  httpCode = http.POST("");
  if (httpCode > 0) {
    Serial.print("Toggle-POST Response Code: ");
    Serial.println(httpCode);
    String payload = http.getString();
    Serial.println("Toggle-POST Response: " + payload);
  } else {
    Serial.println("Toggle-POST failed: " + http.errorToString(httpCode));
  }
  http.end();
}

// Sends a GET request to the STATE_URL and controls the LED
void fetchStateAndControlLED() {
  HTTPClient http;
  int httpCode;

  http.begin(STATE_URL);
  httpCode = http.GET();
  if (httpCode > 0) {
    Serial.printf("HTTP Response code: %d\n", httpCode);
    String payload = http.getString();
    Serial.println("Response: " + payload);
    if (payload == "closed") {
      digitalWrite(LED_BUILTIN, HIGH);  // Turn LED on
    } else {
      digitalWrite(LED_BUILTIN, LOW);  // Turn LED off
    }
  } else {
    Serial.printf("GET failed: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

// Checks the button state
void handleButtonPress() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH) {
    Serial.println("Button state changed");
    delay(50);  // Debounce delay
    sendToggleRequest();
  }
  lastButtonState = buttonState;
}

void setup() {
  Serial.begin(115200);

  // Set pin modes
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  // Establish WiFi connection
  connectToWiFi();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    handleButtonPress();
    fetchStateAndControlLED();
  } else {
    Serial.println("WiFi not connected!");
    delay(1000);  // Prevents excessive debug output
  }
}
