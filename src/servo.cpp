#include "servo.h"

Servo::Servo( uint8_t newPin, uint8_t newChannel, float newMinPosDegree, float newMaxPosDegree, float initPosDegree)
{
	channel = newChannel;
	pin = newPin;
	curPosDegree = initPosDegree;
	minPosDegree = newMinPosDegree;
	maxPosDegree = newMaxPosDegree;
}
void Servo::init(void)
{
	ledcAttachPin(pin, channel);
	ledcSetup(channel, GLOBAL_PWM_FREQ, GLOBAL_PWM_RES);
	setPosition(curPosDegree);
}
void Servo::setPosition(float posDegree)
{
	uint16_t dutyCycle = (curPosDegree+180)/2400.0 * 0xffff;
	// O dutyCycle precisa ser invertido quando o servo é acionado via um
	// transistor NPN
	//dutyCycle = ~dutyCycle;
	ledcWrite(channel, dutyCycle);
}
void Servo::setFeedRate(float newFeedRate)
{
	feedRate = newFeedRate;
}
void Servo::setTargetPosition(float newPosDegree)
{
	float delta = newPosDegree - curPosDegree;
	float stepValue = feedRate * 0.001 * UPDATE_STEP;
	//unsigned long stepCount = abs( delta / stepValue );

	if(delta < 0)
	{
		stepValue = -stepValue;
	}


/*
	for(stepCount; stepCount > 0; stepCount--)
	{
		unsigned long lastMillis = millis();

		curPosDegree += stepValue;

		setPosition(curPosDegree);

		while( millis() < lastMillis + UPDATE_STEP);
	}
*/
}
void Servo::step(void)
{
	if(stepValue == 0.0) 
	{
		return;
	}

	curPosDegree += stepValue;
	setPosition(curPosDegree);

	if( abs(curPosDegree - targetPosDegree) < TOLERANCE)
	{
		stepValue = 0.0;
	}
}
