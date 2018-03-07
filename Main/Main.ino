#include "Motor.h"

#define MotorA_EN 		3
#define MotorA_1		6
#define MotorA_2		7
#define MotorA_Invert	true

#define MotorB_EN 		5
#define MotorB_1		8
#define MotorB_2		9
#define MotorB_Invert	true

#define LED_PIN   13  

Motor MotorA(MotorA_EN, MotorA_1, MotorA_2, MotorA_Invert); 
Motor MotorB(MotorB_EN, MotorB_1, MotorB_2, MotorB_Invert);

void setup() {

	Serial.begin(9600);
	
}

void loop() {

	MotorA.SetSpeed(0);
	MotorB.SetSpeed(0);

}
