// 
// 
// 

#include "MotorC.h"
#include "Arduino.h"

void MotorSetSpeed(int16_t speed, MotorSetting motorconfig) {
	speed = LOWER(speed, MAXPWM);
	speed = HIGHER(speed, -MAXPWM);
	if (speed >= 0) {
		digitalWrite(motorconfig.PIN_A, LOW);
		digitalWrite(motorconfig.PIN_B, HIGH);
		analogWrite(motorconfig.PIN_EN, speed);
	} else {
		digitalWrite(motorconfig.PIN_A, HIGH);
		digitalWrite(motorconfig.PIN_B, LOW);
		analogWrite(motorconfig.PIN_EN, speed);
	}
}
