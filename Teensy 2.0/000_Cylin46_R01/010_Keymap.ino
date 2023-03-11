#define KC_NO 65535 //For keyboard matrix positions not in use
#define KEY_UNDEFINED KC_NO //For keyboard matrix positions not in use
#define KC_LAYER4 KC_NO-1            //scan code for Layer 04 key.
#define KC_LAYER3 KC_LAYER4-1        //scan code for Layer 03 key.
#define KC_LAYER2 KC_LAYER3-1        //scan code for Layer 02 key.
#define KC_LAYER1 KC_LAYER2-1        //scan code for Layer 01 key.
#define KC_LAYER0 KC_LAYER1-1        //scan code for Layer 00 key.

#define KC_MCR9   KC_LAYER0-1      // Macro key 0
#define KC_MCR8   KC_MCR9-1        // Macro key 1
#define KC_MCR7   KC_MCR8-1        // Macro key 2
#define KC_MCR6   KC_MCR7-1        // Macro key 3
#define KC_MCR5   KC_MCR6-1        // Macro key 4
#define KC_MCR4   KC_MCR5-1        // Macro key 5
#define KC_MCR3   KC_MCR4-1        // Macro key 6
#define KC_MCR2   KC_MCR3-1        // Macro key 7
#define KC_MCR1   KC_MCR2-1        // Macro key 8
#define KC_MCR0   KC_MCR1-1        // Macro key 9

// US-English layout
// LAYER 1
#define KC_ESC KEY_ESC	// ESC
#define KC_A KEY_A	// A
#define KC_B KEY_B	// B
#define KC_C KEY_C	// C 
#define KC_D KEY_D	// D
#define KC_E KEY_E	// E
#define KC_F KEY_F	// F
#define KC_G KEY_G	// G
#define KC_H KEY_H	// H
#define KC_I KEY_I	// I
#define KC_J KEY_J	// J
#define KC_K KEY_K	// K
#define KC_L KEY_L	// L
#define KC_M KEY_M	// M
#define KC_N KEY_N	// N
#define KC_O KEY_O	// O
#define KC_P KEY_P	// P
#define KC_Q KEY_Q	// Q
#define KC_R KEY_R	// R
#define KC_S KEY_S	// S
#define KC_T KEY_T	// T
#define KC_U KEY_U	// U
#define KC_V KEY_V	// V
#define KC_W KEY_W	// W
#define KC_X KEY_X	// X
#define KC_Y KEY_Y	// Y
#define KC_Z KEY_Z	// Z
#define KC_DEL KEY_DELETE	// DELETE
#define KC_TAB KEY_TAB	// TAB
#define KC_LSFT MODIFIERKEY_SHIFT	// L SHIFT
#define KC_RSFT MODIFIERKEY_RIGHT_SHIFT	// R SHIFT
#define KC_MINS KEY_MINUS	// MINUX
#define KC_LALT MODIFIERKEY_ALT	// L ALT
#define KC_LCTL MODIFIERKEY_CTRL	// L CONTROL
#define KC_RALT MODIFIERKEY_RIGHT_ALT // R ALT
#define KC_RCTL MODIFIERKEY_RIGHT_CTRL // R CONTROL
#define KC_SPC KEY_SPACE	// SPACE
#define KC_BSPC KEY_BACKSPACE	// BACK SPACE
#define KC_LGUI MODIFIERKEY_GUI	// L WIN
#define KC_GRV KEY_TILDE	// `
#define KC_BSLS KEY_BACKSLASH	// BACKSLASH
#define KC_SCLN KEY_SEMICOLON	// ;
#define KC_ENT KEY_ENTER	// ENTER
#define KC_COMM KEY_COMMA	// ,
#define KC_DOT KEY_PERIOD	// .
#define KC_SLSH KEY_SLASH	// SLASH
// LAYER KEY 2 EA

// LAYER 2
#define KC_1 KEY_1	// 1
#define KC_2 KEY_2	// 2
#define KC_3 KEY_3	// 3
#define KC_4 KEY_4	// 4
#define KC_5 KEY_5	// 5
#define KC_6 KEY_6	// 6
#define KC_7 KEY_7	// 7
#define KC_8 KEY_8	// 8
#define KC_9 KEY_9	// 9
#define KC_0 KEY_0	// 0
#define KC_EQL KEY_EQUAL // =
#define KC_PSLS KEYPAD_SLASH // SLASH
#define KC_PAST KEYPAD_ASTERIX // *
#define KC_PPLS KEYPAD_PLUS // +
#define KC_PMNS KEYPAD_MINUS // -
#define KC_PENT KEYPAD_ENTER // ENTER
#define KC_CIRC 94 // ^   
//[keylayouts.h] //#define ASCII_5E CIRCUMFLEX_BITS + KEY_SPACE   // 94 ^ 
//                 #define ASCII_5E KEY_6 + SHIFT_MASK    // 94 ^
#define KC_HASH 35 // #
#define KC_AMPR 38 // &
#define KC_DLR 36 // $
#define KC_PGUP KEY_PAGE_UP // PAGE_UP
#define KC_PGDN KEY_PAGE_DOWN // PAGE_DOWN
#define KC_UP KEY_UP // UP
#define KC_DOWN KEY_DOWN // DOWN
#define KC_LEFT KEY_LEFT // LEFT
#define KC_RGHT KEY_RIGHT // RIGHT
#define KC_LPRN 40 // (
#define KC_RPRN 41 // )
#define KC_LCBR 123 // {
#define KC_RCBR 125 // }
#define KC_LBRC KEY_LEFT_BRACE // [
#define KC_RBRC KEY_RIGHT_BRACE // ]
#define KC_PERC 37 // %
#define KC_EXLM 33 // !
#define KC_AT 64 // @
#define KC_QUOT KEY_QUOTE // '
#define KC_DQUO 34 // "
//[keylayouts.h] bug??
//		#define ASCII_22  DIAERESIS_BITS + KEY_SPACE    // 34 "
//     #define ASCII_22  KEY_QUOTE + SHIFT_MASK    // 34 "

// ~ tyde = shift + `
// ! bikkuri = shift + 1
// @ atmark = shift + 2
// # shap = shift + 3
// $ dallar = shift + 4
// % percent = shift + 5
// ^ Circ = shift + 6
// & anpercent = shft + 7
// * astro = shft + 8
// ( open  = shft + 9
// ) close = shft + 0
// { shift + [
// } shift + ]

// LAYER 3
#define KC_F1 KEY_F1            //  F1
#define KC_F2 KEY_F2            //  F2
#define KC_F3 KEY_F3            //  F3
#define KC_F4 KEY_F4            //  F4
#define KC_F5 KEY_F5            //  F5
#define KC_F6 KEY_F6            //  F6
#define KC_F7 KEY_F7            //  F7
#define KC_F8 KEY_F8            //  F8
#define KC_F9 KEY_F9            //  F9
#define KC_F10 KEY_F10          //  F10
#define KC_F11 KEY_F11          //  F11
#define KC_F12 KEY_F12          //  F12
#define KC_NLCK KEY_NUM_LOCK    //  NUM LOCK
#define KC_CLCK KEY_CAPS_LOCK   // CAPS LOCK
#define KC_SLCK KEY_SCROLL_LOCK // SCROLL LOCK
#define KC_PAUS KEY_PAUSE       // PAUSE
#define KC_INS KEY_INSERT       // INSERT
#define KC_HOME KEY_HOME        // HOME
#define KC_END KEY_END          // END
#define KC_PSCR KEY_PRINTSCREEN // PRINT SCREEN
