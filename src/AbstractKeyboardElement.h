/** keyboard element basis for all buttons, potis ....
*
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef ABSTRACT_KEYBOARD_ELEMENT_H
#define ABSTRACT_KEYBOARD_ELEMENT_H
#include "Arduino.h"

#ifdef ESP8266	
  // nothing special now
#elif defined ESP32
  // setting PWM properties
  const int freq = 5000;
  const int ledChannel = 0;
  const int resolution = 8;
#else 
  // nothing special now
#endif

class AbstractKeyboardElement {

public:

  /** default constructor
  */
  AbstractKeyboardElement(uint8_t pin, void (*callback)(AbstractKeyboardElement* button, int val)= NULL)
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
    _invert = val;
  }

  void analogReadPin(){  
    #ifdef ESP8266	
	_reading = map(analogRead(_pin), 0,1024,0,101);
    #elif defined ESP32
	_reading = map(analogRead(_pin), 0,4096,0,101);
    #else 
	_reading = map(analogRead(_pin), 0,1024,0,101);
    #endif
  }

  /*void analogWritePin(){  
    #ifdef ESP8266	
      analogWrite(_pin, _curValue);
    #elif defined ESP32
	  analogWrite(_curValue);
	  //_reading = map(analogRead(_pin), 0,4096,0,101);
    #else 
		analogWrite(_pin, _curValue);
	
    #endif
  }*/

  void digitalReadPin() {  
   _reading = digitalRead(_pin);
  }

  void digitalWritePin(){
    digitalWrite(_pin, _curValue);
  }

  void analogWritePin(){
	analogWrite(_pin, _curValue);
  }

protected:
  uint8_t _pin;
  int _curValue;
  int _lastValue;
  int _reading;
  bool _invert = false;

  void (*_callback)(AbstractKeyboardElement* button, int val)= NULL;

  virtual void callCallback() {
    if (_callback != NULL) {
      _callback(this, _curValue);
    }
  }

  
};


#endif  // ABSTRACT_KEYBOARD_ELEMENT_H