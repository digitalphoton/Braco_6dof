#include "servo.h"

Servo::Servo(uint8_t newChannel, uint8_t newPin)
{
	channel = newChannel;
	pin = newPin;
}
void Servo::init(void)
{
	ledcAttachPin(pin, channel);
	ledcSetup(channel, SERVO_PWM_FREQ, SERVO_PWM_FREQ);
}
void Servo::setPosition(float posDegree)
{
	uint16_t dutyCycle = posDegree/1200.0 * 0xffff;

	// O dutyCycle precisa ser invertido porque o servo é
	//	acionado via um transistor NPN
	dutyCycle = ~dutyCycle;

	ledcWrite(channel, dutyCycle);
}
