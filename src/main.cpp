#include <Arduino.h>
#include <ServoBraco.h>
#include <controle.h>

#include <string>

// Intervalo de tempo entre updates, em millisegundos
#define UPDATE_STEP 20

typedef enum {STARTUP, STANDBY, RECEIVING, MANUAL_CONTROL, UPDATING} Estados;

Braco braco;
Estados estado;

unsigned long g_botaoLastPress = 0;
bool g_botaoPressed = false;

Botao botao{'A', 13};

unsigned long g_tickLastUpdate = 0;

void IRAM_ATTR botao_ISR(void);

void setup()
{
	estado = STARTUP;

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

	estado = STANDBY;
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

	switch(estado)
	{
		default:
		case STANDBY:
		{
			if(tickAtual >= g_tickLastUpdate + UPDATE_STEP)
			{
				estado = UPDATING;
			}
			else if(g_botaoPressed)
			{
				estado = MANUAL_CONTROL;
			}
			else if(Serial.available())
			{
				estado = RECEIVING;
			}
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

			estado = STANDBY;
			break;
		}
		case MANUAL_CONTROL:
		{
			Serial.println("Botao!");
			estado = STANDBY;
			break;
		}
		case UPDATING:
		{
			braco.update();
			estado = STANDBY;
			g_tickLastUpdate = tickAtual;
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
	}
}
