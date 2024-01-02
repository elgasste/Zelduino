#if !defined( GAME_H )
#define GAME_H

#include "common.h"
#include "game_state.h"
#include "vector.h"

typedef struct zWorldTile_t
{
  uint8_t textureIndex;
  zBool passable;
}
zWorldTile_t;

typedef struct zGame_t
{
  zGameState_t state;

  uint16_t palette[PALETTE_COLORS];
  uint8_t textureMap[( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_SIZE * WORLD_TILE_TEXTURES];

  zWorldTile_t worldTiles[WORLD_TILES_X * WORLD_TILES_Y];

  zVector4f_t playerHitBox;
  zVector2f_t playerVelocity;
}
zGame_t;

zGame_t zGame;

#if defined( __cplusplus )
extern "C" {
#endif

void zGame_Init();
void zGame_Update();

#if defined( __cplusplus )
}
#endif

#endif // GAME_H
