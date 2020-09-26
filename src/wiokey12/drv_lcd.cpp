#include "arduino.h"
#include "drv_lcd.h"
#include <LGFX_TFT_eSPI.hpp>
#include "def.h"

static TFT_eSPI tft;               // TFT_eSPIがLGFXの別名として定義されます。
//static TFT_eSprite sprite(&tft); // TFT_eSpriteがLGFX_Spriteの別名として定義されます。

Lcd LCD;

Lcd::Lcd()
{
}

void Lcd::setup()
{
  tft.init();
  tft.setRotation(3);

  //sprite.setColorDepth(8);
  //sprite.createSprite(320, 240);
  //sprite.setTextFont(2);
  //sprite.fillScreen(TFT_BLACK);
  //sprite.pushSprite(0, 0);
}

void Lcd::draw_png(const uint8_t* p, const int sz, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  //if(x < DISP_WIDTH && y < DISP_HEIGHT)
  {
    if(p != NULL){
      tft.drawPng(p, sz, x, y, w, h);  
    }else{
      tft.fillRect( x, y, w, h, 0);
    }  
  }
}
