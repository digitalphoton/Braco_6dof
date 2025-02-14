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
	// calcular quantos degraus por passo
	float degreePerStep = newFeedRate * 0.001 * UPDATE_STEP;
	// achar o valor para incrementar o duty cycle por passo
	stepValue = (degreePerStep)*(0xffff)/(2400.0);
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
	// stepCount é positivo quando estamos subindo e negativo quando descendo
	if(stepCount > 0 && curDuty < maxDuty)
	{
		curDuty += stepValue;
		stepCount--;
	}
	else if(stepCount < 0 && curDuty > minDuty)
	{
		curDuty -= stepValue;
		stepCount++	;
	}
	// Nenhum passo para fazer
	else
	{
		curDuty = targetDuty;
		stepCount = 0;
	}
	setPosition(curDuty);
}
void Servo::move(bool direction)
{
	switch(direction)
	{
		default:
		case true:
		{
			targetDuty = maxDuty;
			stepCount = 0x7fff;
			break;
		}
		case false:
		{
			targetDuty = minDuty;
			stepCount = -0x7fff;
			break;
		}
	}
}
void Servo::stop(void)
{
	stepCount = 0;
	targetDuty = curDuty;
}
