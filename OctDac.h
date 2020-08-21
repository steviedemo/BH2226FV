#ifndef __DAC_OCT_H__
#define __DAC_OCT_H__
#include <stdint.h>
class OctDac { 
public:
	OctDac(uint8_t ss, uint8_t sck, uint8_t di);
	void write(uint8_t chan, uint8_t val);
private:
	void bitBang(uint8_t val);
	uint8_t _ss, _sck, _mosi;

};

#endif
