#include <Arduino.h>
#include <ServoBraco.h>
#include <controle.h>

#include <string>

// Intervalo de tempo entre updates, em millisegundos
#define UPDATE_STEP 20

typedef enum {STARTUP, STANDBY, RECEIVING, MANUAL_CONTROL, UPDATING} Estados;

Braco braco;
Estados estadoAtual;
Estados estadoProximo;

unsigned long g_botaoLastPress = 0;
bool g_botaoPressed = false;
bool g_pollingNeeded = false;

Botao botao{'A', 13};

unsigned long g_tickLastPoll = 0;
unsigned long g_tickLastUpdate = 0;

void IRAM_ATTR botao_ISR(void);

void setup()
{
	estadoAtual = STARTUP;

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

	delay(2000);
	Serial.println("Braço inicializado!");
	delay(2000);

	estadoAtual = STANDBY;
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
	estadoProximo = STANDBY;

	switch(estadoAtual)
	{
		default:
		case STANDBY:
		{
			if(tickAtual >= g_tickLastUpdate + UPDATE_STEP)
			{
				estadoProximo = UPDATING;
			}
			else if(tickAtual >= g_tickLastPoll + 2 && g_pollingNeeded)
			{
				estadoProximo = MANUAL_CONTROL;
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
			estadoProximo = STANDBY;
			g_tickLastUpdate = tickAtual;
			break;
		}
		case MANUAL_CONTROL:
		{
			if(g_botaoPressed)
			{
				Serial.println("Botao apertado!");
				braco.rotacao.move(true);
			}
			else
			{
				Serial.println("Botao solto!");
				braco.rotacao.stop();
			}

			g_pollingNeeded = false;
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
	}
}

void IRAM_ATTR botao_ISR(void)
{
	unsigned long now = millis();

	if(now >= g_botaoLastPress + 50)
	{
		g_botaoPressed = (digitalRead(13)) ? false : true;
		g_botaoLastPress = now;
		g_pollingNeeded = true;

		estadoProximo = MANUAL_CONTROL;
	}
}
