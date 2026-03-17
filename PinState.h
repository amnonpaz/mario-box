#ifndef PIN_STATE_H_
#define PIN_STATE_H_

namespace pins {

class State {
  public:
    State(int pin) :
      _pin(pin),
      _state(LOW) {}

    void init() {
      pinMode(_pin, INPUT_PULLUP);
    }

    bool isTriggeredHigh() {
      bool res = false;

      int newState = digitalRead(_pin);

      if (_state == LOW && newState == HIGH) {
        res = true;
      }

      _state = newState;

      delay(10); // debouncing

      return res;
    }

  public:
    const int _pin;
    int _state;

};

}

#endif