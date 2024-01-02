#include "common.h"
#include "lcd_screen.h"
#include "mcu_8bit_magic.h"
#include "lcd_registers.h"
#include "game.h"

#define TFTLCD_DELAY8 0x7F
#define MAX_REG_NUM   24

static uint16_t zLcdScreen_ReadId();
static uint16_t zLcdScreen_ReadReg( uint16_t reg, int8_t index );
static void zLcdScreen_PushCommand( uint16_t cmd, uint8_t* block, int8_t N );
static void zLcdScreen_Start();
static void zLcdScreen_InitTable8( const void *table, int16_t size );
static void zLcdScreen_SetRotation( uint8_t r );
static void zLcdScreen_SetAddrWindow( int16_t x1, int16_t y1, int16_t x2, int16_t y2 );
static void zLcdScreen_VertScroll( int16_t top, int16_t scrollines, int16_t offset );
static void zLcdScreen_InvertDisplay( bool i );

void zLcdScreen_Init( uint8_t cs, uint8_t cd, uint8_t wr, uint8_t rd, uint8_t reset )
{
	zLcdScreen.csPort = portOutputRegister( digitalPinToPort( cs ) );
	zLcdScreen.cdPort = portOutputRegister( digitalPinToPort( cd ) );
	zLcdScreen.wrPort = portOutputRegister( digitalPinToPort( wr ) );
	zLcdScreen.rdPort = portOutputRegister( digitalPinToPort( rd ) );

  zLcdScreen.csPinSet = digitalPinToBitMask( cs );
  zLcdScreen.cdPinSet = digitalPinToBitMask( cd );
  zLcdScreen.wrPinSet = digitalPinToBitMask( wr );
  zLcdScreen.rdPinSet = digitalPinToBitMask( rd );
  zLcdScreen.csPinUnset = ~( zLcdScreen.csPinSet );
  zLcdScreen.cdPinUnset = ~( zLcdScreen.cdPinSet );
  zLcdScreen.wrPinUnset = ~( zLcdScreen.wrPinSet );
  zLcdScreen.rdPinUnset = ~( zLcdScreen.rdPinSet );

	*( zLcdScreen.csPort ) |= zLcdScreen.csPinSet; // Set all control bits to HIGH (idle)
	*( zLcdScreen.cdPort ) |= zLcdScreen.cdPinSet; // Signals are ACTIVE LOW
	*( zLcdScreen.wrPort ) |= zLcdScreen.wrPinSet;
	*( zLcdScreen.rdPort ) |= zLcdScreen.rdPinSet;

  pinMode( cs, OUTPUT );	  // Enable outputs
  pinMode( cd, OUTPUT );
  pinMode( wr, OUTPUT );
  pinMode( rd, OUTPUT );

  if( reset ) 
  {
	  digitalWrite( reset, HIGH );
	  pinMode( reset, OUTPUT );
  }

 	zLcdScreen.rotation = 0;
  
  setWriteDir();

 	zLcdScreen.width = SCREEN_WIDTH;
	zLcdScreen.height = SCREEN_HEIGHT;

  CS_IDLE;
  RD_IDLE;
  WR_IDLE;

  if( reset ) 
  {
    digitalWrite( reset, LOW );
    delay( 2 );
    digitalWrite( reset, HIGH );
  }

  CS_ACTIVE;
  CD_COMMAND;
  write8( 0x00 );

  for( uint8_t i = 0; i < 3; i++ )
  {
  	WR_STROBE; // Three extra 0x00s
  }

  CS_IDLE;

	zLcdScreen_Start();
}

void zLcdScreen_FillRect( int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color )
{
  int16_t end = x + w;

  // X boundaries

  if ( x < 0 )
  {
      x = 0;
  }

  if ( end > SCREEN_WIDTH )
  {
      end = SCREEN_WIDTH;
  }

  w = end - x;

  // Y boundaries

  end = y + h;

  if ( y < 0 )
  {
      y = 0;
  }

  if ( end > SCREEN_HEIGHT )
  {
      end = SCREEN_HEIGHT;
  }

  h = end - y;

  // render

  zLcdScreen_SetAddrWindow( x, y, x + w - 1, y + h - 1 );
	CS_ACTIVE;

	writeCmd8( zLcdScreen.CC );

	if ( h > w )
	{
      end = h;
      h = w;
      w = end;
  }

	while ( h-- > 0 )
	{
		end = w;
		do
		{
      writeData16( color );
    }
    while ( --end != 0 );
	}

	CS_IDLE;
}

