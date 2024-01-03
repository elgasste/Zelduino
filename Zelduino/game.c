#include "game.h"
#include "clock.h"
#include "input_state.h"
#include "physics.h"

static void zGame_HandlePlayingStateInput();
static void zGame_MovePlayer();

void zGame_Init()
{
  zGame_LoadData();

  zGame.playerHitBox.x = ( WORLD_TILES_X / 2 ) * WORLD_TILE_SIZE;
  zGame.playerHitBox.y = ( WORLD_TILES_Y / 2 ) * WORLD_TILE_SIZE;
  zGame.playerHitBox.w = 12;
  zGame.playerHitBox.h = 12;

  zGame.playerVelocity.x = 0;
  zGame.playerVelocity.y = 0;

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
  }

  zGame.playerVelocity.x = 0;
  zGame.playerVelocity.y = 0;
}

// TODO: move this into an input handler file?
static void zGame_HandlePlayingStateInput()
{
  zBool leftIsDown = zButtonStates[zButtonType_Left].down;
  zBool upIsDown = zButtonStates[zButtonType_Up].down;
  zBool rightIsDown = zButtonStates[zButtonType_Right].down;
  zBool downIsDown = zButtonStates[zButtonType_Down].down;

  if ( leftIsDown && !rightIsDown )
  {
    zGame.playerVelocity.x = -PLAYER_MAX_VELOCITY;

    if ( upIsDown || downIsDown )
    {
      zGame.playerVelocity.x *= 0.707;
    }
  }
  else if ( rightIsDown && !leftIsDown )
  {
    zGame.playerVelocity.x = PLAYER_MAX_VELOCITY;

    if ( upIsDown || downIsDown )
    {
      zGame.playerVelocity.x *= 0.707;
    }
  }

  if ( upIsDown && !downIsDown )
  {
    zGame.playerVelocity.y = -PLAYER_MAX_VELOCITY;

    if ( leftIsDown || rightIsDown )
    {
      zGame.playerVelocity.y *= 0.707;
    }
  }
  else if ( downIsDown && !upIsDown )
  {
    zGame.playerVelocity.y = PLAYER_MAX_VELOCITY;

    if ( leftIsDown || rightIsDown )
    {
      zGame.playerVelocity.y *= 0.707;
    }
  }
}
