// MotorC.h

#ifndef _MOTORC_h
#define _MOTORC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define LOWER(x,y)		((x) < (y) ? (x) : (y))
#define HIGHER(x,y)		((x) > (y) ? (x) : (y))
#define MAXPWM			255

typedef struct {
	uint8_t PIN_A;
	uint8_t PIN_B;
	uint8_t PIN_EN;
}MotorSetting;

void MotorSetSpeed(int16_t speed, MotorSetting motorconfig);

#endif

