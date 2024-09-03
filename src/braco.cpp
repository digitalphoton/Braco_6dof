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
}

void Braco::setRotacao(float newRotacao)
{
	curRotacao = newRotacao;
}
void Braco::setOmbro(float newOmbro)
{
	curOmbro= newOmbro;
}
void Braco::setCotovelo(float newCotovelo)
{
	curCotovelo= newCotovelo;
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
