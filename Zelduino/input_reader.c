#include "common.h"
#include "input_reader.h"

// the analog stick ranges from 0 to 1024
#define ANALOG_THRESHOLD_LOW 200
#define ANALOG_THRESHOLD_HIGH 824

static void zInputReader_UpdateButtonState( zButtonState_t* buttonState, zBool down );

void zInputReader_Init()
{
  pinMode( PIN_SELECT_BUTTON, INPUT_PULLUP );
  pinMode( PIN_START_BUTTON, INPUT_PULLUP );
  pinMode( PIN_A_BUTTON, INPUT_PULLUP );
  pinMode( PIN_B_BUTTON, INPUT_PULLUP );

  for( int i = 0; i < zButtonType_Count; i++ )
  {
    zButtonStates[i].pressed = zFalse;
    zButtonStates[i].released = zFalse;
    zButtonStates[i].down = zFalse;
  }
}

void zInputReader_ReadInput()
{
  int xValue = analogRead( PIN_ANALOG_X );
  int yValue = analogRead( PIN_ANALOG_Y );

  zInputReader_UpdateButtonState( &( zButtonStates[zButtonType_Left ] ), xValue > ANALOG_THRESHOLD_HIGH );
  zInputReader_UpdateButtonState( &( zButtonStates[zButtonType_Up ] ), yValue < ANALOG_THRESHOLD_LOW );
  zInputReader_UpdateButtonState( &( zButtonStates[zButtonType_Right ] ), xValue < ANALOG_THRESHOLD_LOW );
  zInputReader_UpdateButtonState( &( zButtonStates[zButtonType_Down ] ), yValue > ANALOG_THRESHOLD_HIGH );

  zInputReader_UpdateButtonState( &( zButtonStates[zButtonType_Select] ), digitalRead( PIN_SELECT_BUTTON ) == LOW );
  zInputReader_UpdateButtonState( &( zButtonStates[zButtonType_Start] ), digitalRead( PIN_START_BUTTON ) == LOW );
  zInputReader_UpdateButtonState( &( zButtonStates[zButtonType_A] ), digitalRead( PIN_A_BUTTON ) == LOW );
  zInputReader_UpdateButtonState( &( zButtonStates[zButtonType_B] ), digitalRead( PIN_B_BUTTON ) == LOW );
}

static void zInputReader_UpdateButtonState( zButtonState_t* buttonState, zBool down )
{
  if ( down )
  {
    buttonState->released = zFalse;
    buttonState->pressed = buttonState->down ? zFalse : zTrue;
  }
  else
  {
    buttonState->pressed = zFalse;
    buttonState->released = buttonState->down ? zTrue : zFalse;
  }

  buttonState->down = down;
}
