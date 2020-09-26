/*
 * drv_lcd.h
 * 
 * 
 */
#ifndef drv_lcd_h
#define drv_lcd_h

// クラスの定義
// クラス名・コンストラクタ名・関数名や使用する変数名を定義します。
class Lcd
{
  public:
    Lcd();
    void setup(void);
    void draw_png(const uint8_t* p, const int sz, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

  private:

};

extern Lcd LCD;

#endif  // drv_lcd_h
