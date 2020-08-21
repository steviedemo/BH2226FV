#include <Arduino.h>
#include "OctDac.h"

OctDac::OctDac(uint8_t ss, uint8_t sck, uint8_t di){
	this->_ss = ss;
	this->_sck = sck;
	this->_mosi = di;
	pinMode(_ss, OUTPUT);
	pinMode(_sck, OUTPUT);
	pinMode(_mosi, OUTPUT);
	digitalWrite(_ss, HIGH);
	digitalWrite(_sck, HIGH);
}

void OctDac::write(uint8_t chan, uint8_t val){
	chan &= 0x0f;
	uint16_t word = ( chan << 8 ) | val;
	digitalWrite(_ss, LOW);
	digitalWrite(_sck, HIGH);
	for (uint8_t i = 11; i>=0; i--){
		bitBang((word >> i) & 1);
	}
	digitalWrite(_sck, LOW);
	digitalWrite(_ss, HIGH);	
}

void OctDac::writeValue(uint16_t word){

}

void OctDac::bitBang(uint8_t val){
	digitalWrite(_sck, LOW);
	digitalWrite(_mosi, val);
	digitalWrite(_sck, HIGH);
}