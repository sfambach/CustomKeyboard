/******************************************************************************
# Test a Joystick with 6 Buttons and one stick
This example is using different buttons and a joystick.


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
#define BUTTON1_SW_PIN 15
#define BUTTON1_LIGHT_PIN 2 

#define BUTTON2_SW_PIN 17
#define BUTTON2_LIGHT_PIN 16 

#define BUTTON3_SW_PIN 22
#define BUTTON3_LIGHT_PIN 21 


/*****************************************************************************/
// Create a one button keyboard ;) 
#include"CustomKeyboard.h"
#include"LightButton.h"
#include"Button.h"

// create a keyboard with one element

const uint8_t LIGHT_LS_BUTTON = 16;


CustomKeyboard keyBoard(11);

// create a variable for the game button
Button* gb0;
LightButton* gb1;
LightButton* gb2;
LightButton* gb3;
LightButton* gb4;
LightButton* gb5;
LightButton* gb6;

Button* joy1;
Button* joy2;
Button* joy3;
Button* joy4;


// declare the callback for the button
void initKeyboard(){

  // create a game button
  gb0 = new LSButton(15, 2000, &button0Callback, INPUT_PULLDOWN);
  
  gb1 = new LightButton(18, 19, LightMode::ALLWAYS_RELEASED_ON, &button1Callback, INPUT_PULLDOWN);
  gb2 = new LightButton(16, 17, LightMode::ALLWAYS_RELEASED_ON, &button2Callback, INPUT_PULLDOWN);
  gb3 = new LightButton(21, 22, LightMode::ALLWAYS_RELEASED_ON, &button3Callback, INPUT_PULLDOWN);
  gb4 = new LightButton(13, 12, LightMode::ALLWAYS_RELEASED_ON, &button4Callback, INPUT_PULLDOWN);
  gb5 = new LightButton(27, 26, LightMode::ALLWAYS_RELEASED_ON, &button5Callback, INPUT_PULLDOWN);
  gb6 = new LightButton(33, 25, LightMode::ALLWAYS_RELEASED_ON, &button6Callback, INPUT_PULLDOWN);

  joy1 = new Button(32,  &joyCallback, INPUT_PULLUP);
  joy2 = new Button(35,  &joyCallback, INPUT_PULLUP);
  joy3 = new Button(34,  &joyCallback, INPUT_PULLUP);
  joy4 = new Button(39,  &joyCallback, INPUT_PULLUP);


  // add the button to the keyboard
  keyBoard.addElement(gb0);
  keyBoard.addElement(gb1);
  keyBoard.addElement(gb2);
  keyBoard.addElement(gb3);
  keyBoard.addElement(gb4);
  keyBoard.addElement(gb5);
  keyBoard.addElement(gb6);

  keyBoard.addElement(joy1);
  keyBoard.addElement(joy2);
  keyBoard.addElement(joy3);
  keyBoard.addElement(joy4);

  keyBoard.setup();
}

/*****************************************************************************/
// Wifi setup
void setupWifi(){

}

void loopWifi(){
  
}

/*****************************************************************************/
// Call back action 
int counter = 0;
bool toggle = false;
void button0Callback(AbstractKeyboardElement* element, int val){

    DEBUG_PRINT("Button 0 = ");
    if(val == LSButton::SHORT){
        DEBUG_PRINT( "Short");
    } else if(val == LSButton::LONG){
        DEBUG_PRINT( "Long");
        toggle = !toggle;
        digitalWrite(LIGHT_LS_BUTTON, toggle);
        /* if(toggle){
          WiFi.disconnect(true);
          WiFi.mode(WIFI_OFF);
        } else {
          WiFi.mode(WIFI_MODE_STA);
          WiFi.disconnect(false);
        }*/
    } else {
        DEBUG_PRINT( "off");
    }
    DEBUG_PRINTLN("");
}

void button1Callback(AbstractKeyboardElement* element, int val){
    DEBUG_PRINT("Button 1 = ");
    DEBUG_PRINTLN( (val?"ON":"OFF"));
}
void button2Callback(AbstractKeyboardElement* element, int val){
    DEBUG_PRINT("Button 2 = ");
    DEBUG_PRINTLN( (val?"ON":"OFF"));
}
void button3Callback(AbstractKeyboardElement* element, int val){
    DEBUG_PRINT("Button 3 = ");
    DEBUG_PRINTLN( (val?"ON":"OFF"));
}
void button4Callback(AbstractKeyboardElement* element, int val){
    DEBUG_PRINT("Button 4 = ");
    DEBUG_PRINTLN( (val?"ON":"OFF"));
}
void button5Callback(AbstractKeyboardElement* element, int val){
    DEBUG_PRINT("Button 5 = ");
    DEBUG_PRINTLN( (val?"ON":"OFF"));
}
void button6Callback(AbstractKeyboardElement* element, int val){
    DEBUG_PRINT("Button 6 = ");
    DEBUG_PRINTLN( (val?"ON":"OFF"));
}


void joyCallback(AbstractKeyboardElement* element, int val){
  if(val){
    DEBUG_PRINTLN("Center");
    return;
  }
    if(element == joy1){
      DEBUG_PRINTLN("RIGHT");
    } else if(element == joy2){
      DEBUG_PRINTLN("UP");
    } else if(element == joy3){
      DEBUG_PRINTLN("DOWN");
    } else if(element == joy4){
      DEBUG_PRINTLN("LEFT");
    }
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
