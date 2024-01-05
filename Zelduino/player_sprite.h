#if !defined( PLAYER_SPRITE_H )
#define PLAYER_SPRITE_H

#include "common.h"
#include "direction.h"

typedef struct zPlayerSprite_t
{
  zDirection_t direction;
  uint8_t currentFrame;
  float distanceElapsed;
}
zPlayerSprite_t;

zPlayerSprite_t zPlayerSprite;

#if defined( __cplusplus )
extern "C" {
#endif

void zPlayerSprite_Init();
void zPlayerSprite_Tic( float distance );

#if defined( _cplusplus )
}
#endif

#endif // PLAYER_SPRITE_H
