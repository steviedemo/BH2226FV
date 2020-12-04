#include <Arduino.h>
#include "OctDac_328.h"
//#define DEBUG
#include <debug.h>


OctDac::OctDac(uint8_t ss){
	this->_ss = ss;
	setOutputs();
	begin();
}

void OctDac::begin(){
	powerDownRelease();
	iodaSelect();
	ioStatusSelect();
	for (int i = 1; i < 9; i++){
		write(i, 0);
	}
}

void OctDac::write(uint8_t chan, uint8_t val){
	chan &= 0x0f;
	uint16_t word = 0;
	word = ((uint16_t) reverseNibble(chan)) << 8;
	word |= (uint16_t) val;
	writeWord(word);
}


void OctDac::powerDownRelease(){
	write(0b1001, 0x00);
}
void OctDac::iodaSelect(){
	write(0b1100, 0xff);
}
void OctDac::ioStatusSelect(){
	write(0x0f, 0xff);
}

void OctDac::writeWord(uint16_t word){
	
	word &= 0x0fff;
	debug("Word: ");
	debugf(word, BIN);
	debug("\tCommand: ");
	for (int i = 11; i >= 8; i--){
		uint16_t bit = (word >> i) & 1;
		debug(bit);
	}
	debug("\t Data: ");
	for (int i = 7; i >= 0; i--){
		uint16_t bit = (word >> i) & 1;
		debug(bit);
	}
	debugln();
	digitalWrite(_ss, LOW);
	for (int i = 11; i >= 0; i--){
		uint16_t bit = (word >> i) & 1;
		writeBit(bit);
	}
	digitalWrite(_ss, HIGH);
}

uint8_t OctDac::reverseNibble(uint8_t o){
	uint8_t v = 0;
	v |= ( (o >> 3) & 1) << 0;
	v |= ( (o >> 2) & 1) << 1;
	v |= ( (o >> 1) & 1) << 2;
	v |= ( (o >> 0) & 1) << 3;
	return v;
}



void OctDac::writeBit(uint8_t val){
	val &= 1;
	setSCK(false);
	setMOSI(val == 1);
	setSCK(true);
}

void OctDac::setOutputs(){
	pinMode(_ss, OUTPUT);
	DDRB |= (1<<PB3) | (1<<PB5);
	digitalWrite(_ss, HIGH);
	PORTB |= (1<<PB5);
}
void OctDac::setSCK(bool state){
	if (state){
		PORTB |= (1<<PB5);
	} else {
		PORTB &= ~(1<<PB5);
	}
}

void OctDac::setMOSI(bool state){
	if (state){
		PORTB |= (1<<PB3);
	} else {
		PORTB &= ~(1<<PB3);
	}
}