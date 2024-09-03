#include <Arduino.h>
#include "servo.h"

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

class Braco
{
  float curRotacao;
  float curExtensao;
  float curPulsoFlexao;
  float curPulsoRotacao;
  float curGarra;

  Servo rotacao{ROTACAO_PIN, ROTACAO_CH};
  Servo ombro{OMBRO_PIN, OMBRO_CH};
  Servo cotovelo{COTOVELO_PIN, COTOVELO_CH};
  Servo pulsoFlexao{PULSOFLEXAO_PIN, PULSOFLEXAO_CH};
  Servo pulsoRotacao{PULSOROTACAO_PIN, PULSOROTACAO_CH};
  Servo garra{GARRA_PIN, GARRA_CH};

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
