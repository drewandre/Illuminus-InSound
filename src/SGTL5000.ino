// unsigned int readSGTL5000(unsigned int reg)
// {
// 	unsigned int val;
// 	Wire.beginTransmission(SGTL5000_I2C_ADDR_CS_LOW);
// 	Wire.write(reg >> 8);
// 	Wire.write(reg);
// 	Serial.print("Wire.endTransmission(false) = "); Serial.print(Wire.endTransmission(false));
// 	Serial.println();
// 	if (Wire.endTransmission(false) != 0) {
//     return 0;
//   }
// 	if (Wire.requestFrom((int)SGTL5000_I2C_ADDR_CS_LOW, 2) < 2) {
//     return 0;
//   }
// 	val = Wire.read() << 8;
// 	val |= Wire.read();
// 	Serial.println(val);
// 	return val;
// }
//
//
// bool writeSGTL5000(unsigned int reg, unsigned int val)
// {
// 	// if (reg == CHIP_ANA_CTRL) ana_ctrl = val;
// 	Wire.beginTransmission(SGTL5000_I2C_ADDR_CS_LOW);
// 	Wire.write(reg >> 8);
// 	Wire.write(reg);
// 	Wire.write(val >> 8);
// 	Wire.write(val);
// 	Serial.print("Wire.endTransmission(false) = "); Serial.print(Wire.endTransmission(false));
// 	Serial.println();
// 	if (Wire.endTransmission() == 0) return true;
// 	return false;
// }
//
// unsigned int modifySGTL5000(unsigned int reg, unsigned int val, unsigned int iMask)
// {
// 	unsigned int val1 = (readSGTL5000(reg)&(~iMask))|val;
// 	if(!writeSGTL5000(reg,val1)) return 0;
// 	return val1;
// }
