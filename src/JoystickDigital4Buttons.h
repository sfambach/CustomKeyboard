#ifndef JOYSTICK_DIGITAL_4_BUTTONS_H
#define JOYSTICK_DIGITAL_4_BUTTONS_H

#include "AbstractKeyboardElement.h"
#include "Button.h"

class JoystickDigital4Buttons:AbstractKeyboardElement {

	const uint8_t UP = 1;
	const uint8_t DOWN = 2;
	const uint8_t LEFT = 4;
	const uint8_t RIGHT = 8;
	
	Button* _up;
	Button* _down;
	Button* _left;
	Button* _right;
	
	void buttonCallback(AbstractKeyboardElement element){
		uint8_t = 0;
		if(_up->getCurrentValue() > 0){
			uint8_t |= UP;
		}else if(_down->getCurrentValue() > 0){
			uint8_t |= DOWN;
		}
		
		if(_left->getCurrentValue() > 0){
			uint8_t |= LEFT;
		}else if(_right->getCurrentValue() > 0){
			uint8_t |= RIGHT;
		}
				
				
	}
	
	JoystickDigital4Buttons (uint8_t pinUp, uint8_t pinDown, uint8_t pinLeft, uint8_t pinRight){
	  _up = new Button();
	}


		
	 /** method should be called in setup funktion
	*/
	virtual void init(){
	  
	}

	/** method should be called in loop function
	*/
	virtual void loop(){
	  
	  
	  
	}
	
	
};


#endif // JOYSTICK_DIGITAL_4_BUTTONS_H