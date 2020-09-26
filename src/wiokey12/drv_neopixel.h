/*
 * drv_neopixel.h
 * 
 * 
 */
#ifndef drv_neopixel_h
#define drv_neopixel_h

#include <Adafruit_NeoPixel_ZeroDMA.h>

// クラスの定義
// クラス名・コンストラクタ名・関数名や使用する変数名を定義します。
class Neopixel
{
  public:
    Neopixel();
    void setup(uint8_t numPixels, uint8_t pin, neoPixelType t=NEO_RGB + NEO_KHZ800);
    
    void setBright(int level);
    void clear(void);
    void draw(void);
    void setPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);

  private:
    uint8_t _br_level;    // 明るさレベル
};

extern Neopixel LED;

#endif  // drv_neopixel.h
