#include <Wire.h>
#include <BH1750.h>
unsigned long pTime = 0;
const unsigned long interval1 = 1000*3; //eine sekunde*3
const int plantlight = 1000; //je nach pflanze varierent
const int planttimer = 1000*60*6; //eine sekunde * eine minute * anzahle stunden licht die es braucht
#include "DHT.h"                
#define Feucht A2          
#define DHTTYPE DHT11
DHT dht(Feucht, DHTTYPE);
BH1750 lightMeter;
#define Sensor2 A4
#define Sensor3 A3
#define Pump 12
#define SCL 2
#define SDA 3
#define LED 6
int sen2=0;
int sen3=0;
void setup() {
Serial.begin(9600);
dht.begin();
lightMeter.begin();
pinMode(Sensor2,INPUT);
pinMode(Sensor3,INPUT);
pinMode(Pump,OUTPUT);
pinMode(SCL,INPUT);
pinMode(SDA,INPUT);
pinMode(LED,OUTPUT);
}

void loop() {
  Serial.print("hello");
  unsigned long currentTime = millis();
  if (currentTime - pTime >= interval1) {
    pTime = currentTime;
    uint16_t lux = lightMeter.readLightLevel();
    float feu=dht.readHumidity();
    float temp=dht.readTemperature();
    /*FUNKTIONIERT*/
    /*sen2=analogRead(Sensor2);sen3=analogRead(Sensor3);*/
    sen2=100;sen3=100;
    Serial.print("Boden:");;Serial.print(sen2);Serial.print(sen3);Serial.println();
    Serial.print("Luft:");Serial.print(feu);Serial.println("%");
    Serial.print("Temperatur:");Serial.print(temp);Serial.println("°C");
    Serial.print("Licht:");Serial.print(lux);Serial.println("lx");
    if(sen2<500 && sen3<500) {
      digitalWrite(Pump,HIGH);
      Serial.print("allo");
    }
    else{digitalWrite(Pump,LOW);}

    if(lux<=plantlight){
      digitalWrite(LED,HIGH);
      }
    else{digitalWrite(LED,LOW);}
      
  }
}