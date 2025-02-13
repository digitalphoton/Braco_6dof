#include "servo.h"

Servo::Servo( uint8_t newPin, uint8_t newChannel, float newMinPosDegree, float newMaxPosDegree, float initPosDegree)
{
	channel = newChannel;
	pin = newPin;
	minDuty = _DEGREE_TO_DUTY(newMinPosDegree);
	maxDuty = _DEGREE_TO_DUTY(newMaxPosDegree);
	curDuty = _DEGREE_TO_DUTY(initPosDegree);
	targetDuty = curDuty;
}
void Servo::init(void)
{
	ledcAttachPin(pin, channel);
	ledcSetup(channel, GLOBAL_PWM_FREQ, GLOBAL_PWM_RES);
	setPosition(curDuty);
	setFeedRate(DEFAULT_FEEDRATE);
}
void Servo::setPosition(uint16_t newDuty)
{
	ledcWrite(channel, newDuty);
}
void Servo::setFeedRate(float newFeedRate)
{
	stepValue = _DEGREE_TO_DUTY(newFeedRate * 0.001 * UPDATE_STEP);
}
float Servo::setTargetPosition(float newPosDegree/*, float newFeedRate*/)
{
	uint16_t newDuty = _DEGREE_TO_DUTY(newPosDegree);
//	setFeedRate(newFeedRate);

	if(newDuty > maxDuty)
	{
		newDuty = maxDuty;
	}
	if(newDuty < minDuty)
	{
		newDuty = minDuty;
	}

	stepCount = (newDuty - curDuty)/(stepValue);
	targetDuty = newDuty;

	return _DUTY_TO_DEGREE(targetDuty);
}
void Servo::step(void)
{
	// Nenhum passo para fazer
	if(stepCount == 0)
	{
		curDuty = targetDuty;
	}
	// stepCount é positivo quando estamos subindo e negativo quando descendo
	else if(stepCount > 0)
	{
		curDuty += stepValue;
		stepCount--;
	}
	else
	{
		curDuty -= stepValue;
		stepCount++	;
	}
	setPosition(curDuty);
}
