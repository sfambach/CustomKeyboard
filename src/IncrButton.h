/** Increasing button, the longer you press the higher the value 
* Values between 0 and 100%
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef INCR_BUTTON_H
#define INCR_BUTTON_H
#include "Arduino.h"
#include "Button.h"
enum CountMode {
  RESET = 1,  // Start again with _minValue
  REVERSE = 2,   // after reaching the _maxValue start to count down until the _minValue is reached
  STOP = 3       // stop at _maxValue
};


class IncrButton : public Button {

protected:
  bool _curState = false;
  bool _lastState;
  bool _saveState = true;

  long _stepTime = 200;
  long _stepTS;

  int _minValue = 0;
  int _maxValue = 100;
  int _step = 5;

  CountMode _countMode = REVERSE;

public:


  IncrButton(uint8_t pin, void (*callback)(AbstractKeyboardElement* element, int val) = NULL, CountMode mode = CountMode::RESET, int minValue = 0, int maxValue = 100, int step = 5)
    : Button(pin, callback), _countMode(mode), _minValue(minValue), _maxValue(maxValue),  _step(step) {}


  virtual void init() override {
    pinMode(_pin, INPUT_PULLUP);
    _curValue = _lastValue = _minValue;
    _curState = false;
  }

  /** increase the value by step 
  * check the upper and lower overflow
  */
  void  increaseValueByStep(){
      _curValue += _step;
      
      if(_curValue > _maxValue){ // if upper overflow 
        switch (_countMode) {
          case RESET: _curValue = _minValue; break;
          case REVERSE:
            _step = -_step;
            _curValue = _maxValue + _step;
            break;
          case STOP:  // do nothing ;
            _curValue = _maxValue;
            break;
        }
      } else if(_curValue < _minValue){  // if lower overflow
         switch (_countMode) {
          case RESET:  // nothing to do
            break;
          case REVERSE:
            _step = -_step;
            _curValue = _minValue + _step;
            break;
          case STOP:  // do nothing ;
            break;
        }
      }

       
      _stepTS = millis();
      callCallback();
  }
  virtual void loop() {

    readPin();
    //_state = _reading;

    // If the switch changed, due to noise or pressing:
    if (_reading != _lastState) {
      // reset the debouncing timer
      _bounceTS = millis();
      _stepTS = millis();
    } else if (_reading && millis() > (_stepTS +_stepTime) ) {
      increaseValueByStep();
    }

    if ((millis() - _bounceTS) > _bounceThreashold) {

      // if the button state has changed:
      if (_reading != _curState) {
        _curState = _reading;

        if (_curState) { // if button is pressed
          if (!_saveState) { // save the state or reset after loosing
            _curValue = _step;
          } else {
            increaseValueByStep();
          }
        
        } else {
          if (!_saveState) {
            _curValue = 0;
            callCallback();
          }
        }
      }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    _lastState = _reading;
  }


  CountMode getCountMode() {
    return _countMode;
  }

  /** set the count modus 
  * RESET => Start again with _minValue
  * REVERSE => aftger reaching the _maxValue start to count down until the _Value is reached
  * STOP => stop at _maxValue
  */
  void setCountMode(CountMode mode) {
    this->_countMode = mode;
    init();
  }


  void setStepTime(long ms){
    _stepTime = ms;
  }
};

#endif  // INCR_BUTTON_H