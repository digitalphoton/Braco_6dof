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
