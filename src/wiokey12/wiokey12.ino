/*********************************************************************
 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 Copyright (c) 2019 Ha Thach for Adafruit Industries
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/
#include "drv_neopixel.h"
#include "drv_keyboard.h"
#include "drv_lcd.h"
#include "keymap.h"

static uint8_t layer = 0;

void setup_neopixel()
{
  LED.setup(PIX_LEN, PIXEL_PIN);
  LED.draw();

  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);

  pinMode(WIO_5S_UP, INPUT);
  pinMode(WIO_5S_DOWN, INPUT); 
}

void display_next(void)
{
  layer += 1;
  layer &= (LAYER_MAX - 1);
  
  const KEYMAP* p;

  // キーボードのキー割り当て
  //　LEDの変更
  for(int i = 0 ; i < NUMBER_OF_KEYS ; i++)
  {
    p = &tKeyMap[layer][i];
    KEY.setkeycode(p->x, p->y, p->modifiers, p->keycode);
    LED.setPixel(p->x, p->y, p->r, p->g, p->b);
  }
  // LED電源供給ON
  led_power(HIGH);
  LED.draw();

  // ディスプレイの描画
  for(int i = 0 ; i < NUMBER_OF_KEYS ; i++)
  {
    p = &tKeyMap[layer][i];
    LCD.draw_png(p->pimg, p->sz, p->x * IMAGE_WIDTH, p->y * IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT);
  }
}

void led_power(uint8_t val)
{
  digitalWrite(OUTPUT_CTR_5V, val);  
}

// the setup function runs once when you press reset or power the board
void setup()
{
  // 5V Power OFF
  pinMode(OUTPUT_CTR_5V, OUTPUT);
  led_power(LOW);

  // LEDの初期化
  setup_neopixel();  

  // 電源投入後早い段階でHID接続が必要
  KEY.setup();

  // LCDの初期化
  LCD.setup();

  // 初期画面の表示
  layer = LAYER_MAX - 1;
  display_next();  
}

void loop()
{
  if ( 0 == digitalRead(BUTTON_1))
  {
  }
  else if(0 == digitalRead(BUTTON_2))
  {
  }
  else if(0 == digitalRead(BUTTON_3))
  {
    display_next();
  }
  else if(0 == digitalRead(WIO_5S_UP))
  {
    LED.setBright(1);
    delay(500);
  }else if(0 == digitalRead(WIO_5S_DOWN)){
    LED.setBright(-1);
    delay(500);
  }

  KEY.loop();
}
