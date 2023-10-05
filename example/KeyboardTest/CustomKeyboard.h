#include "Arduino.h"
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Arduino.h"
#include "AbstractKeyboardElement.h"
#include "IncrButton.h"
#include "LSButton.h"
#include "Poti.h"
#include "Button.h"
#include "ModeButton.h"


class CustomKeyboard {

private:
  AbstractKeyboardElement** _elements;
  uint8_t _maxElementCount;
  uint8_t _curElementCount = 0;

public:

  CustomKeyboard(uint8_t maxElementCount)
    : _maxElementCount(maxElementCount) {
    _elements = new AbstractKeyboardElement*[maxElementCount];
  }

  void addElement(AbstractKeyboardElement* element) {
    _elements[_curElementCount] = element;
    _curElementCount++;
  }

  void setup() {
    for (int i = 0; i < _curElementCount; i++) {
      _elements[i]->init();
    }
  }

  void loop() {
    for (int i = 0; i < _curElementCount; i++) {
      _elements[i]->loop();
    }
  }
};



#endif  // KEYBOARD_H
