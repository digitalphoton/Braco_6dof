#include <Arduino.h>

#ifndef SERVO_H
#define SERVO_H

#define _DEGREE_TO_DUTY(DEGREE) (DEGREE+180)*(0xffff)/(2400.0)
#define _DUTY_TO_DEGREE(DUTY) (uint16_t)(DUTY)*(2400.0)/(0xffff)-180

#define GLOBAL_PWM_RES 16
#define GLOBAL_PWM_FREQ 50

#define UPDATE_STEP 20
#define TOLERANCE 0.1
#define DEFAULT_FEEDRATE 60.0

class Servo
{
	uint8_t channel;
	uint8_t pin;

//	float minPosDegree;
//	float maxPosDegree;
//
//	float curPosDegree;
//	float targetPosDegree;
//	float stepValue;

	uint16_t minDuty;
	uint16_t maxDuty;

	uint16_t curDuty;
	uint16_t targetDuty;

	int16_t stepValue;
	int16_t stepCount;

	void setPosition(uint16_t newDuty);

	public:
	
	Servo(
		uint8_t newPin,
		uint8_t newChannel,
		float minPosDegree,
		float maxPosDegree,
		float initPosDegree
	);
	void init(void);
	void setFeedRate(float newFeedRate);
	float setTargetPosition(float posDegree/*, float newFeedRate*/);
	void step(void);

	void move(bool direction);
	void stop(void);
};
#endif
