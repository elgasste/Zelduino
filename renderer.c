#include "renderer.h"
#include "lcd_screen.h"
#include "game.h"
#include "math.h"

static void zRenderer_RenderLoadingState();
static void zRenderer_RenderPlayingState();
static void zRenderer_RedrawDirtyTiles();

void zRenderer_Init()
{
  zLcdScreen_Init( A3, A2, A1, A0, A4 );

  zRenderer.worldScreenOffset.x = WORLD_OFFSET_X;
  zRenderer.worldScreenOffset.y = WORLD_OFFSET_Y;

  zRenderer.drawWorldBackdrop = zTrue;

  zRenderer.wipeColor = 0x0000;
  zRenderer.playerColor = 0x001F; // blue

  // TODO: this should probably be done somewhere else, when we get loading working properly.
  zLcdScreen_FillRect( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, zRenderer.wipeColor );
}

void zRenderer_Render()
{
  switch( zGame.state )
  {
    case zGameState_Loading:
      zRenderer_RenderLoadingState();
      break;
    case zGameState_Playing:
      zRenderer_RenderPlayingState();
      break;
  }
}

static void zRenderer_RenderLoadingState()
{
  // TODO: this will never get called with our current logic
}

static void zRenderer_RenderPlayingState()
{
  // this is VERY slow, so only do it when absolutely necessary
  if ( zRenderer.drawWorldBackdrop )
  {
    zRenderer.drawWorldBackdrop = zFalse;

    for( int row = 0; row < WORLD_TILES_Y; row++ )
    {
      for( int col = 0; col < WORLD_TILES_X; col++ )
      {
        zLcdScreen_DrawWorldTile( &( zGame.worldTiles[zMath_WorldIndexFromCoords( row, col )] ),
                                  zRenderer.worldScreenOffset.x + ( col * WORLD_TILE_SIZE ),
                                  zRenderer.worldScreenOffset.y + ( row * WORLD_TILE_SIZE ) );
      }
    }
  }

  if ( !zVector4i_Equals( &zRenderer.playerHitBoxCache, &zGame.playerHitBox ) )
  {
    // cover up the player's previous position
    zRenderer_RedrawDirtyTiles();

    // now draw the player at the new position
    zLcdScreen_FillRect( zRenderer.worldScreenOffset.x + zGame.playerHitBox.x,
                         zRenderer.worldScreenOffset.y + zGame.playerHitBox.y,
                         zGame.playerHitBox.w,
                         zGame.playerHitBox.h,
                         zRenderer.playerColor );

    zRenderer.playerHitBoxCache = zGame.playerHitBox;
  }
}

static void zRenderer_RedrawDirtyTiles()
{
  // TODO: maybe at some point try doing something more efficient than this. we can figure out
  // exactly which rects are dirty and only draw those, it'd probably be faster than drawing every dirty tile.
  int tileColIndexStart = zRenderer.playerHitBoxCache.x / WORLD_TILE_SIZE;
  int tileColIndexEnd = ( zRenderer.playerHitBoxCache.x + zRenderer.playerHitBoxCache.w ) / WORLD_TILE_SIZE;
  int tileRowIndexStart = zRenderer.playerHitBoxCache.y / WORLD_TILE_SIZE;
  int tileRowIndexEnd = ( zRenderer.playerHitBoxCache.y + zRenderer.playerHitBoxCache.h ) / WORLD_TILE_SIZE;

  for( int row = tileRowIndexStart; row <= tileRowIndexEnd; row++ )
  {
    for( int col = tileColIndexStart; col <= tileColIndexEnd; col++ )
    {
      zLcdScreen_DrawWorldTile( &( zGame.worldTiles[zMath_WorldIndexFromCoords( row, col )] ),
                                zRenderer.worldScreenOffset.x + ( col * WORLD_TILE_SIZE ),
                                zRenderer.worldScreenOffset.y + ( row * WORLD_TILE_SIZE ) );
    }
  }
}
