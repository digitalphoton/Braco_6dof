#include <Arduino.h>

#define GLOBAL_PWM_RES 16
#define GLOBAL_PWM_FREQ 50

class Servo
{
	uint8_t channel;
	uint8_t pin;

	public:
	
	Servo(uint8_t newPin, uint8_t newChannel);
	void init(void);
	void setPosition(float posDegree);
};
