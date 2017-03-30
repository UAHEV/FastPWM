// FastPWM.cpp
//
// Copyright 2017 UAH Electric Vehicle Club
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// 	http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/* -------------------------------------------------------------- */
// The FastPWM Library, forked from Drew's original motor 
// controller by Will Boyd. The original code was partially based 
// off a demo from 
// "www.righto.com/2009/07/secrets-of-arduino-pwm.html"
/* -------------------------------------------------------------- */

#include "FastPWM.h"

FastPWM::FastPWM(int pin, int state, bool initialized, byte val, int OCR, int mapInHigh, int mapOutHigh, int lowWarning, int highWarning) {
	// TODO Auto-generated constructor stub

	this->pin = pin;
	this->state = state;
	this->initialized = initialized;
	this->val = val;
	this->OCR = OCR;
//	this->mapInLow = mapInLow;
	this->mapInHigh = mapInHigh;
//	this->mapOutLow = mapOutLow;
	this->mapOutHigh = mapOutHigh;
	this->lowWarning = lowWarning;
	this->highWarning = highWarning;

	this->pwmInit();

}

FastPWM::~FastPWM() {
	//Doesn't require code...
}

int FastPWM::getHighWarning() const {
	return highWarning;
}

void FastPWM::setHighWarning(int highWarning) {
	this->highWarning = highWarning;
}

bool FastPWM::isInitialized() const {
	return initialized;
}

void FastPWM::setInitialized(bool initialized) {
	this->initialized = initialized;
}

int FastPWM::getLowWarning() const {
	return lowWarning;
}

void FastPWM::setLowWarning(int lowWarning) {
	this->lowWarning = lowWarning;
}

int FastPWM::getMapInHigh() const {
	return mapInHigh;
}

void FastPWM::setMapInHigh(int mapInHigh) {
	this->mapInHigh = mapInHigh;
}

int FastPWM::getMapOutHigh() const {
	return mapOutHigh;
}

void FastPWM::setMapOutHigh(int mapOutHigh) {
	this->mapOutHigh = mapOutHigh;
}

int FastPWM::getOcr() const {
	return OCR;
}

void FastPWM::setOcr(int ocr) {
	OCR = ocr;
}

int FastPWM::getPin() const {
	return pin;
}

void FastPWM::setPin(int pin) {
	this->pin = pin;
}

int FastPWM::getState() const {
	return state;
}

void FastPWM::setState(int state) {

	//check the input
	switch (state) {

		case 1:
			this->state = 1;
			break;
		case 2:
			this->state = 2;
			break;
		case 3:
			this->state = 3;
			break;
		default:
			break;

	}

}

byte FastPWM::getVal() const {
	return val;
}

void FastPWM::setVal(byte val) {
	this->val = val;
	updateState();
	updateOutputCompareRegisterZero();
}

/* Implement Non-getter/setter functions */
//Private function
void FastPWM::pwmInit() {
  pinMode( this->pin, OUTPUT );

        //tccroa/b is the port for output compare register
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
  TCCR0B = _BV(WGM02) | _BV(CS01);
        //used to init the counter
  OCR0A = this->mapOutHigh;				//changed from 200, sets the Duty cycle for OCR0A
  OCR0B = 0;							//TODO: Allow for changing the duty cycle on ORC0B

  return;

}

void FastPWM::updateState() {
	//check to see if the new value is high, low, or acceptable
	
	if (this->val < this->mapValue(this->lowWarning)) {
		this->state = 1;
		this->initialized = false;
	}
	else if (this->val > this->mapValue(this->highWarning)) {
		this->state = 3;
		this->initialized = false;
	}
	else {
		this->state = 2;
	}

}


int FastPWM::mapValue(int value) {
	//map whatever the value is from the input to the output

	return map(value, 0, this->mapInHigh, 0, this->mapOutHigh);

}

void FastPWM::updateOutputCompareRegisterZero() {
	if (this->state == 1) {

		digitalWrite(this->pin, LOW);          //override OCR0A and force output low

	}

	else if (this->state == 3) {

		digitalWrite(this->pin, HIGH);        //override OCR0A and force output high

	}

	else if (this->state == 2) {

		if (!this->initialized) {

			pwmInit();
			this->initialized = true;

		}

		OCR0B = this->val;

	}
}
