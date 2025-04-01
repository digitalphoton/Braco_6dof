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

class Controle {

	private:


	public:

	void init(void);

};

#endif
