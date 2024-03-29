#if !defined( COMMON_H )
#define COMMON_H

#include <Arduino.h>

#define SCREEN_WIDTH        320
#define SCREEN_HEIGHT       480

#define PIN_ANALOG_X        A9
#define PIN_ANALOG_Y        A8

#define PIN_SELECT_BUTTON   52
#define PIN_START_BUTTON    50
#define PIN_A_BUTTON        46
#define PIN_B_BUTTON        48

#define GAME_FPS            30

#define PALETTE_COLORS      16
#define TRANSPARENT_COLOR   0xF81F

#define TEXT_TILE_SIZE      8
#define TEXT_TILES          36

#define WORLD_TILE_SIZE     16
#define WORLD_TILES_X       16
#define WORLD_TILES_Y       11
#define WORLD_TILE_TEXTURES 9   // TODO: can we inject this automatically?

#define COLLISION_TILE_SIZE 8
#define COLLISION_TILES_X   32
#define COLLISION_TILES_Y   22

#define WORLD_OFFSET_X      32
#define WORLD_OFFSET_Y      64

#define PLAYER_SPRITE_SIZE            16
#define PLAYER_SPRITE_FRAMES          2
#define PLAYER_SPRITE_SWAP_DISTANCE   16.0f

#define PLAYER_MAX_VELOCITY 70 // pixels per second

#if !defined( HIGH )
#define HIGH 0x1
#endif

#if !defined( LOW )
#define LOW 0x0
#endif

typedef int8_t zBool;
#define zTrue 1
#define zFalse 0

#endif // COMMON_H