void zLcdScreen_DrawWorldTile( zWorldTile_t* tile, int16_t x, int16_t y )
{
  zLcdScreen_SetAddrWindow( x, y, x + WORLD_TILE_SIZE - 1, y + WORLD_TILE_SIZE - 1 );

	CS_ACTIVE;

	writeCmd8( zLcdScreen.CC );

  int textureOffset = tile->textureIndex * ( WORLD_TILE_SIZE / 2 );

  for( int16_t h = 0; h < WORLD_TILE_SIZE; h++ )
  {
    for( uint16_t textureCol = textureOffset; textureCol < textureOffset + ( WORLD_TILE_SIZE / 2 ); textureCol++ )
    {
      uint8_t texturePair = zGame.textureMap[( h * ( ( WORLD_TILE_SIZE / 2 ) * WORLD_TILE_TEXTURES ) ) + textureCol];

      writeData16( zGame.palette[texturePair >> 2] );
      writeData16( zGame.palette[texturePair & 0x3] );
    }
  }

	CS_IDLE;
}

static uint16_t zLcdScreen_ReadReg( uint16_t reg, int8_t index )
{
	uint16_t ret, high;
  uint8_t low;

	CS_ACTIVE;
  writeCmd16( reg );
  setReadDir();
  delay( 1 );

	do 
	{
		read16( ret );
	}
  while ( --index >= 0 );

  CS_IDLE;
  setWriteDir();

  return ret;
}

static void zLcdScreen_PushCommand( uint16_t cmd, uint8_t* block, int8_t N )
{
  CS_ACTIVE;
  writeCmd16( cmd );

  while ( N-- > 0 ) 
	{
    uint8_t u8 = *block++;
    writeData8( u8 );
  }

  CS_IDLE;
}

static void zLcdScreen_Start()
{
	delay( 200 );

	zLcdScreen.lcd_driver = ID_9486;

	zLcdScreen.XC=ILI9341_COLADDRSET;
  zLcdScreen.YC=ILI9341_PAGEADDRSET;
  zLcdScreen.CC=ILI9341_MEMORYWRITE;
  zLcdScreen.RC=HX8357_RAMRD;
  zLcdScreen.SC1=0x33;
  zLcdScreen.SC2=0x37;
  zLcdScreen.MD=ILI9341_MADCTL;
  zLcdScreen.VL=0;
  zLcdScreen.R24BIT=0;

  static const uint8_t ILI9486_regValues[] PROGMEM = 
  {
    0xF1, 6, 0x36, 0x04, 0x00, 0x3C, 0x0F, 0x8F,
    0xF2, 9, 0x18, 0xA3, 0x12, 0x02, 0xB2, 0x12, 0xFF, 0x10, 0x00, 
    0xF8, 2, 0x21, 0x04,
    0xF9, 2, 0x00, 0x08,
    0x36, 1, 0x08, 
    0xB4, 1, 0x00,
    0xC1, 1, 0x41,
    0xC5, 4, 0x00, 0x91, 0x80, 0x00,
    0xE0, 15, 0x0F, 0x1F, 0x1C, 0x0C, 0x0F, 0x08, 0x48, 0x98, 0x37, 0x0A, 0x13, 0x04, 0x11, 0x0D, 0x00,
    0xE1, 15, 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75, 0x37, 0x06, 0x10 ,0x03, 0x24, 0x20, 0x00,				
    0x3A, 1, 0x55,
    0x11,0,
    0x36, 1, 0x28,
    TFTLCD_DELAY8, 120,
    0x29,0
  };

  zLcdScreen_InitTable8( ILI9486_regValues, sizeof( ILI9486_regValues ) );
 	zLcdScreen_SetRotation( zLcdScreen.rotation );
 	zLcdScreen_InvertDisplay( false );
}

