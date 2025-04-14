#include <controle.h>

Botao::Botao(char newID, uint8_t newPin) {
	id = newID;
	pin = newPin;
	state = false;
}
void Botao::init(void) {
	pinMode(pin, INPUT_PULLUP);
}
void Botao::update(void) {
	state = (digitalRead(pin)) ? false : true;
}
bool Botao::getState(void) {
	return state;
}

Potenciometro::Potenciometro(char newID, uint8_t newPin) {
	id = newID;
	pin = newPin;
	value = 0;
	offset = 0.045;
	deadzone = 0.1;
}
void Potenciometro::init(void) {
	pinMode(pin, INPUT);
}
void Potenciometro::update(void) {
	float valueRead = ((float)analogRead(pin) - 2047.5) / 2047.5 + offset;

	if(valueRead > deadzone || valueRead < -deadzone)
	{
		value = valueRead;
	}
	else
	{
		value = 0.0;
	}
}
float Potenciometro::getValue(void) {
	return value;
}

void Controle::init(void) {
	axisX.init();
	axisY.init();
	botaoK.init();

	botaoA.init();
	botaoB.init();
	botaoC.init();
	botaoD.init();
}
void Controle::update(void) {
	axisX.update();
	axisY.update();
	botaoK.update();

	botaoA.update();
	botaoB.update();
	botaoC.update();
	botaoD.update();
}
