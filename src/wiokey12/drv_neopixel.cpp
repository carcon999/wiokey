#include "arduino.h"
#include "drv_neopixel.h"
#include "def.h"

#define RGB32(r,g,b)  (((uint32_t)r << 16) | ((uint32_t)g <<  8) | b)

#define BR_LEVEL_MAX  (8)     // 明るさ変更レベル数
#define BR_DEFAULT    (3)     // 初期明るさレベル

uint32_t _buffer[MATRIX_Y][MATRIX_X];

const uint8_t led_map[MATRIX_Y][MATRIX_X] = {
#ifdef KEY_TYPE_12
  {11,10, 9, 8},
  { 4, 5, 6, 7},
  { 3, 2, 1, 0}    
#else
  {11,10, 9, 8, 23,22,21,20},
  { 7, 6, 5, 4, 19,18,17,16},
  { 3, 2, 1, 0, 15,14,13,12},    
#endif
};

const uint8_t _brTable[BR_LEVEL_MAX] = {128, 96, 80, 64, 48, 32, 24, 16};

// global instance
Neopixel LED;

static Adafruit_NeoPixel_ZeroDMA led(PIX_LEN, BCM10, NEO_RGB);

// 初期化処理を行う関数
// コンストラクタは　クラス名::クラス名と同じ名前で構成します
Neopixel::Neopixel()
{
}

void Neopixel::setPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b)
{
  _buffer[y][x] = RGB32(r,g,b);
}

void Neopixel::clear(void)
{
  for(int x = 0 ; x < MATRIX_X ; x++)
  {
    for(int y = 0 ; y < MATRIX_Y ; y++)
    {
      _buffer[y][x] = 0;
    }
  }
}

void Neopixel::draw(void)
{
  for(int x = 0 ; x < MATRIX_X ; x++)
  {
    for(int y = 0 ; y < MATRIX_Y ; y++)
    {
      uint8_t pos = led_map[y][x];
      if(pos >= 0){
        led.setPixelColor(pos, _buffer[y][x]);
      }
    }
  }
  
  led.show();
}

void Neopixel::setup(uint8_t numPixels, uint8_t pin, neoPixelType t)
{
  led.setPin(pin);
  led.updateLength(numPixels);
  led.updateType(t);
  led.begin();

  clear();
  setBright(BR_DEFAULT);
}

// 明るさの変更
// 色テーブルを変更する。
void Neopixel::setBright(int level)
{
  int tmp = _br_level;
  tmp += level;
  if(tmp < 0){
    tmp += BR_LEVEL_MAX;
  }else if(tmp >= BR_LEVEL_MAX){
    tmp -= BR_LEVEL_MAX;
  }
  
  _br_level = (uint8_t)tmp;
  _br_level &= (BR_LEVEL_MAX - 1);

  led.setBrightness(_brTable[_br_level]);
  draw();
}
