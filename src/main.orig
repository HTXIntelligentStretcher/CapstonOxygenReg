#include <Arduino.h>
#include <WiFi.h>
#include "network.hpp"

#define RXD2 16
#define TXD2 17

void pubMQTTTask(void *param);

int oxygenBuffer = -1;

void setup() 
{ 
  // Serial.begin(9600);
  net::connectToWifi();
  net::connectToMQTT();
  xTaskCreate(&pubMQTTTask, "pub task", 10000, NULL, 1, NULL);
  delay(1500);
  // Serial.println("Starting shit");
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);   
} 
 
void loop() 
{ 
  if (Serial2.available()) {
    oxygenBuffer = Serial2.read();
  }
  net::checkConnection();
}   

void pubMQTTTask(void *param) {
  while(1) {
    char jsonStr[] = "{\"slpm\": %d}";
    char jsonObj[512];
    sprintf(jsonObj, jsonStr, oxygenBuffer);
    Serial.println(jsonObj);
    net::publishToMQTT(jsonObj);
    vTaskDelay(300);

  }
}