#include <Arduino.h>

#ifndef CONTROLE_H

class Botao {

	private:

	char id;
	uint8_t pin;
	bool state;
	unsigned long lastPressed;
	bool pollingNeeded;
	unsigned long lastPolled;

	public:

	Botao(char newID, uint8_t newPin);

	//void init(void (*isr)());
	void init();
	void update();

	//void setState(bool newState);
	bool getState(void);
	bool needsPolling(void);
	unsigned long getLastPressed(void);
};
class Potenciometro {

	private:

	char id;
	uint8_t pin;
	float value;
	float offset;
	float deadzone;
	float sensitivity;

	unsigned long lastPolled;

	public:

	Potenciometro(char newID, uint8_t newPin);

	void init(void);
	void update(void);
	float getValue(void);

};

class Controle {

	private:

	Potenciometro axisX{'X', 33};
	Potenciometro axisY{'Y', 34};

	public:

	void init(void);
	void update(void);

};

#endif
