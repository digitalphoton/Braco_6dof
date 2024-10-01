#include <Arduino.h>
#include "braco.h"

Braco braco;

void setup()
{
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

  delay(2000);
  Serial.println("Braço inicializado!");
  delay(5000);
  
  braco.setOmbro(70.0);
  braco.setCotovelo(0.0);
  braco.setPulsoFlexao(-70.0);
  braco.update();
}

void loop()
{
  braco.setRotacao(-70.0);
  braco.setPulsoFlexao(-70.0);
  braco.setGarra(70.0);
  braco.setPulsoFlexao(0.0);
  braco.setRotacao(0.0);

  braco.setRotacao(70.0);
  braco.setPulsoFlexao(-70.0);
  braco.setGarra(0.0);
  braco.setPulsoFlexao(0.0);
  braco.setRotacao(0.0);

  braco.setRotacao(70.0);
  braco.setPulsoFlexao(-70.0);
  braco.setGarra(70.0);
  braco.setPulsoFlexao(0.0);
  braco.setRotacao(0.0);

  braco.setRotacao(-70.0);
  braco.setPulsoFlexao(-70.0);
  braco.setGarra(0.0);
  braco.setPulsoFlexao(0.0);
  braco.setRotacao(0.0);
}
