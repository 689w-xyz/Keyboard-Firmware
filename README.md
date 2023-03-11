# Keyboard-Firmware
Simple keyboard firmware

## 0.Thanks to Stefan Jakobsson.
Based on the program in the link below.

https://forum.pjrc.com/threads/55395-queued-Keyboard-simple-firmware

## 1.Arduino Arduino 1.8.19 and Teensy
 - First need to Modify keylayouts.h

(C:\Program Files (x86)\Arduino\hardware\teensy\avr\cores\teensy\keylayouts.h)

      //#define ASCII_22	DIAERESIS_BITS + KEY_SPACE	// 34 "
      
    #define ASCII_22	KEY_QUOTE + SHIFT_MASK		    // 34 "

      //#define ASCII_5E	CIRCUMFLEX_BITS + KEY_SPACE	// 94 ^

      #define ASCII_5E	KEY_6 + SHIFT_MASK		        // 94 ^

I separated the code using arduino style (not a good way).

## 2.Bugs
On some older systems, key.release() sometimes (rarely) doesn't work after key.press() has done.
In this case, pressing another key releases it.
It could also happen because of a specific function I put in.
## 3.Planned improvement
n-key rollover..
If I put the entered key into the queue buffer and forcefully release the key entered first, wouldn't it be possible to process the key input entered after the 7th? Of course, the last 6 keys are entered at the same time... but all keys pressed once will be entered.