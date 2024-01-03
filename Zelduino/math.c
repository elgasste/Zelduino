#include "math.h"

zBool zVector2i_Equals( zVector2i_t* v1, zVector2i_t* v2 )
{
  return ( v1->x == v2->x && v1->y == v2->y ) ? zTrue : zFalse;
}

zBool zVector4i_Equals( zVector4i_t* v1, zVector4i_t* v2 )
{
  return ( v1->x == v2->x && v1->y == v2->y && v1->w == v2->w && v1->h == v2->h ) ? zTrue : zFalse;
}

zBool zVector2f_Equals( zVector2f_t* v1, zVector2f_t* v2 )
{
  return ( v1->x == v2->x && v1->y == v2->y ) ? zTrue : zFalse;
}

zBool zVector4f_Equals( zVector4f_t* v1, zVector4f_t* v2 )
{
  return ( v1->x == v2->x && v1->y == v2->y && v1->w == v2->w && v1->h == v2->h ) ? zTrue : zFalse;
}

int zMath_WorldIndexFromCoords( int row, int col )
{
  return ( row * WORLD_TILES_X ) + col;
}
