#include "physics.h"
#include "game.h"
#include "clock.h"
#include "math.h"

#define CLIP_PADDING 0.001f;

void zPhysics_MovePlayer()
{
  int16_t worldW = WORLD_TILES_X * WORLD_TILE_SIZE;
  int16_t worldH = WORLD_TILES_Y * WORLD_TILE_SIZE;

  zVector2f_t newPosition;
  newPosition.x = zGame.playerHitBox.x + ( zGame.playerVelocity.x * zClock.frameSeconds );
  newPosition.y = zGame.playerHitBox.y + ( zGame.playerVelocity.y * zClock.frameSeconds );

  // clip to world boundaries
  if ( newPosition.x < 0 )
  {
    newPosition.x = 0;
  }
  else if ( newPosition.x + zGame.playerHitBox.w >= worldW )
  {
    newPosition.x = worldW - zGame.playerHitBox.w - 1;
  }

  if ( newPosition.y < 0 )
  {
    newPosition.y = 0;
  }
  else if ( newPosition.y + zGame.playerHitBox.h >= worldH )
  {
    newPosition.y = worldH - zGame.playerHitBox.h - 1;
  }

  // clip to unpassable tiles (horizontal first, then vertical)
  if ( newPosition.x != zGame.playerHitBox.x )
  {
    int tileRowStartIndex = zGame.playerHitBox.y / WORLD_TILE_SIZE;
    int tileRowEndIndex = ( zGame.playerHitBox.y + zGame.playerHitBox.h ) / WORLD_TILE_SIZE;

    if ( newPosition.x < zGame.playerHitBox.x )
    {
      // moving left, check leftward tiles
      int col = newPosition.x / WORLD_TILE_SIZE;

      for( int row = tileRowStartIndex; row <= tileRowEndIndex; row++ )
      {
        zWorldTile_t* tile = &( zGame.worldTiles[ zMath_WorldIndexFromCoords( row, col ) ] );

        if ( !tile->passable )
        {
          newPosition.x = ( ( col + 1 ) * WORLD_TILE_SIZE );
          break;
        }
      }
    }
    else
    {
      // moving right, check rightward tiles
      int col = ( newPosition.x + zGame.playerHitBox.w ) / WORLD_TILE_SIZE;

      for( int row = tileRowStartIndex; row <= tileRowEndIndex; row++ )
      {
        zWorldTile_t* tile = &( zGame.worldTiles[ zMath_WorldIndexFromCoords( row, col ) ] );

        if ( !tile->passable )
        {
          newPosition.x = ( col * WORLD_TILE_SIZE ) - zGame.playerHitBox.w - CLIP_PADDING;
          break;
        }
      }
    }
  }

  if ( newPosition.y != zGame.playerHitBox.y )
  {
    int tileColStartIndex = zGame.playerHitBox.x / WORLD_TILE_SIZE;
    int tileColEndIndex = ( zGame.playerHitBox.x + zGame.playerHitBox.w ) / WORLD_TILE_SIZE;

    if ( newPosition.y < zGame.playerHitBox.y )
    {
      // moving up, check upward tiles
      int row = newPosition.y / WORLD_TILE_SIZE;

      for( int col = tileColStartIndex; col <= tileColEndIndex; col++ )
      {
        zWorldTile_t* tile = &( zGame.worldTiles[ zMath_WorldIndexFromCoords( row, col ) ] );

        if ( !tile->passable )
        {
          newPosition.y = ( ( row + 1 ) * WORLD_TILE_SIZE );
          break;
        }
      }
    }
    else
    {
      // moving down, check downward tiles
      int row = ( newPosition.y + zGame.playerHitBox.h ) / WORLD_TILE_SIZE;

      for( int col = tileColStartIndex; col <= tileColEndIndex; col++ )
      {
        zWorldTile_t* tile = &( zGame.worldTiles[ zMath_WorldIndexFromCoords( row, col ) ] );

        if ( !tile->passable )
        {
          newPosition.y = ( row * WORLD_TILE_SIZE ) - zGame.playerHitBox.h - CLIP_PADDING;
          break;
        }
      }
    }
  }

  zGame.playerHitBox.x = newPosition.x;
  zGame.playerHitBox.y = newPosition.y;
}
