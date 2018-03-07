/*
Created by: Alex Wong Tat Hang
Date: 7/3/2018
*/

#include "Arduino.h"
#include "digitalWriteFast.h"
#include "Motor.h"

Motor::Motor(uint8_t PIN_EN, uint8_t PIN_A, uint8_t PIN_B, uint8_t INVERT) {
	pinMode(PIN_A, OUTPUT);
	_PIN_A = INVERT ? PIN_A : PIN_B;
	pinMode(PIN_B, OUTPUT);
	_PIN_B = INVERT ? PIN_B : PIN_A;
	_PIN_EN = PIN_EN;
	Speed = 0;
	Direction = 0;
}

void Motor::SetSpeed(int16_t speed) {
	Speed = LOWER(speed, MAXPWM);
	Speed = HIGHER(speed, -MAXPWM);
	if (Speed >= 0) {
		digitalWrite(_PIN_A, HIGH);
		digitalWrite(_PIN_B, LOW);
		analogWrite(_PIN_EN, Speed);
	} else {
		digitalWrite(_PIN_A, LOW);
		digitalWrite(_PIN_B, HIGH);
		analogWrite(_PIN_EN, -Speed);
	}
}

void Motor::Stop(void) {
	analogWrite(_PIN_EN, 0);
}
