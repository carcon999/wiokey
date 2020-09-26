/*
 * drv_keyboard.h
 * 
 * 
 */
#ifndef drv_keyboard_h
#define drv_keyboard_h

#include "def.h"

// クラスの定義
// クラス名・コンストラクタ名・関数名や使用する変数名を定義します。
class Keyboard
{
  public:
    Keyboard();
    void setup(void);
    void loop(void);
    void setkeycode(int x, int y, uint8_t modifier, uint8_t code);
    
  private:
    void report(uint32_t current, uint32_t before);

  private:
    uint8_t keycode[NUMBER_OF_KEYS];
    uint8_t modifiers[NUMBER_OF_KEYS];
    uint32_t before_keyflags;
};

extern Keyboard KEY;

#endif  // drv_keyboard_h
