/*
 * Programming by Stefan Jakobsson, 2019
 * Released to public domain
 */
 
#define ROW_COUNT 5        //Number of rows in the keyboard matrix
#define COL_COUNT 14       //Number of columns in the keyboard matrix

#define DEBOUNCE 10         //Adjust as needed: increase if bouncing problem, decrease if not all keypresses register; not less than 2
#define SCAN_DELAY 5        //Delay between scan cycles in ms

#define KC_FN 67            //Keyboard matrix scan code for FN key. FN key switches between layer 0 and 1.
#define KEY_UNDEFINED -1    //For keyboard matrix positions not in use

int rowPins[] = {17,21,18,19,20};   //Teensy pins attached to matrix rows
int colPins[] = {16,15,14,2,3,4,12,11,10,9,8,7,6,5};  //Teensy pins attached to matrix columns

//Key codes for layer 0 (standard layer)
int layer_0[] = {KEY_ESC, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, 
                KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_ENTER,
                KEY_CAPS_LOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE, KEY_BACKSLASH, KEY_UNDEFINED,
                MODIFIERKEY_SHIFT, KEY_TILDE, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH, MODIFIERKEY_RIGHT_SHIFT, KEY_UNDEFINED,
                MODIFIERKEY_CTRL, MODIFIERKEY_GUI, MODIFIERKEY_ALT, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_SPACE, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, MODIFIERKEY_RIGHT_ALT, KEY_UNDEFINED, MODIFIERKEY_RIGHT_GUI, MODIFIERKEY_RIGHT_CTRL};

//Key codes for layer 1 (FN key pressed)
int layer_1[] = {KEY_TILDE, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_UNDEFINED,
                KEY_UNDEFINED, KEY_HOME, KEY_UP, KEY_PAGE_UP, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED,
                KEY_UNDEFINED, KEY_LEFT, KEY_UNDEFINED, KEY_RIGHT, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED,
                KEY_UNDEFINED, KEY_UNDEFINED, KEY_END, KEY_DOWN, KEY_PAGE_DOWN, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, 
                KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED, KEY_UNDEFINED};

int currentRow = 0;
int keyStatus[ROW_COUNT*COL_COUNT];

void setup() {
  //Row pins
  pinMode(rowPins[0], OUTPUT);
  digitalWrite(rowPins[0], LOW);
  
  int i;
  for (i=1;i<ROW_COUNT;i++){
    pinMode(rowPins[i], INPUT);
  }

  //Column pins
  for (i=0;i<COL_COUNT;i++){
    pinMode(colPins[i], INPUT_PULLUP);
  }

  //Clear keyStatus
  for (i=0;i<ROW_COUNT*COL_COUNT;i++){
    keyStatus[i]=0;
  }
}

void loop() {
  scanKeys();
  delay(SCAN_DELAY);
}

/*
 * Scan keyboard matrix, results stored in keyStatus array
 * 
 * Key status values:
 * DEBOUNCE*2                   = key press event
 * DEBOUNCE+1 to DEBOUNCE*2-1   = key down
 * DEBOUNCE                     = key release event
 * 0 to DEBOUNCE-1              = key up
*/
void scanKeys(){
  int i;
  for (i=0;i<ROW_COUNT*COL_COUNT;i++){
    int pin = getKeyPin(i);
    
    if (keyStatus[i]==0 && digitalRead(pin)==LOW){
      //Key press event
      keyStatus[i] = DEBOUNCE*2;
      keyPress(i);
    }
    else if (keyStatus[i]>DEBOUNCE+1){
      keyStatus[i]--;
    }
    else if (keyStatus[i]==DEBOUNCE+1 && digitalRead(pin)==HIGH){
      //Key release event
      keyStatus[i]--;
      keyRelease(i);
    }
    else if (keyStatus[i]>0 && keyStatus[i]<=DEBOUNCE){
      keyStatus[i]--;
    }
  }
}

/*
 * Returns input pin to be read by keyScan method
 * 
 * Param key is the keyboard matrix scan code (row * COL_COUNT + col)
 */
int getKeyPin(int key){
  int p = key/COL_COUNT;
  if (p != currentRow){
    pinMode(rowPins[currentRow], INPUT);
    pinMode(rowPins[p], OUTPUT);
    digitalWrite(rowPins[p], LOW);
    currentRow=p;
  }
  return colPins[key % COL_COUNT];
}

/*
 * Sends key press event
 * 
 * Param keyCode is the keyboard matrix scan code (row * COL_COUNT + col)
 */

void keyPress(int keyCode){
  if (keyCode == KC_FN) releaseLayer(layer_0);
  else if (isKeyDown(KC_FN) && layer_1[keyCode]!=KEY_UNDEFINED){
    Keyboard.press(layer_1[keyCode]);
  }
  else if (layer_0[keyCode]!=KEY_UNDEFINED){
    Keyboard.press(layer_0[keyCode]);
  }
}

/*
 * Sends key release event
 * 
 * Param keyCode is the keyboard matrix scan code (row * COL_COUNT + col)
 */
 
void keyRelease(int keyCode){
  if (keyCode == KC_FN) releaseLayer(layer_1);
  else if (isKeyDown(KC_FN) && layer_1[keyCode]!=KEY_UNDEFINED){
    Keyboard.release(layer_1[keyCode]);
  }
  else if (layer_0[keyCode]!=KEY_UNDEFINED){
    Keyboard.release(layer_0[keyCode]);
  }
}

/*
 * Relases all keys in the layer; called upon change of layer, i.e. press or release of FN key
 * 
 * Param layer[] array of key codes for the layer to be released
 */
void releaseLayer(int layer[]){
  int i;
  for (i=0;i<ROW_COUNT*COL_COUNT;i++){
    if (i!=KC_FN && isKeyDown(i)){
      keyStatus[i] = DEBOUNCE;
      Keyboard.release(layer[i]);
    }
  }
}

/*
 * Returns 0 if the specified key is pressed, otherwise a value not equal to 0
 * 
 * Param keyCode is the keyboard matrix scan code (row * COL_COUNT * col)
 */
 int isKeyDown(int keyCode){
 if (keyStatus[keyCode]>DEBOUNCE) return 1; else return 0; 
}
