#include "player_sprite.h"

void zPlayerSprite_Init()
{
  zPlayerSprite.currentFrame = 0;
  zPlayerSprite.direction = zDirection_Up;
  zPlayerSprite.distanceElapsed = 0;
}

void zPlayerSprite_Tic( float distance )
{
  zPlayerSprite.distanceElapsed += distance;

  // MUFFINS: is this calculation wrong? what's going on here??
  while ( zPlayerSprite.distanceElapsed >= PLAYER_SPRITE_SWAP_DISTANCE )
  {
    zPlayerSprite.currentFrame++;

    if ( zPlayerSprite.currentFrame >= PLAYER_SPRITE_FRAMES )
    {
      zPlayerSprite.currentFrame = 0;
    }

    zPlayerSprite.distanceElapsed -= PLAYER_SPRITE_SWAP_DISTANCE;
  }
}
