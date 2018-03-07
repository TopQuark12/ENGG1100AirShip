/*
Created by: Alex Wong Tat Hang
Date: 7/3/2018
*/

#include "Arduino.h"

#ifndef Motor_h
#define Motor_h

#define LOWER(x,y)		((x) < (y) ? (x) : (y))
#define HIGHER(x,y)		((x) > (y) ? (x) : (y))
#define MAXPWM			255

class Motor {

	public:
		Motor(uint8_t PIN_EN, uint8_t PIN_A, uint8_t PIN_B, uint8_t INVERT);
		void SetSpeed(int16_t speed);		
		void Stop(void);
	protected:
		int16_t Speed;
		uint8_t Direction;
	private:
		uint8_t	_PIN_A;
		uint8_t _PIN_B;
		uint8_t _PIN_EN;

};

#endif
