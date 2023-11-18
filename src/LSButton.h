/** Simple pushbutton
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef LS_BUTTON_H
#define LS_BUTTON_H
#include "Arduino.h"
#include "Button.h"

class LSButton : public Button {



public:

  static const uint8_t SHORT = 0x01;
  static const uint8_t LONG = 0x11;

  LSButton(uint8_t pin, void (*callback)(AbstractKeyboardElement* element, int val))
    : Button(pin, callback) {}

  virtual void callCallback() {
    if (_callback != NULL) {
      _callback(this, _lastPress);
    }
  }

  virtual void loop() {

    readPin();

    // If the switch changed, due to noise or pressing:
    if (_reading != _lastValue) {
      // reset the debouncing timer
      _bounceTS = millis();
    }

    // value has stabilized
    if ((millis() - _bounceTS) > _bounceThreashold) {

      // if the button state has changed:
      if (_reading != _curValue) {
        _curValue = _reading;


        if (_curValue) {  // if state is high then start measure
          _pressTS = millis();
        } else {  // if state is low then check measurement
          if (millis() > _pressTS + _longPressTime) {
            _lastPress = LONG;
          } else {
            _lastPress = SHORT;
          }
          callCallback();
        }
      }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    _lastValue = _reading;
  }

  protected:

  uint8_t _lastPress;
  long _pressTS;
  long _longPressTime = 500;  // default is 3 seconds

};



#endif  // LS_BUTTON_H