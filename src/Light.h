/** Light 
* Can be pressed, can switch light, optional auto fire is available.
*
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef LIGHT_H
#define LIGHT_H
#include "Arduino.h"
#include "Button.h"


enum LightMode {
  PERMANENT, 
  FADE,
  BLINK, 
};

class Light : AbstractKeyboardElement {

protected:

  bool _lightState = false;
  LightMode _lightMode;
  long _blinkDelay = 1000;
  long _blinkTS = 0;

  static const FADE_MIN = 0;
  static const FADE_MAX = 254;
  bool fadeForward = true;

public:

  Light(uint8_t lightPin, LightMode lightMode) 
  : AbstractKeyboardElement(lightPin), _lightPin(lightPin), _lightMode(lightMode) {}

  virtual void init() {

    pinMode(_lightPin, OUTPUT);
    setLightMode(_lightMode);
  #ifdef ESP8266	
  	  
  #elif defined ESP32
      // configure LED PWM functionalitites
      ledcSetup(ledChannel, freq, resolution);
      
      // attach the channel to the GPIO to be controlled
      ledcAttachPin(ledPin, ledChannel);
  #else 
	  
  #endif
    
  }

  virtual void loop() {
    if (_lightMode == LightMode::PERMANENT) {
      setLight((bool)_curValue);
    } else if (_lightMode == LightMode::FADE) {
      analogWritePin();

      if( millis()- _blinkTS > _blinkDelay){
        setValue(get)
        _blinkTS = millis();
      } 

    } else if (_lightMode == LightMode::BLINK) {
      if( millis()- _blinkTS > _blinkDelay){
        setValue(get)
        _blinkTS = millis();
      } 
    }
  }
 
  void setLightMode(LightMode mode) {
    _lightMode = mode;

 /*   if (mode == LightMode::ALLWAYS_OFF) {
      setLight(true);

    } else if (mode == LightMode::ALLWAYS_ON) {
      setLight(false);
    } else if (mode == LightMode::PRESSED_ON) {
      if (_curValue) {
        setLight(true);
      } else {
        setLight(false);
      }
    } else if (mode == LightMode::RELEASED_ON) {
      if (!_curValue) {
        setLight(true);
      } else {
        setLight(false);
      }
    } else if (mode == LightMode::BLINK) {
      if (!_curValue) {
        setLight(true);
      } else {
        setLight(false);
      }
    }*/
  }
  void setLight(bool state) {
    _curValue = state;
    digitalWritePin();
  }

  LightMode getLightMode() {
    return _lightMode;
  }
};

#endif  // LIGHT_H