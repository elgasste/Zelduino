#if !defined( VECTOR_H )
#define VECTOR_H

#include "common.h"

typedef struct zVector2i_t
{
  int16_t x;
  int16_t y;
}
zVector2i_t;

typedef struct zVector2ui_t
{
  uint16_t x;
  uint16_t y;
}
zVector2ui_t;

typedef struct zVector4i_t
{
  int16_t x;
  int16_t y;
  int16_t w;
  int16_t h;
}
zVector4i_t;

typedef struct zVector2f_t
{
  float x;
  float y;
}
zVector2f_t;

typedef struct zVector4f_t
{
  float x;
  float y;
  float w;
  float h;
}
zVector4f_t;

#endif // VECTOR_H
