#include <Arduino.h>

#define SERVO_PWM_RES 16
#define SERVO_PWM_FREQ 50

class Servo
{
	uint8_t channel;
	uint8_t pin;

	public:
	
	Servo(uint8_t newChannel, uint8_t newPin);
	void init(void);
	void setPosition(float posDegree);
};
