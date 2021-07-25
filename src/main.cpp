/*
  ModbusRTU ESP8266/ESP32
  Read multiple coils from slave device example
  (c)2019 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
  modified 13 May 2020
  by brainelectronics
  This code is licensed under the BSD New License. See LICENSE.txt for more info.
*/

#include <ModbusRTU.h>
#if defined(ESP8266)
 #include <SoftwareSerial.h>
 // SoftwareSerial S(D1, D2, false, 256);

 // receivePin, transmitPin, inverse_logic, bufSize, isrBufSize
 // connect RX to D2 (GPIO4, Arduino pin 4), TX to D1 (GPIO5, Arduino pin 4)
 SoftwareSerial S(4, 5);
#endif

#define RXD2 16
#define TXD2 17
ModbusRTU mb;

void setup() {
  Serial.begin(9600);
 #if defined(ESP8266)
  S.begin(9600, SWSERIAL_8N1);
  mb.begin(&S);
 #elif defined(ESP32)
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  mb.begin(&Serial2);
 #else
  Serial1.begin(9600, SERIAL_8N1);
  mb.begin(&Serial1);
  mb.setBaudrate(9600);
 #endif
  mb.master();
}

bool coils[20];
uint16_t values[5];


bool cbWrite(Modbus::ResultCode event, uint16_t transactionId, void* data) {
#ifdef ESP8266
  Serial.printf_P("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());
#elif ESP32
  Serial.printf_P("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());
  Serial.printf_P("Values: [Address: %d, 1: %d, 2: %d, 3: %d, 4: %d, 5: %d", 
    values[0], values[1], values[2], values[3], values[4]);
#else
  Serial.print("Request result: 0x");
  Serial.print(event, HEX);
#endif
  return true;
}


void loop() {
  if (!mb.slave()) {
    // uint16_t readHreg(uint8_t slaveId, uint16_t offset, uint16_t* value, uint16_t numregs = 1, cbTransaction cb = nullptr);
    mb.readHreg(255, 1, values, 5, cbWrite);
  }
  mb.task();
  yield();
}