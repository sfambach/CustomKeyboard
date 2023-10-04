/** Simple pushbutton
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef LS_BUTTON_H
#define LS_BUTTON_H
#include "Arduino.h"
#include "AbstractKeyboardElement.h"

class LSButton : public AbstractKeyboardElement {

private:

  bool _state = LOW;
  bool _lastState = LOW;
  long _bounceTS;
  long _bounceThreashold = 5;

public:
  LSButton(uint8_t pin, void (*callback)(int val))
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
    }

    if ((millis() - _bounceTS) > _bounceThreashold) {

      // if the button state has changed:
      if (reading == _state) {
        _state = !reading;
        _callback(_state);
      }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    _lastState = reading;
  }
};



#endif // LS_BUTTON_H