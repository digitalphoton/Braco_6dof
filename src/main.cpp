#include <Arduino.h>
#include "braco.h"

Braco braco;

void setup()
{
  braco.init();
  delay(2000);
  braco.setOmbro(70.0);
  braco.setCotovelo(0.0);
  braco.setPulsoFlexao(-70.0);
  braco.update();
}

void loop()
{
}
