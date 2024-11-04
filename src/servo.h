#include <Arduino.h>

#ifndef SERVO_H
#define SERVO_H

#define GLOBAL_PWM_RES 16
#define GLOBAL_PWM_FREQ 50

#define UPDATE_STEP 20

class Servo
{
	uint8_t channel;
	uint8_t pin;
	float curPosDegree;
	float feedRate;

	public:
	
	Servo(uint8_t newPin, uint8_t newChannel);
	void init(void);
	void setPosition(float posDegree);
};
#endif
