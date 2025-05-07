#include <Arduino.h>
#include "servo.h"

#ifndef BRACO_H
#define BRACO_H

// Feedrate em graus por egundo
#define FEEDRATE 20.0
#define STEP_SIZE (FEEDRATE * 0.001 * UPDATE_STEP)

class Braco
{
  public:

  Servo rotacao{15, 0, -70.0, +70.0, 0.0};
  Servo ombro{2, 1, -30.0, +70.0, 10.0};
  Servo cotovelo{4, 2, -70.0, +70.0, -70.0};
  Servo pulsoFlexao{16, 3, -70.0, 30.0, -70.0};
  Servo pulsoRotacao{17, 4, -70.0, +70.0, 0.0};
  Servo garra{5, 5, -40.0, +40.0, 0.0};

  void init(void);
  void update(void);
  void estop(void);
  void atuar(char comando, float argumento);
};

#endif
