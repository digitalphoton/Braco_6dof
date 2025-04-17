#include <controle.h>

Botao::Botao(char newID, uint8_t newPin) {
	id = newID;
	pin = newPin;
	prevState = false;
	curState = false;
}
void Botao::init(void) {
	pinMode(pin, INPUT_PULLUP);
}
void Botao::update(void) {
	prevState = curState;
	curState = (digitalRead(pin)) ? false : true;
}
bool Botao::getState(void) {
	return curState;
}
bool Botao::isRisingEdge(void) {
	return (curState && !prevState) ? true : false;
}
bool Botao::isFallingEdge(void) {
	return (!curState && prevState) ? true : false;
}

Potenciometro::Potenciometro(char newID, uint8_t newPin, float newOffset, float newDeadzone, float newValue) {
	id = newID;
	pin = newPin;
	offset = newOffset;
	deadzone = newDeadzone;
	value = newValue;
}
void Potenciometro::init(void) {
	pinMode(pin, INPUT);
}
void Potenciometro::update(void) {
	float valueRead = ((float)analogRead(pin) - 2047.5) / 2047.5 + offset;

	value = 0.0;
	if(valueRead > deadzone)
	{
		value = valueRead;
	}
	else if(valueRead < -deadzone)
	{
		value = valueRead;
	}
}
float Potenciometro::getValue(void) {
	return value;
}

Controle::Controle(ControleModos newModoAtual) {
	modoAtual = newModoAtual;
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
	if(botaoK.isRisingEdge()) {
		switch(modoAtual) {
			default:
			case ROTEXT: {
				modoAtual = PULSO;
				break;
			}
			case PULSO: {
				modoAtual = ROTEXT;
				break;
			}
		}
	}

	botaoA.update();
	botaoB.update();
	botaoC.update();
	botaoD.update();
}
ControleModos Controle::getModoAtual(void) {
	return modoAtual;
}
