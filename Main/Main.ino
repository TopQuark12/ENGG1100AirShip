/*
Created by: Alex Wong Tat Hang
Date: 7/3/2018
*/
#include "Motor.h"

#define MotorA_EN 		3
#define MotorA_1		6
#define MotorA_2		7
#define MotorA_Invert	true

#define MotorB_EN 		5
#define MotorB_1		8
#define MotorB_2		9
#define MotorB_Invert	true

#define LED_PIN   		13  

#define RXBUFFERLENGTH	20

char RxBuffer[RXBUFFERLENGTH];

Motor MotorA(MotorA_EN, MotorA_1, MotorA_2, MotorA_Invert); 
Motor MotorB(MotorB_EN, MotorB_1, MotorB_2, MotorB_Invert);

void SerialDecode(char* buffer) {

	static bool found;
	static bool negative;
	static int16_t power;
	for(uint8_t i = 0; i < RXBUFFERLENGTH; i++) {
		if ((*buffer == '1')  &&  (*(buffer + 1) == ':')) {
			power = 0;
			negative = false;
			buffer += 2;
			while (*buffer != '&'){
				if (*buffer == '-') {
					negative = true;
				} else {
					power = power * 10 +(*buffer - '0');
				}
				buffer++;
			}
			power = negative ? -power : power;
			MotorA.SetSpeed(power);
		} else if ((*buffer == '2')  &&  (*(buffer + 1) == ':')) {
			power = 0;
			negative = false;
			buffer += 2;
			while (*buffer != '&'){
				if (*buffer == '-') {
					negative = true;
				} else {
					power = power * 10 +(*buffer - '0');
				}
				buffer++;
			}
			power = negative ? -power : power;
			MotorB.SetSpeed(power);
		}
		buffer++;
	}

}

void setup() {

	memcpy((void*) RxBuffer, 0, RXBUFFERLENGTH);
	Serial.begin(9600);
	
}

void loop() {

	static uint8_t i;
	i = 0;
	if (Serial.available()) {
		while(RxBuffer[i-1] != '&') {
			while(!Serial.available()){

			}
			RxBuffer[i] = Serial.read();
			Serial.print(RxBuffer[i]);
			i++;
		}
		//Serial.println();
		SerialDecode(RxBuffer);
		memcpy((void*) RxBuffer, 0, RXBUFFERLENGTH);
	}	

}
