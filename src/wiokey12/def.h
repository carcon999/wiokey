/*
 * def.h
 * 
 * 
 */
#ifndef def_h
#define def_h

// Serial LEDs (WS2812 Series)
#define PIXEL_PIN   BCM10

// 12Keyの場合は下記を定義し、24keyの場合はコメントアウトする。
#define KEY_TYPE_12

#ifdef KEY_TYPE_12
  #define MATRIX_Y          (3)
  #define MATRIX_X          (4)
#else
  #define MATRIX_Y          (3)
  #define MATRIX_X          (8)
#endif

#define NUMBER_OF_KEYS    (MATRIX_X*MATRIX_Y)
#define PIX_LEN           (NUMBER_OF_KEYS)

#define IMAGE_WIDTH   (80)
#define IMAGE_HEIGHT  (80)

#define DISP_WIDTH    (320)
#define DISP_HEIGHT   (240)

#define LAYER_MAX     (2)

#endif  // def_h
