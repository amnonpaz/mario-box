#include "sounds.h"
#include "PinState.h"

pins::State pin(2);

void setup() {
  pin.init();
}

void loop() {
  if (pin.isTriggeredHigh()) {
    sounds::g_marioSeq.play();
    delay(300);
  }
}