#ifndef __DAC_OCT_H__
#define __DAC_OCT_H__
#include <stdint.h>
class OctDac { 
public:
	OctDac(uint8_t ss, uint8_t din, uint8_t sck);
	void begin();
	void write(uint8_t chan, uint8_t val);
	void writeWord(uint16_t);
private:
	void writeBit(uint8_t val);
	void powerDownRelease();
	void iodaSelect();
	void ioStatusSelect();
	uint8_t reverseNibble(uint8_t);
	uint8_t _ss, _sck, _mosi;
	// void setCS(bool);
	// void setSCK(bool);
	// void setMOSI(bool);
};

#endif
