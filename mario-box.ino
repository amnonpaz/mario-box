#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "sounds.h"

// false = microswitch on D2 (INPUT_PULLUP, play on release)
// true  = piezo knock sensor on D2 (INPUT + external 1M to GND, play on hit)
#define PIEZO_ENABLED true

// Pin 2 = PD2 = PCINT18 (port D pin change group)
const int TRIGGER_PIN = 2;

#if PIEZO_ENABLED
// Ignore further wakes for a bit after playback so speaker vibration
// doesn't re-trigger the piezo.
const unsigned long PIEZO_COOLDOWN_MS = 1500;
#endif

ISR(PCINT2_vect) {}

void goToSleep() {
  Serial.println("Sleeping");
  Serial.flush();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  PCICR |= (1 << PCIE2);
  PCMSK2 |= (1 << PCINT18);
  sleep_cpu();
  sleep_disable();
  PCICR &= ~(1 << PCIE2);
  Serial.println("Woke up");
}

void setup() {
  Serial.begin(9600);
#if PIEZO_ENABLED
  // Idle LOW via external ~1M bleed resistor to GND; no internal pull-up.
  pinMode(TRIGGER_PIN, INPUT);
#else
  pinMode(TRIGGER_PIN, INPUT_PULLUP);
#endif
  Serial.println("Setup complete");
}

void loop() {
  goToSleep();

#if PIEZO_ENABLED
  // Knock is a short pulse — treat wake itself as the trigger.
  Serial.println("Playing");
  sounds::g_marioSeq.play();
  Serial.println("Done playing");
  delay(PIEZO_COOLDOWN_MS);
#else
  delay(50);
  int pinState = digitalRead(TRIGGER_PIN);
  Serial.print("Pin state: ");
  Serial.println(pinState ? "HIGH" : "LOW");
  if (pinState == HIGH) {
    Serial.println("Playing");
    sounds::g_marioSeq.play();
    Serial.println("Done playing");
  }
#endif
}
