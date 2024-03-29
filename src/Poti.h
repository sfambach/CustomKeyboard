/** Simple pushbutton
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef POTI_H
#define POTI_H
#include "Arduino.h"
#include "AbstractKeyboardElement.h"

class Poti : public AbstractKeyboardElement {

protected:
  
  int _threshold = 1;

  

  
public:
  Poti(uint8_t pin, void (*callback)(AbstractKeyboardElement* element, int val))
    : AbstractKeyboardElement(pin, callback) {}
 
  virtual void init() {
    pinMode(_pin, INPUT);
    _curValue = _lastValue = _reading;
    callCallback();
  };

  virtual void loop() {
    
   analogReadPin();

    // If the switch changed, due to noise or pressing:
    if (_reading > (_curValue + _threshold) || _reading < (_curValue- _threshold)) {
      _lastValue = _curValue;
      _curValue = _reading;
      callCallback();
    }

  }
  
  void setThreshold(int threshold ){
	  this->_threshold = threshold;
  }
  
    
  int getThreshold(){
	  return this->_threshold;
  }
  
};


#endif // POTI_H