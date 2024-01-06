#if !defined( GAME_H )
#define GAME_H

#include "common.h"
#include "game_state.h"
#include "vector.h"

typedef struct zWorldTile_t
{
  uint8_t textureIndex;
}
zWorldTile_t;

typedef struct zCollisionTile_t
{
  zBool passable;
}
zCollisionTile_t;

typedef struct zGame_t
{
  // TODO: should this stuff be in renderer.h? or graphics.h or something?
  uint16_t palette[PALETTE_COLORS];
  
  uint8_t worldTextureMap[( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_SIZE * WORLD_TILE_TEXTURES];
  uint8_t playerTextureMap[( PLAYER_SPRITE_SIZE / 2 ) * PLAYER_SPRITE_SIZE * PLAYER_SPRITE_FRAMES * 4];

  zWorldTile_t worldTiles[WORLD_TILES_X * WORLD_TILES_Y];
  zCollisionTile_t collisionTiles[COLLISION_TILES_X * COLLISION_TILES_Y];

  zVector2ui_t worldCoords;

  zGameState_t state;

  zVector4f_t playerHitBox;
  zVector2f_t playerSpriteOffset;
  zVector2f_t playerVelocity;
}
zGame_t;

zGame_t zGame;

#if defined( __cplusplus )
extern "C" {
#endif

void zGame_LoadData();
void zGame_Init();
void zGame_Update();

#if defined( __cplusplus )
}
#endif

#endif // GAME_H
