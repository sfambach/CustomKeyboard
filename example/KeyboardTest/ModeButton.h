/** Simple pushbutton
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef MODE_BUTTON_H
#define MODE_BUTTON_H
#include "Arduino.h"
#include "IncrButton.h"

class ModeButton : public IncrButton {

protected:


  

public:
 

  ModeButton(uint8_t pin, void (*callback)(int val))
    : IncrButton(pin, callback) {}


  virtual void init() {
    pinMode(_pin, INPUT_PULLUP);
    _step = 1;
    _maxValue = 5;
  }
  virtual void loop() {

   /* bool reading = digitalRead(_pin);

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

      _curMode += _step;
      if(_curMode > _maxMode){

      } else if (_curMode < _minMode){
        
      }

      _callback(_curMode);
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
    _lastState = reading;*/
  }

};



#endif // MODE_BUTTON_H