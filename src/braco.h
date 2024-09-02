#include <Arduino.h>
#include "servo.h"

#define ROTACAO_PIN 2
#define ROTACAO_CH 0
#define OMBRO_PIN 3
#define OMBRO_CH 1
#define COTOVELO_PIN 4
#define COTOVELO_CH 2
#define PULSOFLEXAO_PIN 5
#define PULSOFLEXAO_CH 3
#define PULSOROTACAO_PIN 6
#define PULSOROTACAO_CH 4
#define GARRA_PIN 7
#define GARRA_CH 5

class Braco
{
  float curRotacao;
  float curExtensao;
  float curPulsoFlexao;
  float curPulsoRotacao;
  float curGarra;

  Servo rotacao{ROTACAO_CH, ROTACAO_PIN};
  Servo ombro{OMBRO_CH, OMBRO_PIN};
  Servo cotovelo{COTOVELO_CH, COTOVELO_PIN};
  Servo pulsoFlexao{PULSOFLEXAO_CH, PULSOFLEXAO_PIN};
  Servo pulsoRotacao{PULSOROTACAO_CH, PULSOROTACAO_PIN};
  Servo garra{GARRA_CH, GARRA_PIN};

  public:

  Braco(void)
  {
    curRotacao = 0.0;
    curExtensao = 0.0;
    curPulsoFlexao = 0.0;
    curPulsoRotacao = 0.0;
    curGarra = 0.0;
  }

  void init(void);
  void update(void);

  void setRotacao(float newRotacao);
  void setExtensao(float newExtensao);
  void setPulsoFlexao(float newPulsoFlexao);
  void setPulsoRotacao(float newPulsoRotacao);
  void setGarra(float newGarra);
};
