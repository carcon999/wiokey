/*
 * keyboardmap.h
 * 
 * 
 */
#ifndef keyboardmap_h
#define keyboradmap_h

#include "def.h"

// インラインアセンブラで指定したファイルをROMに配置するコードです。
#define  INC_BIN(file, sym) \
__asm(\
  ".balign 4\n"\
  ".globl " #sym "\n"\
  #sym ":\n"\
  ".incbin " #file "\n"\
  ".global _sizeof_" #sym "\n"\
  ".set _sizeof_" #sym ", . - " #sym "\n"\
);\
extern const uint8_t sym [];\
extern const uint8_t _sizeof_ ## sym [];\

// ここは、各自の環境に合わせてフルパスを記述する必要がある。（相対パスだとファイルが見つからない）
// ご自身の環境に合わせてxxxxxxを変更してください。
// 画像は、１キー辺り80x80pixで作成しておく。
INC_BIN("C:\\xxxxxx\\wiokey12\\data\\mic.png",   png_mic);
INC_BIN("C:\\xxxxxx\\wiokey12\\data\\video.png", png_video);
INC_BIN("C:\\xxxxxx\\wiokey12\\data\\share.png", png_share);
INC_BIN("C:\\xxxxxx\\wiokey12\\data\\quit.png",  png_quit);

INC_BIN("C:\\xxxxxx\\wiokey12\\data\\win.png",   png_win);
INC_BIN("C:\\xxxxxx\\wiokey12\\data\\mac.png",   png_mac);
INC_BIN("C:\\xxxxxx\\wiokey12\\data\\zoom1.png", png_zoom1);
INC_BIN("C:\\xxxxxx\\wiokey12\\data\\zoom2.png", png_zoom2);

INC_BIN("C:\\xxxxxx\\wiokey12\\data\\meet1.png", png_meet1);
INC_BIN("C:\\xxxxxx\\wiokey12\\data\\meet2.png", png_meet2);

typedef struct{
  const uint8_t* pimg;  // png image pointer
  int     sz;           // image size
  uint8_t x;            // image pos x
  uint8_t y;            // image pos y
  uint8_t modifiers;    // key shift etc
  uint8_t keycode;      // key code
  uint8_t keyopt;       // key option
  uint8_t r;            // color r
  uint8_t g;            // color g
  uint8_t b;            // color b
}KEYMAP;

// keycode
// https://github.com/platformio/platformio-pkg-framework-arduinosam/blob/master/cores/adafruit/Adafruit_TinyUSB_Core/tinyusb/src/class/hid/hid.h

// modifiers
//#define KEYBOARD_MODIFIER_LEFTCTRL                    (1 << 0)
//#define KEYBOARD_MODIFIER_LEFTSHIFT                   (1 << 1)
//#define KEYBOARD_MODIFIER_LEFTALT                     (1 << 2)
//#define KEYBOARD_MODIFIER_LEFTGUI                     (1 << 3)
//#define KEYBOARD_MODIFIER_RIGHTCTRL                   (1 << 4)
//#define KEYBOARD_MODIFIER_RIGHTSHIFT                  (1 << 5)
//#define KEYBOARD_MODIFIER_RIGHTALT                    (1 << 6)
//#define KEYBOARD_MODIFIER_RIGHTGUI                    (1 << 7)

