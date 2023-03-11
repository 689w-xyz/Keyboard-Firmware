// reference for cording
// #define ROW_COUNT 4        // Number of rows in the keyboard matrix
// #define COL_COUNT 12       // Number of columns in the keyboard matrix
// #define KEYS  48            // not use 4th row 1st and 12th 
// #define LAYER 3           //Number of Layer
//  `TO(layer)` - activates *layer* and de-activates all other layers (except your default layer).
//                This function is special, because instead of just adding/removing one layer to your active layer stack, 
//                it will completely replace your current active layers, 
//                uniquely allowing you to replace higher layers with a lower one. 
//                This is activated on keydown (as soon as the key is pressed).
//  `TT(layer)` - Layer Tap-Toggle. If you hold the key down, *layer* is activated, 
//                and then is de-activated when you let go (like `MO`). 
//                If you repeatedly tap it, the layer will be toggled on or off (like `TG`).
//                It needs 5 taps by default, but you can change this by defining `TAPPING_TOGGLE` -- for example, 
//                `#define TAPPING_TOGGLE 2` to toggle on just two taps.


#define DEBOUNCE 7         //Adjust as needed: increase if bouncing problem, decrease if not all keypresses register; not less than 2
#define DEBOUNCE2 DEBOUNCE * 2;
#define MACRONM 10
#define MACROKEYMAX 10

//#define LAYER_STAY_TIMER l200ms
bool bLayerStayFlag = true;
int iLayerStayTimer = 0;
int currentRow = 0;

// 20230226 Key pressed count
int iKeyPressed = 0;
#define USBMAXKEY 6

// it used scankeys (key pressed status timer)
// int keyStatus[ROW_COUNT*COL_COUNT];
// struct keySW{
//   int iTime;
//   bool bPressed;
//   bool bMask;
//   int iLayer;
// }stKeyStatus[ROW_COUNT*COL_COUNT];
//Key codes for layer 0
unsigned int layer[LAYER][KEYS] = 
 {{KC_ESC,     KC_Q,  KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
   KC_TAB,     KC_A,  KC_S,    KC_D,    KC_F,    KC_G,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
   KC_LSFT,    KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
   KC_NO,   KC_MINS, KC_LALT, KC_LCTL, KC_LAYER1,KC_SPC, KC_BSPC,KC_LAYER2,KC_LGUI, KC_GRV , KC_BSLS, KC_NO},
//Key codes for layer 1
  {KC_ESC,  KC_PSLS,    KC_1,   KC_2, KC_3,    KC_PAST,  KC_HASH, KC_PGUP, KC_UP,   KC_LPRN,  KC_RPRN, KC_DEL,
   KC_TAB,  KC_PMNS,    KC_4,   KC_5, KC_6,    KC_PPLS,  KC_AMPR, KC_LEFT, KC_RGHT, KC_LCBR,  KC_RCBR, KC_PERC,
   KC_PENT,  KC_EQL,    KC_7,   KC_8, KC_9,    KC_CIRC,  KC_DLR,  KC_PGDN, KC_DOWN, KC_LBRC,  KC_RBRC, KC_EXLM,
   KC_NO,   KC_COMM,  KC_DOT,   KC_0,KC_LAYER0,KC_SPC,   KC_BSPC, KC_LAYER2, KC_AT,  KC_QUOT, KC_DQUO, KC_NO},
//Key codes for layer 2
  {KC_ESC,      KC_F1, KC_F2,  KC_F3,   KC_F4,   KC_NLCK, KC_PAUS, KC_PGUP,  KC_UP,   KC_MCR3,  KC_MCR2, KC_DEL,
   KC_TAB,      KC_F5, KC_F6,  KC_F7,   KC_F8,   KC_CLCK, KC_HOME, KC_LEFT,  KC_RGHT, KC_END, KC_MCR1,   KC_ENT,
   KC_LSFT,     KC_F9, KC_F10, KC_F11,  KC_F12,  KC_SLCK, KC_INS,   KC_PGDN, KC_DOWN, KC_MCR4,  KC_MCR0, KC_LSFT,
   KC_NO,     KC_RCTL, KC_LALT,KC_LCTL, KC_LAYER1,KC_SPC, KC_BSPC, KC_LAYER0,KC_LGUI, KC_PSCR, KC_RALT, KC_NO}};