static void zLcdScreen_InitTable8( const void *table, int16_t size )
{
	uint8_t i;
  uint8_t *p = (uint8_t*)table, dat[MAX_REG_NUM]; // R61526 has GAMMA[22] 

  while ( size > 0 ) 
	{
    uint8_t cmd = pgm_read_byte( p++ );
    uint8_t len = pgm_read_byte( p++ );

    if ( cmd == TFTLCD_DELAY8 )
		{
      delay( len );
      len = 0;
    } 
		else 
		{
      for ( i = 0; i < len; i++ )
      {
        dat[i] = pgm_read_byte( p++ );
      }

			zLcdScreen_PushCommand( cmd, dat, len );
    }

    size -= len + 2;
  }
}

static void zLcdScreen_SetRotation( uint8_t r )
{
  zLcdScreen.rotation = r & 3;
  zLcdScreen.width = ( zLcdScreen.rotation & 1 ) ? SCREEN_HEIGHT : SCREEN_WIDTH;
  zLcdScreen.height = ( zLcdScreen.rotation & 1 ) ? SCREEN_WIDTH : SCREEN_HEIGHT;
	CS_ACTIVE;

  uint8_t val;

	switch ( zLcdScreen.rotation )
  {
    case 0:
      val = ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR; //0 degree 
      break;
    case 1:
      val = ILI9341_MADCTL_MV | ILI9341_MADCTL_ML | ILI9341_MADCTL_BGR ; //90 degree 
      break;
    case 2:
      val = ILI9341_MADCTL_MY |ILI9341_MADCTL_BGR; //180 degree 
      break;
    case 3:
      val = ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR; //270 degree
      break;
  }

	writeCmdData8( zLcdScreen.MD, val );

  zLcdScreen_SetAddrWindow( 0, 0, zLcdScreen.width - 1, zLcdScreen.height - 1 );
	zLcdScreen_VertScroll( 0, SCREEN_HEIGHT, 0 );
	CS_IDLE;
}

static void zLcdScreen_SetAddrWindow( int16_t x1, int16_t y1, int16_t x2, int16_t y2 )
{
	CS_ACTIVE;

  uint8_t x_buf[] = { x1 >> 8, x1 & 0xFF, x2 >> 8, x2 & 0xFF };
  uint8_t y_buf[] = { y1 >> 8, y1 & 0xFF, y2 >> 8, y2 & 0xFF };

  zLcdScreen_PushCommand( zLcdScreen.XC, x_buf, 4);
  zLcdScreen_PushCommand( zLcdScreen.YC, y_buf, 4);

	CS_IDLE;		
}

static void zLcdScreen_VertScroll( int16_t top, int16_t scrollines, int16_t offset )
{
  int16_t bfa = SCREEN_HEIGHT - top - scrollines;
  int16_t vsp;
  int16_t sea = top;

  if ( offset <= -scrollines || offset >= scrollines )
  {
    offset = 0;
  }

	vsp = top + offset;

  if ( offset < 0 )
  {
    vsp += scrollines;
  }

  sea = top + scrollines - 1;

  uint8_t d[6];           // for multi-byte parameters

  d[0] = top >> 8;        //TFA
  d[1] = top;
  d[2] = scrollines >> 8; //VSA
  d[3] = scrollines;
  d[4] = bfa >> 8;        //BFA
  d[5] = bfa;

  zLcdScreen_PushCommand( zLcdScreen.SC1, d, 6 );

  d[0] = vsp >> 8;        //VSP
  d[1] = vsp;

  zLcdScreen_PushCommand( zLcdScreen.SC2, d, 2 );

  if ( offset == 0 )
  {
    zLcdScreen_PushCommand( 0x13, NULL, 0 );
  }
}

static void zLcdScreen_InvertDisplay( bool i )
{
	CS_ACTIVE;
	uint8_t val = zLcdScreen.VL ^ i;
	writeCmd8( val ? 0x21 : 0x20 );
	CS_IDLE;
}
