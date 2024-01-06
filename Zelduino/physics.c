#include "physics.h"
#include "game.h"
#include "clock.h"
#include "math.h"

#define CLIP_PADDING 0.001f;

void zPhysics_MovePlayer()
{
  int16_t worldW = COLLISION_TILES_X * COLLISION_TILE_SIZE;
  int16_t worldH = COLLISION_TILES_Y * COLLISION_TILE_SIZE;

  zVector2f_t newPosition;
  newPosition.x = zGame.playerHitBox.x + ( zGame.playerVelocity.x * zClock.frameSeconds );
  newPosition.y = zGame.playerHitBox.y + ( zGame.playerVelocity.y * zClock.frameSeconds );

  float distanceX = newPosition.x - zGame.playerHitBox.x;
  float distanceY = newPosition.y - zGame.playerHitBox.y;

  if ( distanceX < 0 )
  {
    distanceX = -distanceX;
  }
  if ( distanceY < 0 )
  {
    distanceY = -distanceY;
  }

  zPlayerSprite_Tic( distanceX + distanceY );

  // check world boundaries
  if ( newPosition.x < 0 )
  {
    zGame.worldCoords.x--;
    zGame.playerHitBox.x = worldW - zGame.playerHitBox.w - 1;
    zGame_LoadWorldMap();
    return;
  }
  else if ( newPosition.x + zGame.playerHitBox.w >= worldW )
  {
    zGame.worldCoords.x++;
    zGame.playerHitBox.x = CLIP_PADDING;
    zGame_LoadWorldMap();
    return;
  }

  if ( newPosition.y < 0 )
  {
    zGame.worldCoords.y--;
    zGame.playerHitBox.y = worldH - zGame.playerHitBox.h - 1;
    zGame_LoadWorldMap();
    return;
  }
  else if ( newPosition.y + zGame.playerHitBox.h >= worldH )
  {
    zGame.worldCoords.y++;
    zGame.playerHitBox.y = CLIP_PADDING;
    zGame_LoadWorldMap();
    return;
  }

  // clip to unpassable tiles (horizontal first, then vertical)
  if ( newPosition.x != zGame.playerHitBox.x )
  {
    int tileRowStartIndex = zGame.playerHitBox.y / COLLISION_TILE_SIZE;
    int tileRowEndIndex = ( zGame.playerHitBox.y + zGame.playerHitBox.h ) / COLLISION_TILE_SIZE;

    if ( newPosition.x < zGame.playerHitBox.x )
    {
      // moving left, check leftward tiles
      int col = newPosition.x / COLLISION_TILE_SIZE;

      for( int row = tileRowStartIndex; row <= tileRowEndIndex; row++ )
      {
        zCollisionTile_t* tile = &( zGame.collisionTiles[ zMath_CollisionIndexFromCoords( row, col ) ] );

        if ( !tile->passable )
        {
          newPosition.x = ( ( col + 1 ) * COLLISION_TILE_SIZE );
          break;
        }
      }
    }
    else
    {
      // moving right, check rightward tiles
      int col = ( newPosition.x + zGame.playerHitBox.w ) / COLLISION_TILE_SIZE;

      for( int row = tileRowStartIndex; row <= tileRowEndIndex; row++ )
      {
        zCollisionTile_t* tile = &( zGame.collisionTiles[ zMath_CollisionIndexFromCoords( row, col ) ] );

        if ( !tile->passable )
        {
          newPosition.x = ( col * COLLISION_TILE_SIZE ) - zGame.playerHitBox.w - CLIP_PADDING;
          break;
        }
      }
    }
  }

  if ( newPosition.y != zGame.playerHitBox.y )
  {
    int tileColStartIndex = zGame.playerHitBox.x / COLLISION_TILE_SIZE;
    int tileColEndIndex = ( zGame.playerHitBox.x + zGame.playerHitBox.w ) / COLLISION_TILE_SIZE;

    if ( newPosition.y < zGame.playerHitBox.y )
    {
      // moving up, check upward tiles
      int row = newPosition.y / COLLISION_TILE_SIZE;

      for( int col = tileColStartIndex; col <= tileColEndIndex; col++ )
      {
        zCollisionTile_t* tile = &( zGame.collisionTiles[ zMath_CollisionIndexFromCoords( row, col ) ] );

        if ( !tile->passable )
        {
          newPosition.y = ( ( row + 1 ) * COLLISION_TILE_SIZE );
          break;
        }
      }
    }
    else
    {
      // moving down, check downward tiles
      int row = ( newPosition.y + zGame.playerHitBox.h ) / COLLISION_TILE_SIZE;

      for( int col = tileColStartIndex; col <= tileColEndIndex; col++ )
      {
        zCollisionTile_t* tile = &( zGame.collisionTiles[ zMath_CollisionIndexFromCoords( row, col ) ] );

        if ( !tile->passable )
        {
          newPosition.y = ( row * COLLISION_TILE_SIZE ) - zGame.playerHitBox.h - CLIP_PADDING;
          break;
        }
      }
    }
  }

  zGame.playerHitBox.x = newPosition.x;
  zGame.playerHitBox.y = newPosition.y;
}
