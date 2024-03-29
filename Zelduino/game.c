#include "game.h"
#include "clock.h"
#include "input_state.h"
#include "physics.h"
#include "player_sprite.h"

static void zGame_HandlePlayingStateInput();
static void zGame_HandleInventoryStateInput();
static void zGame_MovePlayer();

void zGame_Init()
{
  zGame_LoadData();

  // TODO: this should be part of data_loader.c at some point
  zGame.worldCoords.x = 1;
  zGame.worldCoords.y = 0;
  zGame_LoadWorldMap();

  zGame.playerHitBox.x = ( ( WORLD_TILES_X / 2 ) - 3 ) * WORLD_TILE_SIZE;
  zGame.playerHitBox.y = ( WORLD_TILES_Y / 2 ) * WORLD_TILE_SIZE;
  zGame.playerHitBox.w = 12;
  zGame.playerHitBox.h = 8;

  zGame.playerSpriteOffset.x = -2;
  zGame.playerSpriteOffset.y = -6;

  zGame.playerVelocity.x = 0;
  zGame.playerVelocity.y = 0;

  zPlayerSprite_Init();

  zRenderer_Init();
}

void zGame_Update()
{
  switch( zGame.state )
  {
    case zGameState_Loading:
      zGame.state = zGameState_Playing;
      break;
    case zGameState_Playing:
      zGame_HandlePlayingStateInput();
      zPhysics_MovePlayer();
      break;
    case zGameState_Inventory:
      zGame_HandleInventoryStateInput();
      break;
  }

  zGame.playerVelocity.x = 0;
  zGame.playerVelocity.y = 0;
}

// TODO: move this into an input handler file?
static void zGame_HandlePlayingStateInput()
{
  if ( zButtonStates[zButtonType_Start].pressed )
  {
    zGame.state = zGameState_Inventory;
    return;
  }

  zBool leftIsDown = zButtonStates[zButtonType_Left].down;
  zBool upIsDown = zButtonStates[zButtonType_Up].down;
  zBool rightIsDown = zButtonStates[zButtonType_Right].down;
  zBool downIsDown = zButtonStates[zButtonType_Down].down;

  if ( leftIsDown && !rightIsDown )
  {
    zGame.playerVelocity.x = -PLAYER_MAX_VELOCITY;

    if ( !( upIsDown && zPlayerSprite.direction == zDirection_Up ) &&
         !( downIsDown && zPlayerSprite.direction == zDirection_Down ) )
    {
      zPlayerSprite.direction = zDirection_Left;
    }

    if ( upIsDown || downIsDown )
    {
      zGame.playerVelocity.x *= 0.707;
    }
  }
  else if ( rightIsDown && !leftIsDown )
  {
    zGame.playerVelocity.x = PLAYER_MAX_VELOCITY;

    if ( !( upIsDown && zPlayerSprite.direction == zDirection_Up ) &&
         !( downIsDown && zPlayerSprite.direction == zDirection_Down ) )
    {
      zPlayerSprite.direction = zDirection_Right;
    }

    if ( upIsDown || downIsDown )
    {
      zGame.playerVelocity.x *= 0.707;
    }
  }

  if ( upIsDown && !downIsDown )
  {
    zGame.playerVelocity.y = -PLAYER_MAX_VELOCITY;

    if ( !( leftIsDown && zPlayerSprite.direction == zDirection_Left ) &&
         !( rightIsDown && zPlayerSprite.direction == zDirection_Right ) )
    {
      zPlayerSprite.direction = zDirection_Up;
    }

    if ( leftIsDown || rightIsDown )
    {
      zGame.playerVelocity.y *= 0.707;
    }
  }
  else if ( downIsDown && !upIsDown )
  {
    zGame.playerVelocity.y = PLAYER_MAX_VELOCITY;

    if ( !( leftIsDown && zPlayerSprite.direction == zDirection_Left ) &&
         !( rightIsDown && zPlayerSprite.direction == zDirection_Right ) )
    {
      zPlayerSprite.direction = zDirection_Down;
    }

    if ( leftIsDown || rightIsDown )
    {
      zGame.playerVelocity.y *= 0.707;
    }
  }
}

// TODO: move this to an input handler file?
static void zGame_HandleInventoryStateInput()
{
  if ( zButtonStates[zButtonType_Start].pressed )
  {
    zGame.state = zGameState_Playing;
    return;
  }
}
