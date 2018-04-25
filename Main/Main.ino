/*
Created by: Alex Wong Tat Hang
Date: 7/3/2018
*/
//#include "Motor.h"

#include "MotorC.h"

#define MotorA_EN 		3   //OK
#define MotorA_1		  2
#define MotorA_2		  4
#define MotorA_Invert	true

#define MotorB_EN 		5   //OK
#define MotorB_1		  7
#define MotorB_2		  8
#define MotorB_Invert	true

#define MotorC_EN     6   //OK
#define MotorC_1      13
#define MotorC_2      11
#define MotorC_Invert true

#define MotorD_EN     9   //OK
#define MotorD_1      14
#define MotorD_2      15
#define MotorD_Invert true

#define MotorE_EN     10    //OK
#define MotorE_1      16
#define MotorE_2      17
#define MotorE_Invert true

#define MotorF_EN     12    //OK
#define MotorF_1      18
#define MotorF_2      19
#define MotorF_Invert true

#define NUMMOTORS		4

#define USENEWDECODE

#define RXBUFFERLENGTH	20

static MotorSetting motors[4];

char RxBuffer[RXBUFFERLENGTH];

//Motor MotorA(MotorA_EN, MotorA_1, MotorA_2, MotorA_Invert); 
//Motor MotorB(MotorB_EN, MotorB_1, MotorB_2, MotorB_Invert);
////Motor MotorC(MotorC_EN, MotorC_1, MotorC_2, MotorC_Invert);
//Motor MotorD(MotorD_EN, MotorD_1, MotorD_2, MotorD_Invert);
//Motor MotorE(MotorE_EN, MotorE_1, MotorE_2, MotorE_Invert);
////Motor MotorF(MotorF_EN, MotorF_1, MotorF_2, MotorF_Invert);



void SerialDecode(char* buffer) {

	static bool found;
	static bool negative;
	static int16_t power;
	static uint8_t motornum;
	static uint8_t i;

	for (i = 0; i < RXBUFFERLENGTH; i++) {
		if ((*buffer == '@') && (*(buffer + 2) == ':')) {
			power = 0;
			negative = false;
			buffer += 1;
			motornum = *buffer;
			buffer += 2;
			while (*buffer != '&') {
				if (*buffer == '-') {
					negative = true;
				}
				else {
					power = power * 10 + (*buffer + 1);
				}
				buffer++;
			}
			power = negative ? -power : power;
			MotorSetSpeed(power, motors[motornum]);
		}

	}
}



void setup() {

	memcpy((void*) RxBuffer, 0, RXBUFFERLENGTH);
	memcpy((void*) motors, 0, sizeof(MotorSetting) * 4);
	motors[0].PIN_A = MotorA_1;
	motors[0].PIN_B = MotorA_2;
	motors[0].PIN_EN = MotorA_EN;
	motors[1].PIN_A = MotorB_1;
	motors[1].PIN_B = MotorB_2;
	motors[1].PIN_EN = MotorB_EN;
	motors[2].PIN_A = MotorD_1;
	motors[2].PIN_B = MotorD_2;
	motors[2].PIN_EN = MotorD_EN;
	motors[3].PIN_A = MotorE_1;
	motors[3].PIN_B = MotorE_2;
	motors[3].PIN_EN = MotorE_EN;
	Serial.begin(9600);
	
}

void loop() {

	static uint8_t i = 0;
	static bool ended = 0;
	if (Serial.available()) {
		ended = false;
		while (Serial.available() > 0 && i < RXBUFFERLENGTH) {
			RxBuffer[i] = Serial.read();
			ended = RxBuffer[i] = '&' ? true : false;
			i++;
		}
		if (ended) {
			ended = false;
			SerialDecode(RxBuffer);
			memcpy((void*)RxBuffer, 0, RXBUFFERLENGTH);
		}
	}	

}
