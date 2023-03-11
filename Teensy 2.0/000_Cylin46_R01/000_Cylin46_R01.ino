/*
 It is based on a program published on forum.pjrc.com 
 by "Stefan Jakobsson (2019)". 
 Thank you for putting your program into the public domain.
 
 I also release this program in the public domain. (689w.xyz@gmail.com)
 
 Modified to enable use of multi layers, 
 and added indicators for layers and lock keys.
*/

// KEYCODE_TYPE   uint16_t
// KEYCODE_MASK   0x07FF
// LayerKey is over 0x07FF

// #ifdef #ifndef #else #endif
// #define DEBUG 1 // debug mode Serial output. disable in release
// #define CHECKLOOPTIME 1 // check loop time
// #define VARIABLE_BLINKING 1 // The blink rate changes according to the typing speed.
// #define CHECKLOCKLED 1 // check lock LED
// #define CHECKOUTPUT 1 // check key code
// #define MUTE 1 // 230124 sound mute mode 

// 230121 make sound
#include "pitches.h"
// 221225 enable when 23 pin shorted (can stop input when some bugs occur)
#define UNABLEKEY 23
// 221225 start function blinking in board LED
#define STATUSLED 11
// 230121 speaker pin
#define SPEAKER 10  //PWM
// 221225 blink timer
int turnOnTime = 0;
int turnOffTime = 0;
int rateBlink = 1;
int rateBlinkb = 1;
bool toggleLED = false;

#define ROW_COUNT 4        // Number of rows in the keyboard matrix
#define COL_COUNT 12       // Number of columns in the keyboard matrix
#define KEYS  48            // 4th row 1st 12th not use 
#define LAYER 3           //Number of Layer
int rowPins[] = {21,20,19,18};   //Teensy pins attached to matrix rows
int colPins[] = {24,0,1,2,3,4,5,6,7,8,9,22};  //Teensy pins attached to matrix columns

// it used scankeys
struct keySW{
  int iTime;      // Debounce Timer
  bool bPressed;  // Pressed or Released status
  bool bMask;     // mask set when layer key changed
  int iLayer;     // layer of Pressed key 
}stKeyStatus[ROW_COUNT*COL_COUNT];
//int keyStatus[ROW_COUNT*COL_COUNT];

#define SCAN_DELAY 3        //Scan Interval
// 230212 delayed loop parameter
unsigned int uiDeley = 10;
long lCheckTime = 0;
unsigned int uiChecked_1k = 0;

//230305 find loop per time (500ms(?))
long lLayerToggleLoopCnt = 61;   // maybe 500ms(?)
long lmsPerLoopCheck = 0;  // check loop time
int iLoopCntSub = 0;
int iLoopCntCheck = 0;
bool bToggleLoopChecked = false;
// 500ms(?)
const long clLayerToggleTime = 500;

// it used scankeys and main
int currentLayer = 0;
int beforeLayer = 1;
unsigned int layerToggleTimer = 0;
bool layerTogglePrepare = false;

bool loopEnabled = false;

// 221225 Layer indicator RGB LED value
int redValue = 255;
int greenValue = 255;
int blueValue = 255;
// dimming RGB LED
int iValue = 4;
        
//#include<keyboard.h>
//#include <Bounce.h>

#define NUM_LOCK 13
#define CAPS_LOCK 16
#define SCROLL_LOCK 17

//221225 Layer (PWM Analog) 
#define RED  15   // 15 pin that red led is connected to    
#define GREEN  14 // 14 pin that green led is connected to     
#define BLUE  12  // 12 pin that blue led is connected to

