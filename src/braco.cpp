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
}
