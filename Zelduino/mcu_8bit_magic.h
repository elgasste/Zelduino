#if !defined( MCU_8BIT_MAGIC_H )
#define MCU_8BIT_MAGIC_H

#define EMASK         0x38
#define GMASK         0x20
#define HMASK         0x78

#define write8( d ) { \
	PORTH &= ~HMASK; \
  PORTH |= ( ( d& ( 0x03 << 6 ) ) >> 3 ) | ( ( d & 0x03 ) << 5 ); \
  PORTE &= ~EMASK; \
  PORTE |= ( ( d & ( 0x03 << 2 ) ) << 2 ) | ( ( d & ( 0x01 << 5 ) ) >> 2 ); \
  PORTG &= ~GMASK; \
  PORTG |= ( d & ( 0x01 << 4 ) ) << 1; WR_STROBE; \
}

#define setWriteDir() { DDRH |= HMASK; DDRE |= EMASK;DDRG |= GMASK; }

 // When using the TFT breakout board, control pins are configurable.
 #define RD_ACTIVE  *( zLcdScreen.rdPort ) &= zLcdScreen.rdPinUnset
 #define RD_IDLE    *( zLcdScreen.rdPort ) |= zLcdScreen.rdPinSet
 #define WR_ACTIVE  *( zLcdScreen.wrPort ) &= zLcdScreen.wrPinUnset
 #define WR_IDLE    *( zLcdScreen.wrPort ) |= zLcdScreen.wrPinSet
 #define CD_COMMAND *( zLcdScreen.cdPort ) &= zLcdScreen.cdPinUnset
 #define CD_DATA    *( zLcdScreen.cdPort ) |= zLcdScreen.cdPinSet
 #define CS_ACTIVE  *( zLcdScreen.csPort ) &= zLcdScreen.csPinUnset
 #define CS_IDLE    *( zLcdScreen.csPort ) |= zLcdScreen.csPinSet

// Data write strobe, ~2 instructions and always inline
#define WR_STROBE { WR_ACTIVE; WR_IDLE; }
#define RD_STROBE {RD_IDLE; RD_ACTIVE; RD_ACTIVE;RD_ACTIVE; }
#define write16( d ) { uint8_t h = ( d ) >> 8, l = d; write8( h ); write8( l ); }
#define read16( dst ) { uint8_t hi; read8( hi ); read8( dst ); dst |= ( hi << 8 ); }
#define writeCmd8( x ) { CD_COMMAND; write8( x ); CD_DATA; }
#define writeData8( x ) {  write8( x ) }
#define writeCmd16( x ) { CD_COMMAND; write16( x ); CD_DATA; }
#define writeData16( x ) { write16( x ) }

// These higher-level operations are usually functionalized,
// except on Mega where's there's gobs and gobs of program space.

// Set value of TFT register: 8-bit address, 8-bit value
#define writeCmdData8( a, d ) { CD_COMMAND; write8( a ); CD_DATA; write8( d ); }

// Set value of TFT register: 16-bit address, 16-bit value
// See notes at top about macro expansion, hence hi & lo temp vars
#define writeCmdData16( a, d ) { \
  uint8_t hi, lo; \
  hi = ( a ) >> 8; lo = ( a ); CD_COMMAND; write8( hi ); write8( lo ); \
  hi = ( d ) >> 8; lo = ( d ); CD_DATA   ; write8( hi ); write8( lo ); }

#endif // MCU_8BIT_MAGIC_H
