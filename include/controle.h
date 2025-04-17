#include <Arduino.h>
#include <ServoBraco.h>

#ifndef CONTROLE_H

#define _VALUE_TO_DIRECTION(VALUE) ( (VALUE > 0.0) ? FORWARD : ((VALUE < 0.0) ? BACKWARD : STOP ) )

typedef enum {ROTEXT, PULSO} ControleModos;

class Botao {

	private:

	char id;
	uint8_t pin;
	bool prevState;
	bool curState;

	public:

	Botao(char newID, uint8_t newPin);

	void init();
	void update();
	bool getState(void);
	bool isRisingEdge(void);
	bool isFallingEdge(void);
};
class Potenciometro {

	private:

	char id;
	uint8_t pin;
	float offset;
	float deadzone;
	float sensitivity;
	float value;

	public:

	Potenciometro(char newID, uint8_t newPin, float newOffset = 0.045, float newDeadzone = 0.2, float newValue = 0.0);

	void init(void);
	void update(void);
	float getValue(void);

};

class Controle {

	private:

	ControleModos modoAtual;

	public:

	Controle(ControleModos newModoAtual = ROTEXT);

	Potenciometro axisX{'X', 36};
	Potenciometro axisY{'Y', 39};
	Botao botaoK{'K', 34};

	Botao botaoA{'A', 25};
	Botao botaoB{'B', 26};
	Botao botaoC{'C', 27};
	Botao botaoD{'D', 14};

	void init(void);
	void update(void);
	ControleModos getModoAtual(void);
};

#endif
