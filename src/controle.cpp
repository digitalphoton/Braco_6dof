#include <controle.h>

Botao::Botao(char newID, uint8_t newPin) {

	id = newID;
	pin = newPin;

}
void Botao::init( void (*isr)() ) {

	pinMode(pin, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(pin), isr, CHANGE);

}
