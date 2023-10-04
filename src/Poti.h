/** Simple pushbutton
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef POTI_H
#define POTI_H
#include "Arduino.h"
#include "AbstractKeyboardElement.h"

class Poti : public AbstractKeyboardElement {

private:

  int _value;
  int _threshold = 1;

public:
  Poti(uint8_t pin, void (*callback)(int val))
    : AbstractKeyboardElement(pin, callback) {}
 
  virtual void init() {
    pinMode(_pin, INPUT);
  };

  virtual void loop() {
    int reading = map(analogRead(_pin), 0,1024,0,100);

    // If the switch changed, due to noise or pressing:
    if (reading > (_value + _threshold) || reading < (_value- _threshold)) {
   
      _value = reading;
      //_callback(map (_value, 0 , 255, 0, 100));
      _callback(_value);
      
    }

  }
};


#endif // POTI_H