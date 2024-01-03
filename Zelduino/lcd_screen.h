#if !defined( LCD_SCREEN_H )
#define LCD_SCREEN_H

#include "common.h"

#define LCD_MODEL 0x9486

// LCD controller chip identifiers
#define ID_9486 5

//LCD controller chip mode identifiers
#define ILI9486 6

typedef struct zWorldTile_t zWorldTile_t;

typedef struct zLcdScreen_t
{
  uint16_t width;
  uint16_t height;
  uint16_t rotation;
  uint16_t lcd_driver;

  volatile uint8_t* csPort;
  volatile uint8_t* cdPort;
  volatile uint8_t* wrPort;
  volatile uint8_t* rdPort;

	uint8_t csPinSet;
  uint8_t cdPinSet;
  uint8_t wrPinSet;
  uint8_t rdPinSet;
  uint8_t csPinUnset;
  uint8_t cdPinUnset;
  uint8_t wrPinUnset;
  uint8_t rdPinUnset;

  uint16_t XC;
  uint16_t YC;
  uint16_t CC;
  uint16_t RC;
  uint16_t SC1;
  uint16_t SC2;
  uint16_t MD;
  uint16_t VL;
  uint16_t R24BIT;
}
zLcdScreen_t;

zLcdScreen_t zLcdScreen;

#if defined( __cplusplus )
extern "C" {
#endif

void zLcdScreen_Init( uint8_t cs, uint8_t cd, uint8_t wr, uint8_t rd, uint8_t reset );
void zLcdScreen_FillRect( int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color );
void zLcdScreen_DrawWorldTile( zWorldTile_t* tile, int16_t x, int16_t y );

#if defined( __cplusplus )
}
#endif

#endif // LCD_SCREEN_H
