/** Increasing button, the longer you press the higher the value 
* Values between 0 and 100%
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef INCR_BUTTON_H
#define INCR_BUTTON_H
#include "Arduino.h"
#include "AbstractKeyboardElement.h"

class IncrButton : public AbstractKeyboardElement {

protected:
  uint8_t _value;
  bool _state = LOW;
  bool _lastState = LOW;
  long _bounceTS;
  long _bounceThreashold = 5;
  bool _startOver = true;
  uint8_t _step = 5;
  long _stepTime = 500;
  long _stepTS;
  uint8_t _valueMax = 100;

public:
  IncrButton(uint8_t pin, void (*callback)(int val))
    : AbstractKeyboardElement(pin, callback) {}
  virtual void init() {
    pinMode(_pin, INPUT_PULLUP);
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

#endif  // INCR_BUTTON_H