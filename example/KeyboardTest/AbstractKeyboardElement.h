/** keyboard element basis for all buttons ....
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef ABSTRACT_KEYBOARD_ELEMENT_H
#define ABSTRACT_KEYBOARD_ELEMENT_H
#include "Arduino.h"
#include "AbstractKeyboardElement.h"

class AbstractKeyboardElement {
protected:
  uint8_t _pin;
  void (*_callback)(int val);
public:
  AbstractKeyboardElement(uint8_t pin, void (*callback)(int val))
    : _pin(pin), _callback(callback) {}
  virtual void init() = 0;
  virtual void loop() = 0;

  uint8_t getPin() {
    return _pin;
  }
  void setPin(uint8_t pin) {
    this->_pin = pin;
  }
};


#endif // ABSTRACT_KEYBOARD_ELEMENT_H