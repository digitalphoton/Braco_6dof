#include <Arduino.h>
#include "braco.h"

Braco braco;

void setup()
{
  braco.init();
  delay(2000);
}

void loop()
{
  braco.setPulsoFlexao(-60.0);
  braco.update();
  delay(2000);

  braco.setPulsoFlexao(60.0);
  braco.update();
  delay(2000);
}
