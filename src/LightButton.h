/** Light button,
* Can be pressed, can switch light,
*
* Author: Stefan Fambach
* Website: http://www.fambach.net
*/
#ifndef LIGHT_BUTTON_H
#define LIGHT_BUTTON_H
#include "Arduino.h"
#include "Button.h"

enum LightMode {
  ALLWAYS_ON,
  ALLWAYS_OFF,
  ALLWAYS_RELEASED_ON,
  ALLWAYS_PRESSED_ON
};

class LightButton : public Button {

protected:

  bool _lightState = false;
  uint8_t _lightPin;
  LightMode _lightMode;

public:

  LightButton(uint8_t pin, uint8_t lightPin, LightMode lightMode = ALLWAYS_PRESSED_ON, void (*callback)(AbstractKeyboardElement* element, int val) = NULL, uint8_t pinMode = INPUT_PULLUP)
    : Button(pin, callback, pinMode), _lightPin(lightPin), _lightMode(lightMode) {}

  virtual void init() {
    Button::init();
    pinMode(_lightPin, OUTPUT);
    setLightMode(_lightMode);
  }

  virtual void loop() {
    Button::loop();
    if (_lightMode == LightMode::ALLWAYS_PRESSED_ON) {
      setLight((bool)_curValue);
    } else if (_lightMode == LightMode::ALLWAYS_RELEASED_ON) {
      setLight(!(bool)_curValue);
    }
  }
 
  void setLightMode(LightMode mode) {
    _lightMode = mode;

    if (mode == LightMode::ALLWAYS_OFF) {
      setLight(true);

    } else if (mode == LightMode::ALLWAYS_ON) {
      setLight(false);
    } else if (mode == LightMode::ALLWAYS_PRESSED_ON) {
      if (_curValue) {
        setLight(true);
      } else {
        setLight(false);
      }
    } else if (mode == LightMode::ALLWAYS_RELEASED_ON) {
      if (!_curValue) {
        setLight(true);
      } else {
        setLight(false);
      }
    }
  }
  void setLight(bool state) {
    digitalWrite(_lightPin, state);
  }

  LightMode getLight() {
    return _lightMode;
  }
};

#endif  // LIGHT_BUTTON_H