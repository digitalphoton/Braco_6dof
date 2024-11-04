#include <Arduino.h>
#include "servo.h"

#ifndef BRACO_H
#define BRACO_H

#define ROTACAO_PIN 15
#define ROTACAO_CH 0
#define OMBRO_PIN 2
#define OMBRO_CH 1
#define COTOVELO_PIN 4
#define COTOVELO_CH 2
#define PULSOFLEXAO_PIN 16
#define PULSOFLEXAO_CH 3
#define PULSOROTACAO_PIN 17
#define PULSOROTACAO_CH 4
#define GARRA_PIN 5
#define GARRA_CH 5

#define UPDATE_DELAY 3000
// Feedrate em graus por egundo
#define FEEDRATE 50.0
// Intervalo de tempo entre updates, em millisegundos
#define UPDATE_STEP 20
#define STEP_SIZE (FEEDRATE * 0.001 * UPDATE_STEP)

class Braco
{
  float curRotacao;
  float curOmbro;
  float curCotovelo;
  float curPulsoFlexao;
  float curPulsoRotacao;
  float curGarra;

  public:

  Servo rotacao{ROTACAO_PIN, ROTACAO_CH, -70.0, +70.0, 0.0};
  Servo ombro{OMBRO_PIN, OMBRO_CH, 0.0, +70.0, +70.0};
  Servo cotovelo{COTOVELO_PIN, COTOVELO_CH, -70.0, +70.0, -70.0};
  Servo pulsoFlexao{PULSOFLEXAO_PIN, PULSOFLEXAO_CH, -70.0, 0.0, -70.0};
  Servo pulsoRotacao{PULSOROTACAO_PIN, PULSOROTACAO_CH, -45.0, +45.0, 0.0};
  Servo garra{GARRA_PIN, GARRA_CH, 0.0, +30.0, 0.0};

  Braco(void)
  {
    curRotacao = 0.0;
    curOmbro = 70.0;
    curCotovelo = -70.0;
    curPulsoFlexao = -70.0;
    curPulsoRotacao = 0.0;
    curGarra = 0.0;
  }

  void init(void);
  void update(void);

  /*
  void setRotacao(float newRotacao, bool doUpdate = false);
  void setOmbro(float newOmbro, bool doUpdate = false);
  void setCotovelo(float newCotovelo, bool doUpdate = false);
  void setPulsoFlexao(float newPulsoFlexao, bool doUpdate = false);
  void setPulsoRotacao(float newPulsoRotacao, bool doUpdate = false);
  void setGarra(float newGarra, bool doUpdate = false);
  */

  void atuar(char comando, float argumento);
};

#endif
