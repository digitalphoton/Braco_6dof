#include "braco.h"

void Braco::init(void)
{
  rotacao.init();
  ombro.init();
  cotovelo.init();
  pulsoFlexao.init();
  pulsoRotacao.init();
  garra.init();

  update();
}
void Braco::update(void)
{
	rotacao.setPosition(curRotacao);
	ombro.setPosition(curOmbro);
	cotovelo.setPosition(curCotovelo);
	pulsoFlexao.setPosition(curPulsoFlexao);
	pulsoRotacao.setPosition(curPulsoRotacao);
	garra.setPosition(curGarra);
	delay(UPDATE_DELAY);
}

void Braco::setRotacao(float newRotacao, bool doUpdate)
{
	curRotacao = newRotacao;
	if(doUpdate)
	{
		rotacao.setPosition(curRotacao);
		delay(UPDATE_DELAY);
	}
}
void Braco::setOmbro(float newOmbro, bool doUpdate)
{
	curOmbro= newOmbro;
	if(doUpdate)
	{
		ombro.setPosition(curOmbro);
		delay(UPDATE_DELAY);
	}
}
void Braco::setCotovelo(float newCotovelo, bool doUpdate)
{
	curCotovelo= newCotovelo;
	if(doUpdate)
	{
		cotovelo.setPosition(curCotovelo);
		delay(UPDATE_DELAY);
	}
}
void Braco::setPulsoFlexao(float newPulsoFlexao, bool doUpdate)
{
	curPulsoFlexao = newPulsoFlexao;
	if(doUpdate)
	{
		pulsoFlexao.setPosition(curPulsoFlexao);
		delay(UPDATE_DELAY);
	}
}
void Braco::setPulsoRotacao(float newPulsoRotacao, bool doUpdate)
{
	curPulsoRotacao = newPulsoRotacao;
	if(doUpdate)
	{
		pulsoRotacao.setPosition(curPulsoRotacao);
		delay(UPDATE_DELAY);
	}
}
void Braco::setGarra(float newGarra, bool doUpdate)
{
	curGarra = newGarra;
	if(doUpdate)
	{
		garra.setPosition(curGarra);
		delay(UPDATE_DELAY);
	}
}
