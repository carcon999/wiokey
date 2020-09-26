#include "arduino.h"
#include "drv_keyboard.h"
#include "Adafruit_TinyUSB.h"

// ******************************************************************
// USB Key
// ******************************************************************
// HID report descriptor using TinyUSB's template
// Single Report (no ID) descriptor
uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_KEYBOARD(),
};

Adafruit_USBD_HID usb_hid;

// global instance
Keyboard KEY;

// Array of pins and its keycode
// https://github.com/platformio/platformio-pkg-framework-arduinosam/blob/master/cores/adafruit/Adafruit_TinyUSB_Core/tinyusb/src/class/hid/hid.h
// 接続端子定義
const uint8_t pins[NUMBER_OF_KEYS] = 
{
#ifdef KEY_TYPE_12
// 24     23     22     21
   BCM11, BCM9,  BCM22, BCM27,
// 20     19     18     17
  BCM17, BCM4,  BCM3,  BCM2,
// 16     15     14     13
  BCM8,  BCM25, BCM24, BCM23

#else
// 12     11     10     9      24     23     22     21
   BCM13, BCM6,  BCM5,  BCM0,  BCM11, BCM9,  BCM22, BCM27,
// 8      7      6      5      20     19     18     17
   BCM26, BCM19, BCM1,  BCM7,  BCM17, BCM4,  BCM3,  BCM2,
// 4      3      2      1      16     15     14     13
   BCM21, BCM20, BCM16, BCM12, BCM8,  BCM25, BCM24, BCM23
#endif
};

// 初期化処理を行う関数
// コンストラクタは　クラス名::クラス名と同じ名前で構成します
Keyboard::Keyboard()
{
}

void Keyboard::report(uint32_t current, uint32_t before)
{
  // 今回送信なしで前回送信有の場合は、停止コマンド
  if(current == 0 && before)
  {
    usb_hid.keyboardRelease(0);
  }
  // フラグに応じてデータを送信しておく。
  else
  {
    static uint8_t buff[6];
    for (int8_t i = NUMBER_OF_KEYS - 1; i >= 0; i--)
    {
      current >>= 1;
      if(current & 0x0001)
      {
        buff[0] = keycode[i];
        usb_hid.keyboardReport(0, modifiers[i], buff);
      }
    }
  }
}

void Keyboard::setup(void)
{
  // Set up pin as input 12 keys
  for (uint8_t i=0; i<NUMBER_OF_KEYS; i++)
  {
    pinMode(pins[i], INPUT_PULLUP);
  }

  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.begin();
  
  // wait until device mounted
  while( !USBDevice.mounted() ) delay(1);
}

void Keyboard::setkeycode(int x, int y, uint8_t modifier, uint8_t code)
{
  int id = y*MATRIX_X + x;
  keycode[id] = code;
  modifiers[id] = modifier;
}

void Keyboard::loop(void)
{
  static uint32_t tm;

  if ( !usb_hid.ready() ) return;

  // スキャン周期がタイムアウトしている場合のみ
  if(tm > millis()) return;

  // 次のスキャンは、20ms後
  tm = millis() + 20;

  // 12bitのキー押下状態を作成する。
  uint32_t current_keyflags = 0;

  for(int i = 0 ; i < NUMBER_OF_KEYS ; i++)
  {
    if ( 0 == digitalRead(pins[i]) && (keycode[i] != 0x00) )
    {
      current_keyflags |= 1;
    }
    current_keyflags <<= 1;
  }

  // 前回のスキャン状態と変化があれば、送信する。
  if(before_keyflags != current_keyflags)
  {
    report(current_keyflags, before_keyflags);
    before_keyflags = current_keyflags;
  }
  else
  {
    // 同じキーの状態はリピート状態として特に処理しない。
  }
}
