#include "game.h"
#include "clock.h"
#include "input_state.h"
#include "physics.h"
#include "math.h"

static void zGame_HandlePlayingStateInput();
static void zGame_MovePlayer();
static void zGame_LoadPalette();
static void zGame_LoadWorldTileTextures();
static void zGame_LoadWorld();

void zGame_Init()
{
  zGame_LoadPalette();
  zGame_LoadWorldTileTextures();
  zGame_LoadWorld();

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

static void zGame_LoadPalette()
{
  // NOTE: colors are set up a little strange here, the left 5 bits are R,
  // the next 5 bits are G, and then it seems to skip one bit, so the last
  // 5 bits are B. I'm not sure that's totally accurate, but it seems like it.
  zGame.palette[0] = 0x0000;    // black
  zGame.palette[1] = 0xFE93;    // ground cream
  zGame.palette[2] = 0x4D02;    // rock green
  zGame.palette[3] = 0x9700;    // link green
  zGame.palette[4] = 0xBB80;    // link brown
  zGame.palette[5] = 0xFCC0;    // link skin
  zGame.palette[6] = 0x0000;
  zGame.palette[7] = 0x0000;
  zGame.palette[8] = 0x0000;
  zGame.palette[9] = 0x0000;
  zGame.palette[10] = 0x0000;
  zGame.palette[11] = 0x0000;
  zGame.palette[12] = 0x0000;
  zGame.palette[13] = 0x0000;
  zGame.palette[14] = 0x0000;
  zGame.palette[15] = 0x0000;   // reserved for transparent pixels
}

static void zGame_LoadWorldTileTextures()
{
  // NOTE: each uint8_t is split into two palette indexes
  
  // index 0: ground
  for( int row = 0; row < WORLD_TILE_SIZE; row++ )
  {
    for( int col = 0; col < ( WORLD_TILE_SIZE / 2 ); col++ )
    {
      int i = ( row * ( ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES ) ) + col;
      zGame.textureMap[i] = 0x5; // packed index 1 (ground cream)
    }
  }

  // index 1: rocks
  int rowThing = 0;                                             // row 0
  zGame.textureMap[8 + rowThing]  = 0xA; // green, green
  zGame.textureMap[9 + rowThing]  = 0x8; // green, black
  zGame.textureMap[10 + rowThing] = 0x4; // cream, black
  zGame.textureMap[11 + rowThing] = 0x1; // black, cream
  zGame.textureMap[12 + rowThing] = 0xA; // green, green
  zGame.textureMap[13 + rowThing] = 0x0; // black, black
  zGame.textureMap[14 + rowThing] = 0x4; // cream, black
  zGame.textureMap[15 + rowThing] = 0xA; // green, green
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 1
  zGame.textureMap[8 + rowThing]  = 0xA; // green, green
  zGame.textureMap[9 + rowThing]  = 0xA; // green, green
  zGame.textureMap[10 + rowThing] = 0x0; // black, black
  zGame.textureMap[11 + rowThing] = 0x6; // cream, green
  zGame.textureMap[12 + rowThing] = 0xA; // green, green
  zGame.textureMap[13 + rowThing] = 0xA; // green, green
  zGame.textureMap[14 + rowThing] = 0x0; // black, black
  zGame.textureMap[15 + rowThing] = 0x1; // black, cream
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 2
  zGame.textureMap[8 + rowThing]  = 0xA; // green, green
  zGame.textureMap[9 + rowThing]  = 0xA; // green, green
  zGame.textureMap[10 + rowThing] = 0x0; // black, black
  zGame.textureMap[11 + rowThing] = 0x6; // cream, green
  zGame.textureMap[12 + rowThing] = 0xA; // green, green
  zGame.textureMap[13 + rowThing] = 0xA; // green, green
  zGame.textureMap[14 + rowThing] = 0x0; // black, black
  zGame.textureMap[15 + rowThing] = 0x8; // green, black
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 3
  zGame.textureMap[8 + rowThing]  = 0x6; // cream, green
  zGame.textureMap[9 + rowThing]  = 0xA; // green, green
  zGame.textureMap[10 + rowThing] = 0x0; // black, black
  zGame.textureMap[11 + rowThing] = 0x6; // cream, green
  zGame.textureMap[12 + rowThing] = 0xA; // green, green
  zGame.textureMap[13 + rowThing] = 0xA; // green, green
  zGame.textureMap[14 + rowThing] = 0x8; // green, black
  zGame.textureMap[15 + rowThing] = 0x8; // green, black
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 4
  zGame.textureMap[8 + rowThing]  = 0x6; // cream, green
  zGame.textureMap[9 + rowThing]  = 0xA; // green, green
  zGame.textureMap[10 + rowThing] = 0x1; // black, cream
  zGame.textureMap[11 + rowThing] = 0xA; // green, green
  zGame.textureMap[12 + rowThing] = 0xA; // green, green
  zGame.textureMap[13 + rowThing] = 0xA; // green, green
  zGame.textureMap[14 + rowThing] = 0x8; // green, black
  zGame.textureMap[15 + rowThing] = 0x8; // green, black
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 5
  zGame.textureMap[8 + rowThing]  = 0xA; // green, green
  zGame.textureMap[9 + rowThing]  = 0xA; // green, green
  zGame.textureMap[10 + rowThing] = 0x1; // black, cream
  zGame.textureMap[11 + rowThing] = 0xA; // green, green
  zGame.textureMap[12 + rowThing] = 0xA; // green, green
  zGame.textureMap[13 + rowThing] = 0xA; // green, green
  zGame.textureMap[14 + rowThing] = 0xA; // green, green
  zGame.textureMap[15 + rowThing] = 0x8; // green, black
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 6
  zGame.textureMap[8 + rowThing]  = 0xA; // green, green
  zGame.textureMap[9 + rowThing]  = 0xA; // green, green
  zGame.textureMap[10 + rowThing] = 0x1; // black, cream
  zGame.textureMap[11 + rowThing] = 0xA; // green, green
  zGame.textureMap[12 + rowThing] = 0xA; // green, green
  zGame.textureMap[13 + rowThing] = 0x9; // green, cream
  zGame.textureMap[14 + rowThing] = 0x4; // cream, black
  zGame.textureMap[15 + rowThing] = 0x1; // black, cream
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 7
  zGame.textureMap[8 + rowThing]  = 0xA; // green, green
  zGame.textureMap[9 + rowThing]  = 0xA; // green, green
  zGame.textureMap[10 + rowThing] = 0x1; // black, cream
  zGame.textureMap[11 + rowThing] = 0xA; // green, green
  zGame.textureMap[12 + rowThing] = 0xA; // green, green
  zGame.textureMap[13 + rowThing] = 0x6; // cream, green
  zGame.textureMap[14 + rowThing] = 0xA; // green, green
  zGame.textureMap[15 + rowThing] = 0x1; // black, cream
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 8
  zGame.textureMap[8 + rowThing]  = 0xA; // green, green
  zGame.textureMap[9 + rowThing]  = 0x8; // green, black
  zGame.textureMap[10 + rowThing] = 0x1; // black, cream
  zGame.textureMap[11 + rowThing] = 0xA; // green, green
  zGame.textureMap[12 + rowThing] = 0xA; // green, green
  zGame.textureMap[13 + rowThing] = 0x6; // cream, green
  zGame.textureMap[14 + rowThing] = 0xA; // green, green
  zGame.textureMap[15 + rowThing] = 0x8; // green, black
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 9
  zGame.textureMap[8 + rowThing]  = 0xA; // green, green
  zGame.textureMap[9 + rowThing]  = 0x8; // green, black
  zGame.textureMap[10 + rowThing] = 0x1; // black, cream
  zGame.textureMap[11 + rowThing] = 0xA; // green, green
  zGame.textureMap[12 + rowThing] = 0xA; // green, green
  zGame.textureMap[13 + rowThing] = 0x6; // cream, green
  zGame.textureMap[14 + rowThing] = 0xA; // green, green
  zGame.textureMap[15 + rowThing] = 0x8; // green, black
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 10
  zGame.textureMap[8 + rowThing]  = 0x6; // cream, green
  zGame.textureMap[9 + rowThing]  = 0x0; // black, black
  zGame.textureMap[10 + rowThing] = 0x1; // black, cream
  zGame.textureMap[11 + rowThing] = 0x2; // black, green
  zGame.textureMap[12 + rowThing] = 0x8; // green, black
  zGame.textureMap[13 + rowThing] = 0x6; // cream, green
  zGame.textureMap[14 + rowThing] = 0xA; // green, green
  zGame.textureMap[15 + rowThing] = 0x0; // black, black
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 11
  zGame.textureMap[8 + rowThing]  = 0x6; // cream, green
  zGame.textureMap[9 + rowThing]  = 0x1; // black, cream
  zGame.textureMap[10 + rowThing] = 0x5; // cream, cream
  zGame.textureMap[11 + rowThing] = 0x0; // black, black
  zGame.textureMap[12 + rowThing] = 0x8; // green, black
  zGame.textureMap[13 + rowThing] = 0x6; // cream, green
  zGame.textureMap[14 + rowThing] = 0xA; // green, green
  zGame.textureMap[15 + rowThing] = 0x1; // black, cream
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 12
  zGame.textureMap[8 + rowThing]  = 0x8; // green, black
  zGame.textureMap[9 + rowThing]  = 0x6; // cream, green
  zGame.textureMap[10 + rowThing] = 0xA; // green, green
  zGame.textureMap[11 + rowThing] = 0xA; // green, green
  zGame.textureMap[12 + rowThing] = 0x0; // black, black
  zGame.textureMap[13 + rowThing] = 0x6; // cream, green
  zGame.textureMap[14 + rowThing] = 0xA; // green, green
  zGame.textureMap[15 + rowThing] = 0x1; // black, cream
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 13
  zGame.textureMap[8 + rowThing]  = 0x8; // green, black
  zGame.textureMap[9 + rowThing]  = 0x6; // cream, green
  zGame.textureMap[10 + rowThing] = 0xA; // green, green
  zGame.textureMap[11 + rowThing] = 0x8; // green, black
  zGame.textureMap[12 + rowThing] = 0x0; // black, black
  zGame.textureMap[13 + rowThing] = 0x6; // cream, green
  zGame.textureMap[14 + rowThing] = 0xA; // green, green
  zGame.textureMap[15 + rowThing] = 0x1; // black, cream
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 14
  zGame.textureMap[8 + rowThing]  = 0x9; // green, cream
  zGame.textureMap[9 + rowThing]  = 0xA; // green, green
  zGame.textureMap[10 + rowThing] = 0xA; // green, green
  zGame.textureMap[11 + rowThing] = 0xA; // green, green
  zGame.textureMap[12 + rowThing] = 0x0; // black, black
  zGame.textureMap[13 + rowThing] = 0x2; // black, green
  zGame.textureMap[14 + rowThing] = 0x8; // green, black
  zGame.textureMap[15 + rowThing] = 0x0; // black, black
  rowThing += ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES;    // row 15
  zGame.textureMap[8 + rowThing]  = 0x1; // black, cream
  zGame.textureMap[9 + rowThing]  = 0x9; // green, cream
  zGame.textureMap[10 + rowThing] = 0xA; // green, green
  zGame.textureMap[11 + rowThing] = 0x4; // cream, black
  zGame.textureMap[12 + rowThing] = 0x4; // cream, black
  zGame.textureMap[13 + rowThing] = 0x1; // black, cream
  zGame.textureMap[14 + rowThing] = 0x4; // cream, black
  zGame.textureMap[15 + rowThing] = 0x1; // black, cream
}

// TODO: move this into some kind of game loader source file
static void zGame_LoadWorld()
{
  for( int i = 0; i < WORLD_TILES_X * WORLD_TILES_Y; i++ )
  {
    zGame.worldTiles[i].textureIndex = 0;
    zGame.worldTiles[i].passable = zTrue;
  }

  // upper and lower walls
  for( int i = 0; i < WORLD_TILES_X; i++ )
  {
    zGame.worldTiles[i].textureIndex = 1;
    zGame.worldTiles[i].passable = zFalse;
  }
  for( int i = ( WORLD_TILES_X * WORLD_TILES_Y ) - WORLD_TILES_X; i < WORLD_TILES_X * WORLD_TILES_Y; i++ )
  {
    zGame.worldTiles[i].textureIndex = 1;
    zGame.worldTiles[i].passable = zFalse;
  }

  // left and right walls
  for( int i = 1; i < WORLD_TILES_Y - 1; i++ )
  {
    zGame.worldTiles[i * WORLD_TILES_X].textureIndex = 1;
    zGame.worldTiles[i * WORLD_TILES_X].passable = zFalse;
    zGame.worldTiles[( i * WORLD_TILES_X ) + ( WORLD_TILES_X - 1 )].textureIndex = 1;
    zGame.worldTiles[( i * WORLD_TILES_X ) + ( WORLD_TILES_X - 1 )].passable = zFalse;
  }
}
