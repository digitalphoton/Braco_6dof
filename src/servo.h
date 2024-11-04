#include <Arduino.h>

#ifndef SERVO_H
#define SERVO_H

#define GLOBAL_PWM_RES 16
#define GLOBAL_PWM_FREQ 50

#define UPDATE_STEP 20
#define TOLERANCE 0.1

class Servo
{
	uint8_t channel;
	uint8_t pin;

	float minPosDegree;
	float maxPosDegree;

	float curPosDegree;
	float targetPosDegree;
	float stepValue;

	void setPosition(float posDegree);

	public:
	
	Servo(
		uint8_t newPin,
		uint8_t newChannel,
		float minPosDegree,
		float maxPosDegree,
		float initPosDegree
	);
	void init(void);
	void setTargetPosition(float posDegree, float feedRate);
	void step(void);
};
#endif