// 230302 macro
unsigned int iMacro[MACRONM][MACROKEYMAX] = {
{KC_SLSH, KC_PAST, KC_PAST, KC_SLSH, KC_LEFT, KC_LEFT, KC_NO  , KC_NO  , KC_NO  , KC_NO  },
{KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  },
{KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  },
{KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  },
{KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  },
{KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  },
{KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  },
{KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  },
{KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  },
{KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  }};

// 20230226 n key roll over
int iKeyQueueInsert=0; 
int iKeyQueueDelete=0; 
unsigned int uiKeyPressQueue[USBMAXKEY]={0,0,0,0,0,0};

//221225 heart rate
long heartBit = 0;
long heartBitb = 0;
long heartRate = 0;
// 230121 If you don't press the keyboard, the status LED blinks slower.
long standBy = 0;

/*
 * Scan keyboard matrix, results stored in keyStatus array
 * 
 * Key status values:
 * DEBOUNCE*2                   = key press event
 * DEBOUNCE+1 to DEBOUNCE*2-1   = key down
 * DEBOUNCE                     = key release event
 * 0 to DEBOUNCE-1              = key up
*/

int scanKeys(){
  int i;
  iKeyPressed = 0;
  for (i=0;i<ROW_COUNT*COL_COUNT;i++){
    int pin = getKeyPin(i);
    int iPinStatus = digitalRead(pin);
    if (iPinStatus == LOW) iKeyPressed++;
    // key pressed
    if (stKeyStatus[i].iTime==0 && iPinStatus==LOW){
      //Key press event
      //keyStatus[i] = DEBOUNCE*2;
      stKeyStatus[i].iTime = DEBOUNCE2;  // DEBOUNCE*2

      //20230228 call keyPress if not Masked or keyRelease
      if ( stKeyStatus[i].bMask == false) keyPress(i);
      else  keyRelease(i);

      //221225 Pressing the keyboard frequently 
      //       causes the status LED to blink quickly.
      heartBitb = heartBit;      heartBit = millis();
      if (!(heartBit < heartBitb)) heartRate = 1000/(heartBit - heartBitb);
      else heartRate = 1;
    }
    // key pressed? check chettering
    else if (stKeyStatus[i].iTime>DEBOUNCE+1){
      stKeyStatus[i].iTime--;
    }
    else if (stKeyStatus[i].iTime==DEBOUNCE+1 && iPinStatus==HIGH){
      //Key release event
      stKeyStatus[i].iTime--;
      keyRelease(i);
    }
    else if (stKeyStatus[i].iTime>0 && stKeyStatus[i].iTime<=DEBOUNCE){
      stKeyStatus[i].iTime--;
    }
  }
  
  //layer toggle timer check
  if (bLayerStayFlag == true){
    if (iLayerStayTimer > 0) iLayerStayTimer--;
    else{
      // layer key pressed long time, if release key change before layer
      bLayerStayFlag = false;
#ifdef CHECKOUTPUT      
      Serial.print("Prepare layerToggleBefore");      Serial.print('\n');
#endif      
    }
  }
  if (heartRate > 1)  {  
    //230121 If you don't press a key on the keyboard, it blinks slowly.
    standBy++;
    if (standBy > 1000){
      heartRate--;
      standBy = 0;
    }
  }  
  if (heartRate < 1) heartRate = 1;
  if (heartRate > 10) heartRate = 10;
#ifdef CHECKOUTPUT      
//      Serial.print("heartRate:");
//      Serial.print(heartRate);   
//      Serial.print("_StandBy:"); 
//      Serial.print(standBy);      
//      Serial.print('\n');
#endif   
  return heartRate;
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
  bool bLayerKeyPushed = false;
  switch(layer[currentLayer][keyCode]){
    // 20230305 macro key added
    case KC_MCR0: MacroKey(0);  break;
    case KC_MCR1: MacroKey(1);  break;
    case KC_MCR2: MacroKey(2);  break;
    case KC_MCR3: MacroKey(3);  break;
    case KC_MCR4: MacroKey(4);  break;
    case KC_MCR5: MacroKey(5);  break;
    case KC_MCR6: MacroKey(6);  break;
    case KC_MCR7: MacroKey(7);  break;
    case KC_MCR8: MacroKey(8);  break;
    case KC_MCR9: MacroKey(9);  break;
    // 20230226 only layer key input
    case KC_LAYER0:
      // change layer to '0'
#ifdef CHECKOUTPUT    
      Serial.print("Change Layer 0");    Serial.print('\n');
#endif    
      beforeLayer = currentLayer;
      currentLayer = 0;
      bLayerKeyPushed = true;
      break;
    case KC_LAYER1:
      // change layer to '1'
#ifdef CHECKOUTPUT    
      Serial.print("Change Layer 1");    Serial.print('\n');
#endif    
      beforeLayer = currentLayer;
      currentLayer = 1;
      bLayerKeyPushed = true;
      break;
    case KC_LAYER2:
      // change layer to '2'
#ifdef CHECKOUTPUT    
      Serial.print("Change Layer 2");    Serial.print('\n');
#endif    
      beforeLayer = currentLayer;
      currentLayer = 2;  
      bLayerKeyPushed = true;  
      break;
    case KC_NO:
      break;
    default:
      if ( stKeyStatus[keyCode].bPressed == true &&
          stKeyStatus[keyCode].iLayer != currentLayer)
            stKeyStatus[keyCode].bMask = true;
      else{
        stKeyStatus[keyCode].bPressed = true;
        stKeyStatus[keyCode].iLayer = currentLayer;
        // 20230226 try nkey roll over
        QueueKeyPress(layer[currentLayer][keyCode]);
      }
#ifdef CHECKOUTPUT      
      Serial.print("KeyPressed:");
      Serial.print(iKeyPressed);      Serial.print('\n');
      Serial.print("Pressed_Ly-");
      Serial.print(currentLayer); 
      Serial.print("_KC-");
      Serial.print(layer[currentLayer][keyCode]);
      Serial.print('\n');
#endif    
      break;
  }
  // Layer change common 
  if (bLayerKeyPushed == true){
    // release all key in before layer
    releaseLayer(layer[beforeLayer]);
    iLayerStayTimer = lLayerToggleLoopCnt;
    bLayerStayFlag = true;
    stKeyStatus[keyCode].iTime = DEBOUNCE*3;
  }
}

