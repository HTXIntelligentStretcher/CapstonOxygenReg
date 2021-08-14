#ifndef OXYGEN_REG_HPP
#define OXYGEN_REG_HPP

#include <ModbusRTU.h>

namespace O2 
{

void initOxygenReg(const int RX_PIN, const int TX_PIN,
  const int MAX485_CTL_PIN);
void readOxygenReg(uint16_t* values, bool (*readOxygenRegCb)
  (Modbus::ResultCode event, uint16_t transactionId, void* data));

} // namespace O2

#endif // Oxygen_reg_hpp