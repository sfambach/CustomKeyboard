/******************************************************************************
# Test a light button button
A light button has a switch and a light
The light can be permanent ON/OFF or dependant on the button state ON/OFF
The example shows 3 buttons where the light is differently configured.
The first two button are calling the same callback function and the third
Button is calling a different callback version. This should show how to handle
the callback function.

##Settings
Button Input
Button Output for Light ON/OFF
Light Mode
Callback method 

## Credits 
* Licence: AGPL3
* Author:  S. Fambach
Visit http://www.fambach.net if you want
******************************************************************************/

/*****************************************************************************/
// Debuging

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINT(x) Serial.print(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#endif


/*****************************************************************************/
// Button Setup
#define BUTTON1_SW_PIN 19
#define BUTTON1_LIGHT_PIN 18 

#define BUTTON2_SW_PIN 17
#define BUTTON2_LIGHT_PIN 16 

#define BUTTON3_SW_PIN 22
#define BUTTON3_LIGHT_PIN 21 


/*****************************************************************************/
// Create a one button keyboard ;) 
#include"CustomKeyboard.h"
#include"LightButton.h"

// create a keyboard with one element
CustomKeyboard keyBoard(3);

// create a variable for the game button
LightButton* gb1;
LightButton* gb2;
LightButton* gb3;


// declare the callback for the button
void initKeyboard(){

  // create a game button
  gb1 = new LightButton(BUTTON1_SW_PIN, BUTTON1_LIGHT_PIN, LightMode::ALLWAYS_ON, &buttonCallback, INPUT_PULLDOWN);
  gb2 = new LightButton(BUTTON2_SW_PIN, BUTTON2_LIGHT_PIN, LightMode::ALLWAYS_RELEASED_ON, &buttonCallback, INPUT_PULLDOWN);
  gb3 = new LightButton(BUTTON3_SW_PIN, BUTTON3_LIGHT_PIN, LightMode::ALLWAYS_PRESSED_ON, &button3Callback, INPUT_PULLDOWN);

  // add the button to the keyboard
  keyBoard.addElement(gb1);
  keyBoard.addElement(gb2);
  keyBoard.addElement(gb3);

  keyBoard.setup();
}

/*****************************************************************************/
// Call back action 
void buttonCallback(AbstractKeyboardElement* element, int val){
  if(element == gb1){
    DEBUG_PRINT("Button 1 = ");
    DEBUG_PRINTLN( (val?"ON":"OFF"));
  } else if(element == gb2){
    DEBUG_PRINT("Button 2 =");
    DEBUG_PRINTLN( (val?"ON":"OFF"));
  }else {
    DEBUG_PRINT("undefined Button");
  }

}

void button3Callback(AbstractKeyboardElement* element, int val){
    DEBUG_PRINT("Button 3 = ");
    DEBUG_PRINTLN( (val?"ON":"OFF"));
}

/*****************************************************************************/
// Main Programm 

void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  // init the keyboard and its buttons
  initKeyboard();
}


void loop() {
  // check the buttons for changes
  keyBoard.loop();
}
