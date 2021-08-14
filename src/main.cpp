/*
  ModbusRTU ESP8266/ESP32
  Read multiple coils from slave device example
  (c)2019 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
  modified 13 May 2020
  by brainelectronics
  This code is licensed under the BSD New License. See LICENSE.txt for more info.
*/
#include "oxygenReg.hpp"
#include "network.hpp"

#include <Arduino.h>

#ifdef ESP32
#define RXD2 16
#define TXD2 17
#define MAX485_RE_NEG 4
#else
#define RXD2 5
#define TXD2 4
#define MAX485_RE_NEG D3
#endif

// #define HTX_TEST

uint16_t values[5];

const char* OXYGEN_FORMAT = "{\"slpm\": %d}";
const char* OXYGEN_TOPIC = "sensor/oxygen";

void testSetup();
void testLoop();

bool cbWrite(Modbus::ResultCode event, uint16_t transactionId,
  void* data);


void setup() {
#ifdef HTX_TEST
  testSetup();
  return;
#endif
  // Serial.begin(9600);
  // Serial.println("init");
  net::connectToWifi();
  net::connectToMQTT();
  O2::initOxygenReg(RXD2, TXD2, MAX485_RE_NEG);  
  // Serial.println("wf connect");
}

void loop() {
#ifdef HTX_TEST
  testLoop();
  return;
#endif
  O2::readOxygenReg(values, cbWrite);
  net::checkConnection();
}

bool cbWrite(Modbus::ResultCode event, uint16_t transactionId,
  void* data) {
#ifdef ESP8266
  // Serial.printf_P("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());
#elif ESP32
  Serial.printf_P("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());
#else
  Serial.print("Request result: 0x");
  Serial.print(event, HEX);
#endif
  // Serial.printf_P("Values: [Address: %d, 1: %d, 2: %d, 3: %d, 4: %d, 5: %d", 
  //   values[0], values[1], values[2], values[3], values[4]);
  char jsonObj[512];
  sprintf(jsonObj, OXYGEN_FORMAT, values[2]);
  net::publishToMQTT(OXYGEN_TOPIC, jsonObj);
  return true;
}

void testSetup() {
  Serial.begin(9600);
  net::connectToWifi();
  net::connectToMQTT();
  // Serial.println("wf connect");
  values[2] = 0.1;

}

void testLoop() {
  net::checkConnection();
  char jsonObj[512];
  sprintf(jsonObj, OXYGEN_FORMAT, values[2]);
  net::publishToMQTT(OXYGEN_TOPIC, jsonObj);
}