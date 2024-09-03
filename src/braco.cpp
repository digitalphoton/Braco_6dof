#include "braco.h"

void Braco::init(void)
{
  rotacao.init();
  rotacao.setPosition(0.0);

  ombro.init();
  ombro.setPosition(0.0);

  cotovelo.init();
  cotovelo.setPosition(0.0);

  pulsoFlexao.init();
  pulsoFlexao.setPosition(0.0);

  pulsoRotacao.init();
  pulsoRotacao.setPosition(0.0);

  garra.init();
  garra.setPosition(0.0);

  update();
}
void Braco::update(void)
{
	rotacao.setPosition(curRotacao);
	ombro.setPosition(curExtensao);
	cotovelo.setPosition(curExtensao);
	pulsoFlexao.setPosition(curPulsoFlexao);
	pulsoRotacao.setPosition(curPulsoRotacao);
	garra.setPosition(curGarra);
}

void Braco::setRotacao(float newRotacao)
{
	curRotacao = newRotacao;
}
void Braco::setExtensao(float newExtensao)
{
	curExtensao = newExtensao;
}
void Braco::setPulsoFlexao(float newPulsoFlexao)
{
	curPulsoFlexao = newPulsoFlexao;
}
void Braco::setPulsoRotacao(float newPulsoRotacao)
{
	curPulsoRotacao = newPulsoRotacao;
}
void Braco::setGarra(float newGarra)
{
	curGarra = newGarra;
}
