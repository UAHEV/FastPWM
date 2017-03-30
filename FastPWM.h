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

#ifndef FASTPWM_FASTPWM_H_
#define FASTPWM_FASTPWM_H_

#include "Arduino.h"

class FastPWM {
public:
	FastPWM(int pin, int state, bool initialized, byte val, int OCR, int mapInHigh, int mapOutHigh, int lowWarning, int highWarning);
	virtual ~FastPWM();
	int getHighWarning() const;
	void setHighWarning(int highWarning);
	bool isInitialized() const;
	void setInitialized(bool initialized);
	int getLowWarning() const;
	void setLowWarning(int lowWarning);
	int getMapInHigh() const;
	void setMapInHigh(int mapInHigh);
	int getMapInLow() const;
	void setMapInLow(int mapInLow);
	int getMapOutHigh() const;
	void setMapOutHigh(int mapOutHigh);
	int getMapOutLow() const;
	void setMapOutLow(int mapOutLow);
	int getOcr() const;
	void setOcr(int ocr);
	int getPin() const;
	void setPin(int pin);
	int getState() const;
	void setState(int state);
	byte getVal() const;
	void setVal(byte val);
	void updateState();
	int mapValue(int value);
	void updateOutputCompareRegisterZero();

private:
	/* Original fastPWM struct variables */
	int pin;              	//pin
	int state;            	//current state of the OCR
	bool initialized;     	//whether we've initialized yet
	byte val;             	//value from 0-200 TODO: insure that we are always [0 -> 200]
	/* Added Variables */
	int OCR;				//which register to use (1-3)
//	int mapInLow;			//low value on the input
	int mapInHigh;			//high value on the input
//	int mapOutLow;			//low value on the output
	int mapOutHigh;			//high value on the output
	int lowWarning;			//the low value to manually override
	int highWarning;		//the high value to manually override

	/* Functions */
	void pwmInit();

};

#endif /* FASTPWM_FASTPWM_H_ */
