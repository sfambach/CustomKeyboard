/** Simple pushbutton
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef BUTTON_H
#define BUTTON_H
#include "Arduino.h"
#include "AbstractKeyboardElement.h"

class ModeButton : public IncrButton {

private:


public:
  ModeButton(uint8_t pin, void (*callback)(int val))
    : AbstractKeyboardElement(pin, callback) {}
  virtual void init() {
    pinMode(_pin, INPUT_PULLUP);
    _step = 1;
    _valueMax = 5;
  }
  virtual void loop() {

    bool reading = digitalRead(_pin);

    // If the switch changed, due to noise or pressing:
    if (reading != _lastState) {
      // reset the debouncing timer
      _bounceTS = millis();
    } else if (_state && millis() - _stepTime > _stepTS) {
      _value += _step;

      if (_value > _valueMax) {
        if (_startOver) {
          _value = _step;
        } else {
          _value = _valueMax;
        }
      }
      _stepTS = millis();
      _callback(_value);
    }


    if ((millis() - _bounceTS) > _bounceThreashold) {

      // if the button state has changed:
      if (reading == _state) {
        _state = !reading;

        if (_state) {
          _value = _step;
          _stepTS = millis();
        } else {
          _value = 0;
        }
        _callback(_value);
      }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    _lastState = reading;
  }

};



#endif // BUTTON_H