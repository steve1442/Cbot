#include "main.h"
void initializeIO() {}
void initialize() {
  lcdInit(uart1);
  LeftEnc = encoderInit(3, 4, false);
  RightEnc = encoderInit(2, 1, true);
  pinMode(1, OUTPUT);
  digitalWrite(1, LOW);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}
