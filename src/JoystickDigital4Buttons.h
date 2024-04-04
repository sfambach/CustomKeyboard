#ifndef JOYSTICK_DIGITAL_4_BUTTONS_H
#define JOYSTICK_DIGITAL_4_BUTTONS_H

#include "AbstractKeyboardElement.h"
#include "Button.h"

class JoystickDigital4Buttons: public AbstractKeyboardElement {

public:

	static const int UP = 1;
	static const int DOWN = 2;
	static const int LEFT = 4;
	static const int RIGHT = 8;
	
	JoystickDigital4Buttons(uint8_t pinUp, uint8_t pinDown, uint8_t pinLeft, uint8_t pinRight, void (*callback)(AbstractKeyboardElement* element, int val)= NULL, uint8_t pinMode = INPUT_PULLUP)
	: AbstractKeyboardElement(0, callback), _pinMode(pinMode) {
	  _up = new Button(pinUp,NULL, _pinMode);
	  _down = new Button(pinDown,NULL, _pinMode);
	  _left = new Button(pinLeft,NULL, _pinMode);
	  _right = new Button(pinRight,NULL, _pinMode);
	  
	  _curValue = _lastValue = 0;
	  readPin();
	}


		
	 /** method should be called in setup funktion
	*/
	virtual void init(){
		_up->init();
		_down->init();
		_left->init();
		_right->init();
	}

	/** method should be called in loop function
	*/
	virtual void loop(){
		_up->loop();
		_down->loop();
		_left->loop();
		_right->loop();
		readPin();
		if(_curValue != _lastValue){
			callCallback();
		}
	  
	}
	
	protected:
	
	uint8_t _pinMode;
	bool _debounce = true;
	
	Button* _up;
	Button* _down;
	Button* _left;
	Button* _right;
	
	virtual void readPin() {
		_lastValue = _curValue;
		_curValue = 0;
		if(_up->getCurrentValue() > 0){
			//Log.traceln("Up Pressed");
			_curValue |= UP;
		}else if(_down->getCurrentValue() > 0){
			//Log.traceln("Down Pressed");
			_curValue |= DOWN;
		}
		
		if(_left->getCurrentValue() > 0){
			//Log.traceln("Left Pressed");
			_curValue |= LEFT;
		}else if(_right->getCurrentValue() > 0){
			//Log.traceln("Right Pressed");
			_curValue |= RIGHT;
		}		
	}
};


#endif // JOYSTICK_DIGITAL_4_BUTTONS_H