#include <Wire.h>
#include <BH1750.h>
#include "DHT.h"

// Constants
const unsigned long INTERVAL = 1000 * 3;
const int PLANT_LIGHT = 1000;
const int PLANT_TIMER = 1000 * 60 * 6;
const int FEUCHT_PIN = A2;
const int DHT_TYPE = DHT11;
const int SENSOR2_PIN = A4;
const int SENSOR3_PIN = A3;
const int PUMP_PIN = 12;
const int SCL_PIN = 2;
const int SDA_PIN = 3;
const int LED_PIN = 6;

// Global variables
unsigned long previousTime = 0;
int sensor2 = 0;
int sensor3 = 0;

// Objects
DHT dht(FEUCHT_PIN, DHT_TYPE);
BH1750 lightMeter;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lightMeter.begin();
  pinMode(SENSOR2_PIN, INPUT);
  pinMode(SENSOR3_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(SCL_PIN, INPUT);
  pinMode(SDA_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  Serial.print("hello");
  unsigned long currentTime = millis();
 
  if (currentTime - previousTime >= INTERVAL) {
    previousTime = currentTime;
    uint16_t lux = lightMeter.readLightLevel();
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    sensor2 = analogRead(SENSOR2_PIN);
    sensor3 = analogRead(SENSOR3_PIN);

    Serial.print("Soil: ");
    Serial.print(sensor2);
    Serial.print(", ");
    Serial.print(sensor3);
    Serial.println();

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");

    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println("lx");

    if (sensor2 < 500 && sensor3 < 500) {
      digitalWrite(PUMP_PIN, HIGH);
      Serial.print("allo");
    } else {
      digitalWrite(PUMP_PIN, LOW);
    }

    if (lux <= PLANT_LIGHT) {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  }
}
