#include <Arduino.h>
#include "OctDac.h"
#define DEBUG
#include <debug.h>


OctDac::OctDac(uint8_t ss, uint8_t di, uint8_t sck){
	this->_ss = ss;
	this->_sck = sck;
	this->_mosi = di;
	// DDRB |= (1<<PB2) | (1<<PB3) | (1<<PB5);
	pinMode(_ss, OUTPUT);
	pinMode(_sck, OUTPUT);
	pinMode(_mosi, OUTPUT);
	// PORTB |= (1<<PB2);
	// PORTB |= (1<<PB5);
	digitalWrite(_ss, HIGH);
	digitalWrite(_sck, LOW);
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
		Serial.print(bit);
	}
	debug("\t Data: ");
	for (int i = 7; i >= 0; i--){
		uint16_t bit = (word >> i) & 1;
		Serial.print(bit);
	}
	Serial.println();
	digitalWrite(_ss, LOW);
//	setCS(false);
//	setSCK(false);
	for (int i = 11; i >= 0; i--){
		uint16_t bit = (word >> i) & 1;
		writeBit(bit);
	}
//	setSCK(true);
	digitalWrite(_ss, HIGH);
// /	setCS(true);
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
	digitalWrite(_sck, LOW);
//	setSCK(false);
//	setMOSI(val == 1);
	digitalWrite(_mosi, val);
	digitalWrite(_sck, HIGH);
	// sleep(1);
//	setSCK(true);
}
/*
void OctDac::setCS(bool state){
	if (state){
		PORTB |= (1<<PB2);
	} else{
		PORTB &= ~(1<<PB2);
	}
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
*/