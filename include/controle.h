#include <Arduino.h>

#ifndef CONTROLE_H

class Botao {

	private:

	char id;
	uint8_t pin;
	bool state;

	public:

	Botao(char newID, uint8_t newPin);
	void init(void (*isr)());

};

class Potenciometro {

	private:

	char id;
	uint8_t pin;
	int16_t value;

	public:

	Potenciometro(char newID, uint8_t newPin, int16_t value);

	void init();
	void getValue();

};

class Controle {

	private:


	public:

	void init(void);

};

#endif
