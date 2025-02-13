#include "braco.h"

void Braco::init(void)
{
	rotacao.init();
	ombro.init();
	cotovelo.init();
	pulsoFlexao.init();
	pulsoRotacao.init();
	garra.init();

//	rotacao.setFeedRate(50.0);
//	ombro.setFeedRate(50.0);
//	cotovelo.setFeedRate(50.0);
//	pulsoFlexao.setFeedRate(50.0);
//	pulsoRotacao.setFeedRate(50.0);
//	garra.setFeedRate(50.0);

//	update();
}
void Braco::update(void)
{
	rotacao.step();
	ombro.step();
	cotovelo.step();
	pulsoFlexao.step();
	pulsoRotacao.step();
	garra.step();
	//delay(UPDATE_DELAY);
}

/*
void Braco::setRotacao(float newRotacao, bool doUpdate)
{
	//curRotacao = newRotacao;
	//if(doUpdate)
	//{
	//	rotacao.setPosition(curRotacao);
	//	delay(UPDATE_DELAY);
	//}

	float stepValue = (newRotacao > curRotacao)? STEP_SIZE : -STEP_SIZE;
	unsigned long stepCount = abs(newRotacao - curRotacao)/(STEP_SIZE);
	
	// Incrementar curRotacao até chegar em newRotacao
	for(stepCount; stepCount > 0; stepCount--)
	{
		unsigned long lastMillis = millis();

		curRotacao+= stepValue;

		rotacao.setPosition(curRotacao);
		//Serial.print("    Atual: ");
		//Serial.println(newPosition);

		while(millis() < lastMillis + UPDATE_STEP);
	}
}
void Braco::setOmbro(float newOmbro, bool doUpdate)
{
	//curOmbro= newOmbro;
	//if(doUpdate)
	//{
	//	ombro.setPosition(curOmbro);
	//	delay(UPDATE_DELAY);
	//}

	float stepValue = (newOmbro > curOmbro)? STEP_SIZE : -STEP_SIZE;
	unsigned long stepCount = abs(newOmbro - curOmbro)/(STEP_SIZE);
	
	// Incrementar curOmbro até chegar em newOmbro
	for(stepCount; stepCount > 0; stepCount--)
	{
		unsigned long lastMillis = millis();

		curOmbro+= stepValue;

		ombro.setPosition(curOmbro);
		//Serial.print("    Atual: ");
		//Serial.println(newPosition);

		while(millis() < lastMillis + UPDATE_STEP);
	}
}
void Braco::setCotovelo(float newCotovelo, bool doUpdate)
{
	//curCotovelo= newCotovelo;
	//if(doUpdate)
	//{
	//	cotovelo.setPosition(curCotovelo);
	//	delay(UPDATE_DELAY);
	//}

	float stepValue = (newCotovelo > curCotovelo)? STEP_SIZE : -STEP_SIZE;
	unsigned long stepCount = abs(newCotovelo - curCotovelo)/(STEP_SIZE);
	
	// Incrementar curCotovelo até chegar em newCotovelo
	for(stepCount; stepCount > 0; stepCount--)
	{
		unsigned long lastMillis = millis();

		curCotovelo+= stepValue;

		cotovelo.setPosition(curCotovelo);
		//Serial.print("    Atual: ");
		//Serial.println(newPosition);

		while(millis() < lastMillis + UPDATE_STEP);
	}
}
void Braco::setPulsoFlexao(float newPulsoFlexao, bool doUpdate)
{
	//curPulsoFlexao = newPulsoFlexao;
	//if(doUpdate)
	//{
	//	pulsoFlexao.setPosition(curPulsoFlexao);
	//	delay(UPDATE_DELAY);
	//}

	float stepValue = (newPulsoFlexao > curPulsoFlexao)? STEP_SIZE : -STEP_SIZE;
	unsigned long stepCount = abs(newPulsoFlexao - curPulsoFlexao)/(STEP_SIZE);
	
	// Incrementar curPulsoFlexao até chegar em newPulsoFlexao
	for(stepCount; stepCount > 0; stepCount--)
	{
		unsigned long lastMillis = millis();

		curPulsoFlexao+= stepValue;

		pulsoFlexao.setPosition(curPulsoFlexao);
		//Serial.print("    Atual: ");
		//Serial.println(newPosition);

		while(millis() < lastMillis + UPDATE_STEP);
	}
}
void Braco::setPulsoRotacao(float newPulsoRotacao, bool doUpdate)
{
	//curPulsoRotacao = newPulsoRotacao;
	//if(doUpdate)
	//{
	//	pulsoRotacao.setPosition(curPulsoRotacao);
	//	delay(UPDATE_DELAY);
	//}

	float stepValue = (newPulsoRotacao > curPulsoRotacao)? STEP_SIZE : -STEP_SIZE;
	unsigned long stepCount = abs(newPulsoRotacao - curPulsoRotacao)/(STEP_SIZE);
	
	// Incrementar curPulsoRotacao até chegar em newPulsoRotacao
	for(stepCount; stepCount > 0; stepCount--)
	{
		unsigned long lastMillis = millis();

		curPulsoRotacao+= stepValue;

		pulsoRotacao.setPosition(curPulsoRotacao);
		//Serial.print("    Atual: ");
		//Serial.println(newPosition);

		while(millis() < lastMillis + UPDATE_STEP);
	}
}
void Braco::setGarra(float newGarra, bool doUpdate)
{
	//curGarra = newGarra;
	//if(doUpdate)
	//{
	//	garra.setPosition(curGarra);
	//	delay(UPDATE_DELAY);
	//}

	//Serial.print("Garra! Origem:");
	//Serial.print(curGarra);
	//Serial.print("Destino: ");
	//Serial.println(newGarra);

	float stepValue = (newGarra > curGarra)? STEP_SIZE : -STEP_SIZE;
	unsigned long stepCount = abs(newGarra - curGarra)/(STEP_SIZE);

	// Incrementar curGarra até chegar em newGarra
	for(stepCount; stepCount > 0; stepCount--)
	{
		unsigned long lastMillis = millis();

		curGarra += stepValue;

		garra.setPosition(curGarra);
		//Serial.print("    Atual: ");
		//Serial.println(newPosition);

		while(millis() < lastMillis + UPDATE_STEP);
	}
}
*/

// recebe um comando e um argumento, atua o servo respectivo
void Braco::atuar(char comando, float argumento)
{
	switch(comando)
	{
		default:
			Serial.println("Comando não reconhecido!");
			return;
		
		case 'Q':
		case 'q':
			Serial.print("Rotação definida para ");
			Serial.print( rotacao.setTargetPosition(argumento) );
			break;
			
		case 'W':
		case 'w':
			Serial.print("Posição do Ombro definida para ");
			Serial.print( ombro.setTargetPosition(argumento) );
			break;

		case 'E':
		case 'e':
			Serial.print("Posição do Cotovelo definida para ");
			Serial.print( cotovelo.setTargetPosition(argumento) );
			break;

		case 'R':
		case 'r':
			Serial.print("Flexão do Pulso definida para ");
			Serial.print( pulsoFlexao.setTargetPosition(argumento) );
			break;

		case 'T':
		case 't':
			Serial.print("Rotacao do Pulso definida para ");
			Serial.print( pulsoRotacao.setTargetPosition(argumento) );
			break;

		case 'F':
		case 'f':
			Serial.print("Posição da Garra definida para ");
			Serial.print( garra.setTargetPosition(argumento) );
			break;
	}
	Serial.println();
}
