#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "sounds.h"

// Pin 2 = PD2 = PCINT18 (port D pin change group)
const int SWITCH_PIN = 2;

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
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  Serial.println("Setup complete");
}

void loop() {
  goToSleep();
  delay(50);
  int pinState = digitalRead(SWITCH_PIN);
  Serial.print("Pin state: ");
  Serial.println(pinState ? "HIGH" : "LOW");
  if (pinState == HIGH) {
    Serial.println("Playing");
    sounds::g_marioSeq.play();
    Serial.println("Done playing");
  }
}
