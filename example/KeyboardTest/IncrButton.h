/** Increasing button, the longer you press the higher the value 
* Values between 0 and 100%
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef INCR_BUTTON_H
#define INCR_BUTTON_H
#include "Arduino.h"
#include "AbstractKeyboardElement.h"
enum CountMode {
  OVERFLOW = 1,
  REVERSE = 2,
  STOP = 3
};


class IncrButton : public AbstractKeyboardElement {

protected:
  int _value;
  bool _state = LOW;
  bool _lastState = LOW;
  long _bounceTS;
  long _bounceThreashold = 5;


  long _stepTime = 200;
  long _stepTS;

  int _minValue = 0;
  int _maxValue = 100;
  int _curValue = 0;
  int _step = 5;

  CountMode _countMode = REVERSE;

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
      _curValue += _step;

      if (_curValue > _maxValue) {

        switch (_countMode) {
          case OVERFLOW: _curValue = _minValue; break;
          case REVERSE:
            _step = -_step;
            _curValue = _maxValue + _step;
            break;
          case STOP:  // do nothing ;
            _curValue = _maxValue;
            break;
        }
      } else if (_curValue < _minValue) {

        switch (_countMode) {
          case OVERFLOW:  // nothing to do
            break;
          case REVERSE:
            _step = -_step;
            _curValue = _minValue + _step;
            break;
          case STOP:  // do nothing ;
            break;
        }
      }
      _stepTS = millis();
      _callback(_curValue);
    }


    if ((millis() - _bounceTS) > _bounceThreashold) {

      // if the button state has changed:
      if (reading == _state) {
        _state = !reading;

        if (_state) {
          _curValue = _step;
          _stepTS = millis();
        } else {
          _curValue = 0;
        }
        _callback(_curValue);
      }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    _lastState = reading;
  }
};

#endif  // INCR_BUTTON_H