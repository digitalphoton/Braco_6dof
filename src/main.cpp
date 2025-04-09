#include <Arduino.h>
#include <ServoBraco.h>
#include <controle.h>

#include <string>

// Intervalo de tempo entre updates, em millisegundos
#define UPDATE_STEP 20

typedef enum {STARTUP, STANDBY, RECEIVING, MANUAL_CONTROL, UPDATING, LOGGING} Estados;

Braco braco;
Estados estadoAtual;
Estados estadoProximo;

//unsigned long g_botaoLastPress = 0;
//bool g_botaoPressed = false;
//bool g_pollingNeeded = false;

Botao botao{'A', 13};
Potenciometro potenciometro{'Y', 34};

unsigned long g_tickLastPoll = 0;
unsigned long g_tickLastUpdate = 0;
unsigned long g_tickLastLog = 0;

void IRAM_ATTR botao_ISR(void);

void setup()
{
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
	while(Serial.available() > 0)
	{
		Serial.read();
	}

	braco.init();

	botao.init(botao_ISR);
	potenciometro.init();

	delay(2000);
	Serial.println("Braço inicializado!");
	delay(2000);
}

void loop()
{
	/*braco.setRotacao(-70.0, true);
	braco.setPulsoFlexao(-70.0, true);
	braco.setGarra(70.0, true);
	braco.setPulsoFlexao(0.0, true);
	braco.setRotacao(0.0, true);

	braco.setRotacao(70.0, true);
	braco.setPulsoFlexao(-70.0, true);
	braco.setGarra(0.0, true);
	braco.setPulsoFlexao(0.0, true);
	braco.setRotacao(0.0, true);

	braco.setRotacao(70.0, true);
	braco.setPulsoFlexao(-70.0, true);
	braco.setGarra(70.0, true);
	braco.setPulsoFlexao(0.0, true);
	braco.setRotacao(0.0, true);

	braco.setRotacao(-70.0, true);
	braco.setPulsoFlexao(-70.0, true);
	braco.setGarra(0.0, true);
	braco.setPulsoFlexao(0.0, true);
	braco.setRotacao(0.0, true);*/

	unsigned long tickAtual = millis();
	estadoAtual = estadoProximo;

	switch(estadoAtual)
	{
		default:
		case STANDBY:
		{
			if(tickAtual >= g_tickLastUpdate + UPDATE_STEP)
			{
				estadoProximo = UPDATING;
			}
			else if(tickAtual >= g_tickLastPoll + 3)
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
		}
		case UPDATING:
		{
			braco.update();
			g_tickLastUpdate = tickAtual;

			estadoProximo = STANDBY;
			break;
		}
		case MANUAL_CONTROL:
		{
			if(botao.getState())
			{
				braco.rotacao.move(true);
			}
			else
			{
				braco.rotacao.stop();
			}

			g_tickLastPoll = tickAtual;
			estadoProximo = STANDBY;
			break;
		}
		case RECEIVING:
		{
			char receiveBuffer[10];
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
			char comando = receiveBuffer[0];
			float argumento = atof(&receiveBuffer[1]);
			braco.atuar(comando, argumento);

			estadoProximo = STANDBY;
			break;
		}
		case LOGGING:
		{
			Serial.print("Valor Potenciometro = ");
			Serial.print(potenciometro.getValue());
			Serial.print("; Estado Botao = ");
			Serial.print(botao.getState());
			Serial.println();

			g_tickLastLog = tickAtual;
			estadoProximo = STANDBY;
			break;
		}
	}
}

void IRAM_ATTR botao_ISR(void)
{
	unsigned long now = millis();

	if(now >= botao.getLastPressed() + 50)
	{
		bool newState = (digitalRead(13)) ? false : true;
		botao.setState(newState);

		estadoProximo = MANUAL_CONTROL;
	}
}
