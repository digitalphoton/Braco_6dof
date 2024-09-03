#include <Arduino.h>
#include "braco.h"

Braco braco;

void setup()
{
  braco.init();
  delay(5000);
  braco.setRotacao(60.0);
  braco.setExtensao(60.0);
  braco.setPulsoFlexao(60.0);
  braco.setPulsoRotacao(60.0);
}

void loop()
{
  braco.update();
}
