
/** Simple pushbutton
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef BUTTON_H
#define BUTTON_H
#include "Arduino.h"
#include "AbstractKeyboardElement.h"

#ifdef ESP32
	#include "esp32-hal-gpio.h"
#endif


class Button : public AbstractKeyboardElement {



public:
  Button(uint8_t pin, void (*callback)(AbstractKeyboardElement* element, int val)= NULL, uint8_t pinMode = INPUT_PULLUP )
    : AbstractKeyboardElement(pin, callback), _pinMode(pinMode) {}

  virtual void init() {
    pinMode(_pin, _pinMode);
    _invert = (_pinMode == INPUT_PULLUP);
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

    if ((millis() - _bounceTS) > _bounceThreashold || !_debounce) {

      // if the button state has changed:
      if (_reading != _curValue) {
        _curValue = _reading;
        callCallback();
      }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    _lastValue = _reading;
  }

  /** get the current bounce threshold
  */
  int getBounceThreshold() {
    return _bounceThreashold;
  }


/** set the threshold of the dbouncing, 
  * time until a state change is valid
  * @value threshold time in ms
  */
  void setBounceThreshold(int threshold) {
    this->_bounceThreashold = threshold;
  }

  void setDebounce (bool state){
    this->_debounce = state;
  }

  bool isDebounce (){
    return _debounce;
  }

protected:

  long _bounceTS;
  long _bounceThreashold = 5;
  uint8_t _pinMode;

  bool _debounce = true;

  virtual void readPin() {
    _reading = digitalRead(_pin);
   if (_invert) {
      _reading = !_reading;
   }
  }

};



#endif  // BUTTON_H