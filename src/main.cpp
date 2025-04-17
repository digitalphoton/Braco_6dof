#include <Arduino.h>
#include <ServoBraco.h>
#include <controle.h>

typedef enum {STARTUP, STANDBY, RECEIVING, MANUAL_CONTROL, UPDATING, LOGGING} Estados;

Braco braco;
Controle controle;
Estados estadoAtual;
Estados estadoProximo;

unsigned long g_tickLastPoll = 0;
unsigned long g_tickLastUpdate = 0;
unsigned long g_tickLastLog = 0;
unsigned long g_counter;

void setup() {
	estadoAtual = STARTUP;
	estadoProximo = STANDBY;

	Serial.begin(115200);
	while(!Serial);
	delay(1000);

	Serial.println(
		"Favor ligar fonte externa. Aperte Enter para continuar."
	);

	// Esperar entrada, e depois descartar os bytes recebidos
	while(!Serial.available());
	while(Serial.available() > 0) {
		Serial.read();
	}

	braco.init();
	controle.init();

	delay(2000);
	Serial.println("Braço inicializado!");
	delay(2000);
}

void loop() {
	unsigned long tickAtual = millis();
	char receiveBuffer[10];
	estadoAtual = estadoProximo;

	switch(estadoAtual) {
		default:
		case STANDBY:
			if(tickAtual >= g_tickLastUpdate + UPDATE_STEP)
			{
				estadoProximo = UPDATING;
			}
			else if(tickAtual > g_tickLastPoll)
			{
				estadoProximo = MANUAL_CONTROL;
			}
			else if(tickAtual >= g_tickLastLog + 1000)
			{
				estadoProximo = LOGGING;
			}
			else if(Serial.available())
			{
				estadoProximo = RECEIVING;
			}
			break;
		case UPDATING:
			braco.update();
			g_tickLastUpdate = tickAtual;

			estadoProximo = STANDBY;
			break;
		case MANUAL_CONTROL: {
			controle.update();

			switch(controle.getModoAtual())
			{
				default:
				case ROTEXT: {
					braco.rotacao.move(_VALUE_TO_DIRECTION(controle.axisX.getValue()));
					braco.ombro.move(_VALUE_TO_DIRECTION(controle.axisY.getValue()));
					break;
				}
				case PULSO: {
					braco.pulsoRotacao.move(_VALUE_TO_DIRECTION(controle.axisX.getValue()));
					braco.pulsoFlexao.move(_VALUE_TO_DIRECTION(controle.axisY.getValue()));
					break;
				}
			}

			g_tickLastPoll = tickAtual;
			estadoProximo = STANDBY;
			break;
		}
		case RECEIVING:
			for(uint8_t i; i < 10; i++)
			{
				receiveBuffer[i] = Serial.read();
				if(receiveBuffer[i] == '\n')
				{
					receiveBuffer[i] = '\0';
					break;
				}
			}
			// primeiro caractere vai para comando, o resto da string é
			// convertida para número e vai para argumento
			braco.atuar(receiveBuffer[0], atof(&receiveBuffer[1]));

			estadoProximo = STANDBY;
			break;
		case LOGGING:
			Serial.print("Eixo X = ");
			Serial.print(controle.axisX.getValue());
			Serial.print("; Eixo Y = ");
			Serial.print(controle.axisY.getValue());
			Serial.print("; Estado Botao = ");
			Serial.print(controle.botaoK.getState());
			Serial.print("; ciclos por segundo = ");
			Serial.print(g_counter);
			Serial.println();

			g_counter = 0;
			g_tickLastLog = tickAtual;
			estadoProximo = STANDBY;
			break;
	}
	g_counter++;
}
