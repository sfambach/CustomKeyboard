/** Simple pushbutton
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef BUTTON_H
#define BUTTON_H
#include "Arduino.h"
#include "AbstractKeyboardElement.h"

class Button : public AbstractKeyboardElement {

protected:

  virtual void readPin() {
    _reading = digitalRead(_pin);
    if (_invert) {
      _reading = !_reading;
    }
  }

public:
  Button(uint8_t pin, void (*callback)(int val))
    : AbstractKeyboardElement(pin, callback) {}

  virtual void init() {
    pinMode(_pin, INPUT_PULLUP);
    readPin();
    _curValue = _lastValue = _reading;
  }

  virtual void loop() {

    readPin();

    // If the switch changed, due to noise or pressing:
    if (_reading != _lastValue) {
      // reset the debouncing timer
      _bounceTS = millis();
    }

    if ((millis() - _bounceTS) > _bounceThreashold) {

      // if the button state has changed:
      if (_reading != _curValue) {
        _curValue = _reading;
        callCallback();
      }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    _lastValue = _reading;
  }
};



#endif  // BUTTON_H