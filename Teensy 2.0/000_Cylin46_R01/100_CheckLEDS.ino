// 1=num lock, 2=caps lock, 4=scroll lock, 8=compose, 16=kana
// 00000001 = num lock
// 00000010 = caps lock
// 00000011 = both num lock and caps lock, etc
// Bit numbers for each led - used to make it easier later to know what you were actually testing for...
#define USB_LED_NUM_LOCK 1
#define USB_LED_CAPS_LOCK 2
#define USB_LED_SCROLL_LOCK 4
#define USB_LED_COMPOSE 8
#define USB_LED_KANA 16

extern volatile uint8_t keyboard_leds; //lets code access this variable found in usb_keyboard.h and usb_private.h; neither could be #include-ed for some reason
short keyboard_leds_bf = 0xFF;

// Keyboard keylocks check and Turn on LEDs
void CheckLEDS(void)
{
  if (keyboard_leds_bf != keyboard_leds)
  {
    keyboard_leds_bf = keyboard_leds;
    if (keyboard_leds & USB_LED_NUM_LOCK)
    {
        // NumLock is ON - put your "on" code here
        // 230124 LED Controlled by LOW (GND)
        digitalWrite(NUM_LOCK, LOW);
#ifdef CHECKLOCKLED        
        Serial.print("NumLock ON..");        Serial.print('\n');
#endif   
    }
    else
    {
        // NumLock is OFF - put your "off" code here
        // 230124 LED Controlled by LOW (GND)
        digitalWrite(NUM_LOCK, HIGH);
#ifdef CHECKLOCKLED
        Serial.print("NumLock OFF..");        Serial.print('\n');
#endif        
    }
        if (keyboard_leds & USB_LED_CAPS_LOCK)
    {
        // CapsLock is ON - put your "on" code here
        // 230124 LED Controlled by LOW (GND)
        digitalWrite(CAPS_LOCK, LOW);
#ifdef DEBUG        
        Serial.print("CapsLock ON..");        Serial.print('\n');
#endif        
    }
    else
    {
        // CapsLock is OFF - put your "off" code here
        // 230124 LED Controlled by LOW (GND)
        digitalWrite(CAPS_LOCK, HIGH);
#ifdef CHECKLOCKLED        
        Serial.print("CapsLock OFF..");        Serial.print('\n');
#endif        
    }
    if (keyboard_leds & USB_LED_SCROLL_LOCK)
    {
        // Scroll Lock is ON - put your "on" code here
        // 230124 LED Controlled by LOW (GND)
        digitalWrite(SCROLL_LOCK, LOW);
#ifdef CHECKLOCKLED        
        Serial.print("Scroll Lock ON..");        Serial.print('\n');
#endif        
    }
    else
    {
        // Scroll Lock is OFF - put your "off" code here
        // 230124 LED Controlled by LOW (GND)
        digitalWrite(SCROLL_LOCK, HIGH);
#ifdef CHECKLOCKLED        
        Serial.print("Scroll Lock OFF..");        Serial.print('\n');
#endif        
    }
  }
}

//-----------no more-------------
