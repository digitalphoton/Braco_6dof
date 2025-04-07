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
