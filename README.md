# Keyboard-Firmware
Simple keyboard firmware

## Arduino Arduino 1.8.19 and Teensy 2.0
 - First need to Modify keylayouts.h

(C:\Program Files (x86)\Arduino\hardware\teensy\avr\cores\teensy\keylayouts.h)

      //#define ASCII_22	DIAERESIS_BITS + KEY_SPACE	// 34 "
      
    #define ASCII_22	KEY_QUOTE + SHIFT_MASK		    // 34 "

      //#define ASCII_5E	CIRCUMFLEX_BITS + KEY_SPACE	// 94 ^

      #define ASCII_5E	KEY_6 + SHIFT_MASK		        // 94 ^