/*
 * Sends key release event
 * 
 * Param keyCode is the keyboard matrix scan code (row * COL_COUNT + col)
 */
 
void keyRelease(int keyCode){
  // 20230228 Key Status change
  bool bLayerKeyReleased = false;
  int iTmpLayer = 0;
  
  switch(layer[currentLayer][keyCode]){
    case KC_MCR0:
    case KC_MCR1:
    case KC_MCR2:
    case KC_MCR3:
    case KC_MCR4:
    case KC_MCR5:
    case KC_MCR6:
    case KC_MCR7:
    case KC_MCR8:
    case KC_MCR9: break;
    case KC_LAYER0:
    case KC_LAYER1:
    case KC_LAYER2:    
      bLayerKeyReleased = true;
      break;
    case KC_NO:
      break;
    default:
      // 20230228 unset mask
      stKeyStatus[keyCode].bMask = false;
      if ( stKeyStatus[keyCode].bPressed == true ){
        stKeyStatus[keyCode].bPressed = false;
        Keyboard.release(layer[currentLayer][keyCode]);
        // 20230226 try nkey roll over
      }
#ifdef CHECKOUTPUT      
      Serial.print("KeyPressed:");
      Serial.print(iKeyPressed);      Serial.print('\n');
      Serial.print("released_Ly-");
      Serial.print(currentLayer); 
      Serial.print("_KC-");
      Serial.print(layer[currentLayer][keyCode]);
      Serial.print('\n');
#endif   
      break;
  }
  // Layer change common
  if (bLayerKeyReleased == true){
    // 230211 layer key pressed long time
    if(bLayerStayFlag == false){
      releaseLayer(layer[currentLayer]);
      // when long pressed change before layer
#ifdef CHECKOUTPUT      
      Serial.print("Change Before Layer ");      
      Serial.print(beforeLayer);      Serial.print('\n');
#endif
      iTmpLayer = currentLayer;
      currentLayer = beforeLayer;      
      beforeLayer = iTmpLayer;
    }
    else{
        // when short pressed not change before layer
#ifdef CHECKOUTPUT      
        Serial.print("Stay Layer ");      
        Serial.print(beforeLayer);      Serial.print('\n');
#endif      
    }
  }
}

