#include <Arduino.h>
#include "DHT.h"

#define DHTPIN 14
#define DHTTYPE DHT22

#define BUZZER_PIN 4

#define RED_PIN    16
#define GREEN_PIN  17
#define BLUE_PIN   18

#define PWM_FREQ        5000
#define PWM_RESOLUTION  8
#define RED_CHANNEL     0
#define GREEN_CHANNEL   1
#define BLUE_CHANNEL    2

DHT dht(DHTPIN, DHTTYPE);

enum HeaterState {
  IDLE,
  HEATING,
  STABILIZING,
  TARGET_REACHED,
  OVERHEAT
};

HeaterState currentState = IDLE;

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Set up PWM channels
  ledcSetup(RED_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(RED_PIN, RED_CHANNEL);

  ledcSetup(GREEN_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(GREEN_PIN, GREEN_CHANNEL);

  ledcSetup(BLUE_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(BLUE_PIN, BLUE_CHANNEL);
}

void setRGB(uint8_t r, uint8_t g, uint8_t b) {
  ledcWrite(RED_CHANNEL, r);
  ledcWrite(GREEN_CHANNEL, g);
  ledcWrite(BLUE_CHANNEL, b);
}

void loop() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    currentState = IDLE;
    Serial.println("Sensor error! State: IDLE");
    setRGB(0, 0, 0);
    delay(2000);
    return;
  }

  // Update heater state based on temp
  if (temp < 30.0) {
    currentState = HEATING;
  } else if (temp >= 30.0 && temp < 35.0) {
    currentState = STABILIZING;
  } else if (temp >= 35.0 && temp <= 35.5) {
    currentState = TARGET_REACHED;
  } else if (temp > 40.0) {
    currentState = OVERHEAT;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C  |  State: ");

  switch (currentState) {
    case IDLE:
      Serial.println("IDLE");
      setRGB(0, 0, 0);
      break;
    case HEATING:
      Serial.println("HEATING");
      setRGB(255, 0, 0); // Red
      break;
    case STABILIZING:
      Serial.println("STABILIZING");
      setRGB(255, 165, 0); // Orange
      break;
    case TARGET_REACHED:
      Serial.println("TARGET REACHED");
      setRGB(0, 255, 0); // Green
      break;
    case OVERHEAT:
      Serial.println("OVERHEAT! SHUTTING DOWN HEATER");
      setRGB(0, 0, 255); // Blue
      break;
  }

  delay(2000);
}
