/***********************************************
* Organ Test
* Licence: AGPL3
* Author: S. Fambach
* Website: http://Fambach.net
************************************************/
// allow debug output
#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINT(x) Serial.print(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#endif

/******************************************************************************************/
//Keyboard
#include "CustomKeyboard.h"

CustomKeyboard keyboard(6);

void initKeyboard(){
  //keyboard = new CustomKeyboard(6);
  keyboard.addElement(new Poti(A0, poti1Callback));
  keyboard.addElement(new Button(A1, button1Callback));
  keyboard.addElement(new LSButton(A2,lsCallback) );
  keyboard.addElement(new IncrButton(A3, incrCallback));


  IncrButton* mode =  new IncrButton(A4, modeCallback, RESET , 0, 6, 1);
  mode->setBounceThreshold(100);
  mode->setStepTime(2000);
  keyboard.addElement(mode);
  
  keyboard.setup();

}

/******************************************************************************************/
// callbacks
void button1Callback(AbstractKeyboardElement* button, int state) {
  DEBUG_PRINT("Button");
  DEBUG_PRINT(1);
  DEBUG_PRINT(" is ");
  if (state) {
    DEBUG_PRINTLN("ON");

  } else {
    DEBUG_PRINTLN("OFF");
  }
}

void poti1Callback(AbstractKeyboardElement* element,int state) {
  DEBUG_PRINT("Poti ");
  DEBUG_PRINT(1);
  DEBUG_PRINT(" has value ");
  DEBUG_PRINTLN(state);
}

void modeCallback(AbstractKeyboardElement* button, int mode) {

  switch(mode){
    case 0: DEBUG_PRINTLN("Fountain 1 started");break;
    case 1: DEBUG_PRINTLN("Fountain 2 started");break;
    case 2: DEBUG_PRINTLN("Fountain 3 started");break;
    case 3: DEBUG_PRINTLN("Fountain 4 started");break;
    case 4: DEBUG_PRINTLN("Fountain 5 started");break;
    case 5: DEBUG_PRINTLN("Fountain 6 started");break;
    case 6: DEBUG_PRINTLN("Manual Mode");break;

  }
}

void lsCallback(AbstractKeyboardElement* button, int state) {
  DEBUG_PRINT("LS ");
  DEBUG_PRINT(" has value ");
  DEBUG_PRINTLN(state == LSButton::LONG? "LONG":"SHORT");
}

void incrCallback(AbstractKeyboardElement* button, int state) {
  DEBUG_PRINT("LS ");
  DEBUG_PRINT(1);
  DEBUG_PRINT(" has value ");
  DEBUG_PRINTLN(state);
}

/******************************************************************************************/


void setup() {

  // serial
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  initKeyboard();

}

// run the program
void loop() {
 keyboard.loop();
}