void setup() {
  //Row pins
  int i;
  for (i=1;i<ROW_COUNT;i++){
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
  //Column pins
  for (i=0;i<COL_COUNT;i++){
    pinMode(colPins[i], INPUT_PULLUP);    
  }
  //Clear keyStatus
  for (i=0;i<ROW_COUNT*COL_COUNT;i++){
    stKeyStatus[i].iTime=0;
    stKeyStatus[i].bPressed=false;
    stKeyStatus[i].bMask=false;
    stKeyStatus[i].iLayer=0;
  }
  
  pinMode(UNABLEKEY,INPUT_PULLUP);
  pinMode(STATUSLED,OUTPUT);
  pinMode(SPEAKER,OUTPUT);
  //221225 layer indicator 
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  //221225 STATUS LED
  pinMode(NUM_LOCK, OUTPUT);
  digitalWrite(NUM_LOCK, HIGH);
  pinMode(CAPS_LOCK, OUTPUT);
  digitalWrite(CAPS_LOCK, HIGH);
  pinMode(SCROLL_LOCK, OUTPUT);
  digitalWrite(SCROLL_LOCK, HIGH);
  
#ifdef DEBUG
  Serial.begin(9600);
#endif
  redValue = 255 - iValue;
  greenValue = 255 - iValue;
  blueValue = 255 - iValue;
  analogWrite(RED, redValue); // red initially ON
  analogWrite(GREEN, greenValue); // green initially ON
  analogWrite(BLUE, blueValue); // blue ON  // -> white
  //230305 check loop start time
  lmsPerLoopCheck = millis();
}

//zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
// main
//
void loop() {
  // 230305 find loop per time (200ms)
  if (bToggleLoopChecked == false){
    if (iLoopCntCheck > 10){
      bToggleLoopChecked = true;
#ifdef CHECKLOOPTIME
      Serial.print("500 millisec Loop Cnt: ");
      Serial.print(lLayerToggleLoopCnt); Serial.print('\n');
#endif
    }
    else{
      if (iLoopCntSub > 10){
        iLoopCntCheck++;
        iLoopCntSub=0;
        lmsPerLoopCheck = (millis() - lmsPerLoopCheck)/10;
        if (lmsPerLoopCheck > 0)
          lLayerToggleLoopCnt = clLayerToggleTime / lmsPerLoopCheck;
      }
      else  iLoopCntSub++;
    }
  }
  if ( uiDeley < SCAN_DELAY )    uiDeley++;
  else {
#ifdef CHECKLOOPTIME
    // check 1000 loop time
    if ( uiChecked_1k < 1000) uiChecked_1k++;
    else {          
      uiChecked_1k = 0;
      Serial.print("Thousand looped millisec : ");
      Serial.print(millis() - lCheckTime);
      Serial.print('\n');
      lCheckTime = millis();    
    }
#endif
    uiDeley = 0;
    // check all function enable or disable
    if (digitalRead(UNABLEKEY) == LOW) loopEnabled = true;
    else loopEnabled = false;
    
    // keyboard function
    if (loopEnabled == true){
      // toggle LED and sound HeartBeat
      if (toggleLED == true) {
        turnOnTime++;
        if (turnOnTime > (600/rateBlink))  {          
          turnOnTime = 0;
          toggleLED = false;
          digitalWrite(STATUSLED, LOW);
#ifndef MUTE
          // 230121 sound
          noTone(SPEAKER);
#endif      
        }
      }
      else { //if (toggleLED == true)
        turnOffTime++;
        if (turnOffTime > (300/rateBlink))
        {          
          turnOffTime = 0;
          toggleLED = true;
          digitalWrite(STATUSLED, HIGH);
#ifndef MUTE          
          // 230121 sound
          tone(SPEAKER,NOTE_DS8,600/rateBlink);
#endif          
        }
      }
      // check key lock status
      CheckLEDS();
      // scan key status
      rateBlinkb = rateBlink;
      // check key matrix, key pressed or released
      rateBlink = scanKeys();
      //delay(SCAN_DELAY);
      
#ifdef VARIABLE_BLINKING
     if (rateBlinkb != rateBlink)
     {
       Serial.print("Rate : ");
       Serial.print(rateBlink);
       Serial.print('\n');
     }
#endif
    // Layer indicator Check
      if (beforeLayer != currentLayer) {        
        if (currentLayer == 0)
        {
              redValue = 255 - iValue;      greenValue = 255;      blueValue = 255;
        }
        if (currentLayer == 1)
        {
              redValue = 255;      greenValue = 255 - iValue;      blueValue = 255;
        }
        if (currentLayer == 2)
        {
              redValue = 255;      greenValue = 255;      blueValue = 255 - iValue;
        }
        analogWrite(RED, redValue);
        analogWrite(GREEN, greenValue);
        analogWrite(BLUE, blueValue);
      }
    } //if (loopEnabled == false)
  }   // if (uiDeley < SCAN_DELAY ) uiDeley++;
}

//
// main End
//zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz

//-----------------------------functions are seperated file
//-----------no more-------------
