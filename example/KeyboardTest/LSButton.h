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

  uint8_t value = SHORT;
  bool _state = LOW;
  bool _lastState = LOW;
  long _bounceTS;
  long _bounceThreashold = 5;
  long _longPressTime = 500;  // default is 3 seconds
  long _pressTS;

public:

  static const uint8_t SHORT = 0x01;
  static const uint8_t LONG = 0x11;

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

    // value has stabilized
    if ((millis() - _bounceTS) > _bounceThreashold) {

      // if the button state has changed:
      if (reading == _state) {
        _state = !reading;


        if (_state) {  // if state is high then start measure
          _pressTS = millis();
        } else {  // if state is low then check measurement
          if (millis() > _pressTS + _longPressTime) {
            _callback(LONG);
          } else {
            _callback(SHORT);
          }
        }
      }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    _lastState = reading;
  }
};



#endif  // LS_BUTTON_H