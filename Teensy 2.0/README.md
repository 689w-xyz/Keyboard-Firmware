# Teensy 2.0 Keyboard-Firmware
Simple keyboard firmware

## Files
### 000_Cylin46_R01.ino
- setup()  
- main()  
- Uncomment #define DEBUG to enable debug output.

### 010_Keymap.ino
- Added and shortened the key name.

### 100_CheckLEDS.ino
- Read the state of the lock key and turn on the LED.

### 200_scanKeys.ino
- Define layers and macro keys.
- Functions related to keyboard input are defined and processed.

### pitches.h
- Define tone and pitch.

## Layers
If you press and hold the layer key, it works like "Shift",  
and if you tap it, the layer is switched.
### Layer 0  
![image](https://user-images.githubusercontent.com/100514330/224507654-a70e91f1-850d-45d4-a23b-d65fa5f9df85.png)

### Layer 1
I use the Phone Layouts for number  
Number input layer (for calculations in Excel, etc.)  
![image](https://user-images.githubusercontent.com/100514330/224507656-045ccd6d-5eb6-44fd-8cfe-ea433863d5d4.png)

### Layer 2
Macro and Function Key and Modi Keys  
![image](https://user-images.githubusercontent.com/100514330/224507660-f67508f1-3e29-4b26-9b71-d3ce9c5dfdf6.png)
