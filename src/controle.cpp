#include <controle.h>

Botao::Botao(char newID, uint8_t newPin) {

	id = newID;
	pin = newPin;
	state = false;
	lastPressed = 0;
	pollingNeeded = false;

}
void Botao::init( void (*isr)() ) {

	pinMode(pin, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(pin), isr, CHANGE);

}
void Botao::setState(bool newState) {

	state = newState;
	lastPressed = millis();
	pollingNeeded = true;

}
bool Botao::getState(void) {

	pollingNeeded = false;
	lastPolled = millis();
	return state;

}
bool Botao::needsPolling(void) {

	return pollingNeeded;

}
unsigned long Botao::getLastPressed(void) {

	return lastPressed;

}

Potenciometro::Potenciometro(char newID, uint8_t newPin)
{
	id = newID;
	pin = newPin;
	value = 0;
}

void Potenciometro::init(void)
{
	pinMode(pin, INPUT);
}

float Potenciometro::getValue(void)
{
	float valueRead = ((float)analogRead(pin) - 2047.5) / 2047.5 + offset;

	if(valueRead > deadzone || valueRead < -deadzone)
	{
		value = valueRead;
	}
	else
	{
		value = 0.0;
	}
	return value;
}
