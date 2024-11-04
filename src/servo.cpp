#include "servo.h"

Servo::Servo(uint8_t newPin, uint8_t newChannel)
{
	channel = newChannel;
	pin = newPin;
}
void Servo::init(void)
{
	ledcAttachPin(pin, channel);
	ledcSetup(channel, GLOBAL_PWM_FREQ, GLOBAL_PWM_RES);
}
void Servo::setPosition(float newPosDegree)
{
	float delta = newPosDegree - curPosDegree;
	float stepValue = feedRate * 0.001 * UPDATE_STEP;
	unsigned long stepCount = abs( delta / stepValue );

	if(delta < 0)
	{
		stepValue = -stepValue;
	}


	for(stepCount; stepCount > 0; stepCount--)
	{
		unsigned long lastMillis = millis();

		curPosDegree += stepValue;

		uint16_t dutyCycle = (curPosDegree+180)/2400.0 * 0xffff;
		// O dutyCycle precisa ser invertido quando o servo é acionado via um
		// transistor NPN
		//dutyCycle = ~dutyCycle;
		ledcWrite(channel, dutyCycle);

		while( millis() < lastMillis + UPDATE_STEP);
	}
}
