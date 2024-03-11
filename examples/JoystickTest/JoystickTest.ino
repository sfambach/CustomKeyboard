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
// Create a keyboard 
#include "joystick_settings.h"
#include"CustomKeyboard.h"
#include"LightButton.h"
#include"Button.h"


CustomKeyboard keyBoard(10);

// create a variable for the game button
LightButton* player;
LightButton* gb1;
LightButton* coin;
LightButton* button1;
LightButton* button2;
LightButton* button3;
LightButton* button4;

Button* joyUp;
Button* joyDown;
Button* joyLeft;
Button* joyRight;


// declare the callback for the button
void initKeyboard(){


  // create a game button
  //gb0 = new LSButton(15, 2000, &button0Callback, INPUT_PULLDOWN);

  coin = new LightButton(COIN_SW, COIN_LIGHT, LightMode::ALLWAYS_ON, &coinCallback, INPUT_PULLDOWN);
  player = new LightButton(PLAYER_SW, PLAYER_LIGHT, LightMode::ALLWAYS_ON, &playerCallback, INPUT_PULLDOWN);
  
  button1 = new LightButton(BUTTON1_SW, BUTTON1_LIGHT, LightMode::ALLWAYS_RELEASED_ON, &button1Callback, INPUT_PULLDOWN);
  button2 = new LightButton(BUTTON2_SW, BUTTON2_LIGHT, LightMode::ALLWAYS_RELEASED_ON, &button2Callback, INPUT_PULLDOWN);
  button3 = new LightButton(BUTTON3_SW, BUTTON3_LIGHT, LightMode::ALLWAYS_RELEASED_ON, &button3Callback, INPUT);
  button4 = new LightButton(BUTTON4_SW, BUTTON4_LIGHT, LightMode::ALLWAYS_RELEASED_ON, &button4Callback, INPUT_PULLDOWN);
 // gb6 = new LightButton(33, 25, LightMode::ALLWAYS_RELEASED_ON, &button6Callback, INPUT_PULLDOWN);

  joyUp = new Button(UP_SW,  &joyCallback, INPUT_PULLUP);
  joyDown = new Button(DOWN_SW,  &joyCallback, INPUT_PULLUP);
  joyLeft = new Button(LEFT_SW,  &joyCallback, INPUT_PULLUP);
  joyRight = new Button(RIGHT_SW,  &joyCallback, INPUT_PULLUP);


  // add the button to the keyboard
  
  keyBoard.addElement(button1);
  keyBoard.addElement(button2);
  keyBoard.addElement(button3);
  keyBoard.addElement(button4);
  //keyBoard.addElement(gb6);

  keyBoard.addElement(player);
  keyBoard.addElement(coin);


  keyBoard.addElement(joyUp);
  keyBoard.addElement(joyDown);
  keyBoard.addElement(joyLeft);
  keyBoard.addElement(joyRight);

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
void coinCallback(AbstractKeyboardElement* element, int val){
    log_v("Coin Button = %s", (val?"ON":"OFF"));
    
    /*DEBUG_PRINT("Button 0 = ");
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
        }
    } else {
        DEBUG_PRINT( "off");
    }
    DEBUG_PRINTLN("");*/
}

void playerCallback(AbstractKeyboardElement* element, int val){
  log_v("Player Button = %s", (val?"ON":"OFF"));
}

void button1Callback(AbstractKeyboardElement* element, int val){
  log_v("Button 1= %s", (val?"ON":"OFF")); 
}

void button2Callback(AbstractKeyboardElement* element, int val){
  log_v("Button 2 = %s", (val?"ON":"OFF"));
}
void button3Callback(AbstractKeyboardElement* element, int val){
  log_v("Button 3 = %s", (val?"ON":"OFF"));
}
void button4Callback(AbstractKeyboardElement* element, int val){
  log_v("Button 4 Button = %s", (val?"ON":"OFF"));
}


void joyCallback(AbstractKeyboardElement* element, int val){
  if(val){
    log_v("Center");
    return;
  }
    if(element == joyUp){
      log_v("UP");
    } else if(element == joyDown){
      log_v("DOWN");
    } else if(element == joyLeft){
      log_v("LEFT");
    } else if(element == joyRight){
      log_v("RIGHT");
    }
}



/*****************************************************************************/
// Main Programm 

void setup() {
  Serial.begin(115200);
  log_v("Setup");

  // init the keyboard and its buttons
  initKeyboard();
}


void loop() {
  // check the buttons for changes
  keyBoard.loop();
}
