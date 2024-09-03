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
void Servo::setPosition(float posDegree)
{
	uint16_t dutyCycle = (posDegree+120)/2400.0 * 0xffff;

	// O dutyCycle precisa ser invertido porque o servo é
	//	acionado via um transistor NPN
	dutyCycle = ~dutyCycle;

	ledcWrite(channel, dutyCycle);
}