/*
 * Relases all keys in the layer; called upon change of layer, i.e. press or release of FN key
 * 
 * Param layer[] array of key codes for the layer to be released
 */
void releaseLayer(unsigned int iOldLayer[]){
#ifdef CHECKOUTPUT      
          Serial.print("release layer");  Serial.print('\n');
#endif    
  int i;
  // 230121 KC_NO added
  for (i=0;i<ROW_COUNT*COL_COUNT;i++){
    switch(iOldLayer[i]){
      case KC_LAYER0:
      case KC_LAYER1:
      case KC_LAYER2:
      case KC_NO:
        break;
      default:
        if(isKeyDown(i)){
          stKeyStatus[i].iTime = DEBOUNCE;
          Keyboard.release(iOldLayer[i]);
#ifdef CHECKOUTPUT      
          Serial.print("release layer KC-");
          Serial.print(iOldLayer[i]);  Serial.print('\n');
#endif        
        }
        break;
    }
  }
}

/*
 * Returns 0 if the specified key is pressed, otherwise a value not equal to 0
 * 
 * Param keyCode is the keyboard matrix scan code (row * COL_COUNT * col)
 */
int isKeyDown(int keyCode){
  if (stKeyStatus[keyCode].iTime>DEBOUNCE) return 1; else return 0; 
}

// 20230226 try nkey roll over
// unsigned int uiKeyPressQueue[USBMAXKEY]=
void QueueKeyPress(unsigned int ikeyPressed){
  // 20230226 insert key input to queue
  uiKeyPressQueue[iKeyQueueInsert] = ikeyPressed;  
  if ( iKeyPressed > USBMAXKEY){
    Keyboard.release(uiKeyPressQueue[iKeyQueueDelete]);
#ifdef CHECKOUTPUT      
    Serial.print("release Queued KC-");
    Serial.print(uiKeyPressQueue[iKeyQueueDelete]);  Serial.print('\n');
#endif 
    iKeyQueueDelete++;
    if ( iKeyQueueDelete > USBMAXKEY ) iKeyQueueInsert=0;
    Keyboard.press(ikeyPressed);
  }
  else{
    iKeyQueueInsert = 0;
    Keyboard.press(ikeyPressed);
  }  
  iKeyQueueInsert++;
  if ( iKeyQueueInsert > USBMAXKEY ) iKeyQueueInsert=0;
}

/*Marco Key function 
  Max 10 combo key
  ended by KC_NO  */
void MacroKey(int iKey){  
  int i=0;
#ifdef CHECKOUTPUT      
          Serial.print("Macro Key : ");
          Serial.print(iKey);  Serial.print('\n');
#endif   
  if ( iKey < MACRONM){
    for (i=0; i<MACROKEYMAX; i++){
      if (iMacro[iKey][i] != KC_NO){
#ifdef CHECKOUTPUT      
        Serial.print("Macro Key : ");
        Serial.print(iMacro[iKey][i]);  Serial.print('\n');
#endif           
        Keyboard.press(iMacro[iKey][i]);
        // delay
        int j=0;  for(j=0; j<100;j++);
        Keyboard.release(iMacro[iKey][i]);
      }
    }
  }
}
//-----------no more-------------
