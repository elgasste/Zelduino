#if !defined( INPUT_STATE_H )
#define INPUT_STATE_H

#include "common.h"

typedef enum zButtonType_t
{
  zButtonType_Left = 0,
  zButtonType_Up,
  zButtonType_Right,
  zButtonType_Down,
  zButtonType_Select,
  zButtonType_Start,
  zButtonType_A,
  zButtonType_B,

  zButtonType_Count
}
zButtonType_t;

typedef struct zButtonState_t
{
  zBool pressed;
  zBool released;
  zBool down;
}
zButtonState_t;

zButtonState_t zButtonStates[zButtonType_Count];

#endif // INPUT_STATE_H
