#include "main.h"
void initializeIO() {}
void initialize() {
  lcdInit(uart1);
  LeftEnc = encoderInit(3, 4, false);
  RightEnc = encoderInit(2, 1, true);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
}
