// This is also a program for checking the operation of the WioTerminal Switch 12/24 switch.

#include <Adafruit_NeoPixel_ZeroDMA.h>

// When using with 24key, comment out the following one line.
// 24keyの場合は下記をコメントアウトする。
#define KEY_TYPE_12

#ifdef KEY_TYPE_12
#define NUMBER_OF_KEYS 12
#define ALL_BIT    0x00000FFF
#else
#define NUMBER_OF_KEYS 24
#define ALL_BIT    0x00FFFFFF
#endif

#define PIN        BCM10
#define NUM_PIXELS NUMBER_OF_KEYS

const uint8_t pins[NUMBER_OF_KEYS] = 
{
#ifdef KEY_TYPE_12
BCM23, BCM24, BCM25, BCM8,
BCM2,  BCM3,  BCM4,  BCM17,
BCM27, BCM22, BCM9,  BCM11

#else
BCM12, BCM16, BCM20, BCM21,
BCM7 , BCM1,  BCM19, BCM26,
BCM0,  BCM5,  BCM6,  BCM13,
BCM23, BCM24, BCM25, BCM8,
BCM2,  BCM3 , BCM4,  BCM17,
BCM27, BCM22, BCM9,  BCM11,
#endif
};

Adafruit_NeoPixel_ZeroDMA strip(NUM_PIXELS, PIN, NEO_GRB);
static uint32_t all_flag;

void setup() {
  strip.begin();
  strip.setBrightness(32);
  strip.show();

  for (uint8_t i=0; i<NUMBER_OF_KEYS; i++)
  {
    pinMode(pins[i], INPUT_PULLUP);
  }
}

void loop() 
{
  for(int i = 0 ; i < NUMBER_OF_KEYS ; i++)
  {
    if ( 0 == digitalRead(pins[i]))
    {
      all_flag |= (0x1 << i);
      strip.setPixelColor(i, 0xFF0000);
      strip.show();
      delay(100);
    }
  }

  if(all_flag == ALL_BIT)
  {
    // Rainbow cycle
    uint32_t elapsed, t, startTime = micros();
    for(;;) 
    {
      t       = micros();
      elapsed = t - startTime;
      if(elapsed > 5000000) break; // Run for 5 seconds
      uint32_t firstPixelHue = elapsed / 32;
      for(int i=0; i<strip.numPixels(); i++) {
        uint32_t pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      }
      strip.show();
    }
    // clear
    all_flag = 0;
    for(int i = 0 ; i < NUMBER_OF_KEYS ; i++)
    {
      strip.setPixelColor(i, 0);
    }
    strip.show();
  }
}
