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

// Feedrate em graus por egundo
#define FEEDRATE 20.0
#define STEP_SIZE (FEEDRATE * 0.001 * UPDATE_STEP)

class Braco
{
  public:

  Servo rotacao{ROTACAO_PIN, ROTACAO_CH, -70.0, +70.0, 0.0};
  Servo ombro{OMBRO_PIN, OMBRO_CH, -30.0, +70.0, 10.0};
  Servo cotovelo{COTOVELO_PIN, COTOVELO_CH, -70.0, +70.0, -70.0};
  Servo pulsoFlexao{PULSOFLEXAO_PIN, PULSOFLEXAO_CH, -70.0, 30.0, -70.0};
  Servo pulsoRotacao{PULSOROTACAO_PIN, PULSOROTACAO_CH, -70.0, +70.0, 0.0};
  Servo garra{GARRA_PIN, GARRA_CH, 0.0, +60.0, 0.0};

  void init(void);
  void update(void);
  void estop(void);
  void atuar(char comando, float argumento);
};

#endif
