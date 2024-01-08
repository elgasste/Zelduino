#if !defined( RENDERER_H )
#define RENDERER_H

#include "common.h"
#include "vector.h"
#include "game_state.h"

typedef struct zRenderer_t
{
  zVector2i_t worldScreenOffset;

  uint16_t wipeColor;
  uint16_t playerColor;

  zGameState_t gameStateCache;
  zVector2ui_t worldCoordsCache;
  zVector4f_t playerHitBoxCache;
}
zRenderer_t;

zRenderer_t zRenderer;

#if defined( __cplusplus )
extern "C" {
#endif

void zRenderer_Init();
void zRenderer_Render();

#if defined( __cplusplus )
}
#endif

#endif // RENDERER_H
