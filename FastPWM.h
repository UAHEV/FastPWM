/*
 * FastPWM.h
 *
 *  Created on: Feb 25, 2017
 *      Author: Will
 */

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