const KEYMAP tKeyMap[LAYER_MAX][NUMBER_OF_KEYS] = 
{
  // layer1
  // Zoom Windows & Mac
  // https://icon-rainbow.com/license/
  {
    // 12キーの場合の液晶右側のキーボード
    // 24キーの場合の液晶左側のキーボード
    {png_mic,   (int)_sizeof_png_mic,   0, 0, KEYBOARD_MODIFIER_LEFTALT, HID_KEY_A, 0, 255, 0, 0},       // ミュート Alt + A
    {png_video, (int)_sizeof_png_video, 1, 0, KEYBOARD_MODIFIER_LEFTALT, HID_KEY_V, 0, 128, 0, 255},     // ビデオ　 Alt + V
    {png_share, (int)_sizeof_png_share, 2, 0, KEYBOARD_MODIFIER_LEFTALT, HID_KEY_S, 0, 0, 255, 0},       // 画面共有 Alt + S
    {png_quit,  (int)_sizeof_png_quit,  3, 0, KEYBOARD_MODIFIER_LEFTALT, HID_KEY_Q, 0, 128, 128, 128},   // 終了    Alt + Q
    {png_win,   (int)_sizeof_png_win,   0, 1, 0, 0, 0, 0, 0, 0},
    {png_zoom1, (int)_sizeof_png_zoom1, 1, 1, 0, 0, 0, 0, 0, 0},
    {png_zoom2, (int)_sizeof_png_zoom2, 2, 1, 0, 0, 0, 0, 0, 0},
    {png_mac ,  (int)_sizeof_png_mac,   3, 1, 0, 0, 0, 0, 0, 0},
    {png_mic,   (int)_sizeof_png_mic,   0, 2, KEYBOARD_MODIFIER_LEFTSHIFT | KEYBOARD_MODIFIER_LEFTGUI, HID_KEY_A, 0, 255, 0,   0},     // ミュート  SHIFT + COMMAND + A
    {png_video, (int)_sizeof_png_video, 1, 2, KEYBOARD_MODIFIER_LEFTSHIFT | KEYBOARD_MODIFIER_LEFTGUI, HID_KEY_V, 0, 128, 0,   255},   // ビデオ　  SHIFT + COMMAND + V
    {png_share, (int)_sizeof_png_share, 2, 2, KEYBOARD_MODIFIER_LEFTSHIFT | KEYBOARD_MODIFIER_LEFTGUI, HID_KEY_S, 0,   0, 255, 0},     // 画面共有  SHIFT + COMMAND + S    
    {png_quit,  (int)_sizeof_png_quit,  3, 2, KEYBOARD_MODIFIER_LEFTGUI,                               HID_KEY_R, 0, 128, 128, 128}    // 終了     COMMAND + Q

#ifndef KEY_TYPE_12
    ,
    // 24キーの場合の液晶右側のキーボード
    {NULL,      (int)0,    4, 0, 0, 0, 0, 255, 0, 0}, //　上段
    {NULL,      (int)0,    5, 0, 0, 0, 0, 0, 0, 255}, // 
    {NULL,      (int)0,    6, 0, 0, 0, 0, 255, 0, 0}, // 
    {NULL,      (int)0,    7, 0, 0, 0, 0, 0, 0, 255}, // 
    {NULL,      (int)0,    4, 1, 0, 0, 0, 0, 0, 255}, //  中段
    {NULL,      (int)0,    5, 1, 0, 0, 0, 255, 0, 0}, // 
    {NULL,      (int)0,    6, 1, 0, 0, 0, 0, 0, 255}, // 
    {NULL,      (int)0,    7, 1, 0, 0, 0, 255, 0, 0}, // 
    {NULL,      (int)0,    4, 2, 0, 0, 0, 255, 0, 0}, //  下段
    {NULL,      (int)0,    5, 2, 0, 0, 0, 0, 0, 255}, // 
    {NULL,      (int)0,    6, 2, 0, 0, 0, 255, 0, 0}, // 
    {NULL,      (int)0,    7, 2, 0, 0, 0, 0, 0, 255}  // 
#endif
  },
  // layer2
  // Meet Windows & Mac
  // https://icon-rainbow.com/license/
  {
    // 12キーの場合の液晶右側のキーボード
    // 24キーの場合の液晶左側のキーボード
    {png_quit,  (int)_sizeof_png_quit,  3, 2, KEYBOARD_MODIFIER_LEFTGUI, HID_KEY_W, 0, 128, 128, 128},   // 終了     COMMAND + Q
    {NULL,      (int)0,                 2, 2, 0, 0, 0, 0, 0, 0},                                         // 無し
    {png_video, (int)_sizeof_png_video, 1, 2, KEYBOARD_MODIFIER_LEFTGUI, HID_KEY_E, 0, 128, 0,   255},   // ビデオ　  COMMAND + E
    {png_mic,   (int)_sizeof_png_mic,   0, 2, KEYBOARD_MODIFIER_LEFTGUI, HID_KEY_D, 0, 255, 0,   0},     // ミュート  COMMAND + D
    {png_mac ,  (int)_sizeof_png_mac,   3, 1, 0, 0, 0, 0, 0, 0},
    {png_meet2, (int)_sizeof_png_meet2, 2, 1, 0, 0, 0, 0, 0, 0},
    {png_meet1, (int)_sizeof_png_meet1, 1, 1, 0, 0, 0, 0, 0, 0},
    {png_win,   (int)_sizeof_png_win,   0, 1, 0, 0, 0, 0, 0, 0},
    {png_quit,  (int)_sizeof_png_quit,  3, 0, KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_W, 0, 128, 128, 128},  // 終了 Ctrl + W
    {NULL,      (int)0,                 2, 0, 0, 0, 0, 0, 0, 0},                                         // 無し
    {png_video, (int)_sizeof_png_video, 1, 0, KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_E, 0, 128, 0, 255},    // ビデオ　Ctrl + E
    {png_mic,   (int)_sizeof_png_mic,   0, 0, KEYBOARD_MODIFIER_LEFTCTRL, HID_KEY_D, 0, 255, 0, 0}       // ミュート Ctrl + D  
#ifndef KEY_TYPE_12
    ,
    // 24キーの場合の液晶右側のキーボード
    {NULL,      (int)0,    4, 0, 0, 0, 0, 0, 0, 255}, //　上段
    {NULL,      (int)0,    5, 0, 0, 0, 0, 255, 0, 0}, // 
    {NULL,      (int)0,    6, 0, 0, 0, 0, 0, 0, 255}, // 
    {NULL,      (int)0,    7, 0, 0, 0, 0, 255, 0, 0}, // 
    {NULL,      (int)0,    4, 1, 0, 0, 0, 255, 0, 0}, //  中段
    {NULL,      (int)0,    5, 1, 0, 0, 0, 0, 0, 255}, // 
    {NULL,      (int)0,    6, 1, 0, 0, 0, 255, 0, 0}, // 
    {NULL,      (int)0,    7, 1, 0, 0, 0, 0, 0, 255}, // 
    {NULL,      (int)0,    4, 2, 0, 0, 0, 0, 0, 255}, //  下段
    {NULL,      (int)0,    5, 2, 0, 0, 0, 255, 0, 0}, // 
    {NULL,      (int)0,    6, 2, 0, 0, 0, 0, 0, 255}, // 
    {NULL,      (int)0,    7, 2, 0, 0, 0, 255, 0, 0}  // 
#endif
  } 
};

#endif  // keyboradmap_h
