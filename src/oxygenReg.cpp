#include "oxygenReg.hpp"

#include <Arduino.h>
#include <ModbusRTU.h>
#if defined(ESP8266)
 #include <SoftwareSerial.h>
#endif

namespace O2 
{

#if defined(ESP8266)
 // connect RX to D2 (GPIO4, Arduino pin 4), TX to D1 (GPIO5, Arduino pin 4)
 SoftwareSerial* S;
#endif

ModbusRTU mb;

void initOxygenReg(const int RX_PIN, const int TX_PIN,
  const int MAX485_CTL_PIN) {
#if defined(ESP8266)
  S = new SoftwareSerial(RX_PIN, TX_PIN);
  (*S).begin(9600, SWSERIAL_8N1);
  mb.begin(S, MAX485_CTL_PIN);
#elif defined(ESP32)
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  mb.begin(&Serial2, MAX485_CTL_PIN);
#else
  Serial1.begin(9600, SERIAL_8N1);
  mb.begin(&Serial1);
  mb.setBaudrate(9600);
#endif
  mb.master();
}

void readOxygenReg(uint16_t* values, bool (*readOxygenRegCb)
  (Modbus::ResultCode event, uint16_t transactionId, void* data)) {
  if (!mb.slave()) {
    // uint16_t readHreg(uint8_t slaveId, uint16_t offset, uint16_t* value, uint16_t numregs = 1, cbTransaction cb = nullptr);
    // Serial.println("read");
    mb.readHreg(255, 1, values, 5, readOxygenRegCb);
  }
  mb.task();
}
} // namespace O2
