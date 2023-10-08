/** keyboard element basis for all buttons, potis ....
*
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef ABSTRACT_KEYBOARD_ELEMENT_H
#define ABSTRACT_KEYBOARD_ELEMENT_H
#include "Arduino.h"
#include "AbstractKeyboardElement.h"

class AbstractKeyboardElement {

public:

  /** default constructor
  */
  AbstractKeyboardElement(uint8_t pin, void (*callback)(AbstractKeyboardElement* button, int val))
    : _pin(pin), _callback(callback) {}

  /** method should be called in setup funktion
  */
  virtual void init() = 0;

  /** method should be called in loop function
  */
  virtual void loop() = 0;

  /** get the pin to which the element is attached
  */
  uint8_t getPin() {
    return _pin;
  }

  /** set the pin to which this element is attached.
  * method calls init again
  */
  void setPin(uint8_t pin) {
    this->_pin = pin;
    init();
  }

  // get current value of the button
  int getCurrentValue() {
    return _curValue;
  }

  /** set the callback again, 
  * set to NULL if no callback is needed
  */
  void setCallback(void (*callback)(AbstractKeyboardElement* button, int val)) {
    this->_callback = callback;
  }

  /** is the button value inverted e.g. off instead of on 
  */
  bool isInvert() {
    return _invert;
  }

  /** set if the input for this element should be inverted 
  * e.g. for a button to deliver on when its off
  */
  void setInvert(bool val) {
    this->_invert = val;
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

protected:
  uint8_t _pin;
  int _curValue;
  int _lastValue;
  int _reading;
  long _bounceTS;
  long _bounceThreashold = 5;

  void (*_callback)(AbstractKeyboardElement* button, int val) = NULL;
  bool _invert = true;

  virtual void callCallback() {
    if (_callback != NULL) {
      _callback(this, _curValue);
    }
  }
  virtual void readPin() = 0;
};


#endif  // ABSTRACT_KEYBOARD_ELEMENT_H