/******************************************************************************
# Test for the digital 4 button joystick

##Settings
*	JOY_UP	GPIO Pin for up 
*	JOY_DOWN	GPIO Pin for down 
*	JOY_LEFT	GPIO Pin for left
*	JOY_RIGHT GPIO Pin for right
* SERIAL_SPEED Boud rate of serial port
* DEBUG_LEVEL Debug level for output
* MANUAL_TEST_BUTTONS test the switches in the joy independant

## Libs
https://github.com/thijse/Arduino-Log/
https://github.com/sfambach/CustomKeyboard

## Credits 
* Licence: AGPL3
* Author:  S. Fambach
* Website: http://www.fambach.net 
******************************************************************************/
#include <Arduino.h>
#include <ArduinoLog.h> // https://github.com/thijse/Arduino-Log/

/** setup serial speed */
#define SERIAL_SPEED 115200

/** set the debugging level */
#define DEBUG_LEVEL LOG_LEVEL_VERBOSE

/** activate this to test the switches in the 
* joy independant with singe button objects */
//#define MANUAL_TEST_BUTTONS 

/** set the pins for the joystick*/
#define JOY_UP		33
#define JOY_DOWN	32
#define JOY_LEFT	26
#define JOY_RIGHT 25


/*****************************************************************************/
// Keyboard setting
#include <CustomKeyboard.h> // https://github.com/sfambach/CustomKeyboard
#include <JoystickDigital4Buttons.h> // https://github.com/sfambach/CustomKeyboard

CustomKeyboard* kb;

#ifdef MANUAL_TEST_BUTTONS
  Button* upButton;
  Button* downButton;
  Button* leftButton;
  Button* rightButton;
#else
  JoystickDigital4Buttons* joy;
#endif 

void joystickCallback(AbstractKeyboardElement* element, int state){
#ifdef MANUAL_TEST_BUTTONS
  if(element == upButton && state > 0){
    Log.traceln("UP");
  }
  if(element == downButton && state > 0){
    Log.traceln("Down");
  }
  if(element == leftButton && state > 0){
    Log.traceln("Left");
  }
  if(element == rightButton && state > 0){
    Log.traceln("Right");
  }
#else


  bool up = state & JoystickDigital4Buttons::UP;
  bool down = state & JoystickDigital4Buttons::DOWN;
  bool left = state & JoystickDigital4Buttons::LEFT;
  bool right = state & JoystickDigital4Buttons::RIGHT;

  Log.traceln("UP=%s DONW=%s , LEFT=%s RIGHT=%s",
    (up?"ON ":"OFF"),
    (down?"ON ":"OFF"),
    (left?"ON ":"OFF"),
    (right?"ON ":"OFF"));
#endif
}

/*****************************************************************************/
// Main Programm 

void setup() {
  Serial.begin(SERIAL_SPEED);
  Log.begin(DEBUG_LEVEL, &Serial, false);
    
  Log.traceln("Init Joystick completed, setup keyboard");
 #ifdef MANUAL_TEST_BUTTONS

  kb = new CustomKeyboard(4);
  //kb->addElement(joy);
  upButton = new Button(JOY_UP,  &joystickCallback, INPUT_PULLUP);
  downButton = new Button(JOY_DOWN,  &joystickCallback, INPUT_PULLUP);
  leftButton = new Button(JOY_LEFT,  &joystickCallback, INPUT_PULLUP);
  rightButton = new Button(JOY_RIGHT,  &joystickCallback, INPUT_PULLUP);

  kb->addElement(upButton);
  kb->addElement(downButton);
  kb->addElement(leftButton);
  kb->addElement(rightButton);

#else 
  kb = new CustomKeyboard(1);
  joy = new JoystickDigital4Buttons(JOY_UP, JOY_DOWN,JOY_LEFT,JOY_RIGHT, &joystickCallback, INPUT);
  kb->addElement(joy);
  
#endif
  kb->setup();
  Log.traceln("keyboard setup finished");
}


void loop() {
  kb->loop();
}

/*****************************************************************************/
// end