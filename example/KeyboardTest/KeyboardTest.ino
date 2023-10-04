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
  //keyboard = new OrganKeyboard(6);
  keyboard.addElement(new Poti(A0, poti1Callback));
  keyboard.addElement(new IncrButton(A1, incrCallback));
  keyboard.addElement(new LSButton(A2,lsCallback) );
  keyboard.addElement(new IncrButton(A3, button1Callback));

  keyboard.setup();

}

/******************************************************************************************/
// callbacks
void button1Callback(int state) {
  DEBUG_PRINT("Button");
  DEBUG_PRINT(1);
  DEBUG_PRINT(" is ");
  if (state) {
    DEBUG_PRINTLN("ON");

  } else {
    DEBUG_PRINTLN("OFF");
  }
}

void poti1Callback(int state) {
  DEBUG_PRINT("Poti ");
  DEBUG_PRINT(1);
  DEBUG_PRINT(" has value ");
  DEBUG_PRINTLN(state);
}

void lsCallback(int state) {
  DEBUG_PRINT("LS ");
  DEBUG_PRINT(1);
  DEBUG_PRINT(" has value ");
  DEBUG_PRINTLN(state);
}

void incrCallback(int state) {
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
