#if !defined( MATH_H )
#define MATH_H

#include "common.h"
#include "vector.h"

#if defined( __cplusplus )
extern "C" {
#endif

zBool zVector2i_Equals( zVector2i_t* v1, zVector2i_t* v2 );
zBool zVector4i_Equals( zVector4i_t* v1, zVector4i_t* v2 );
zBool zVector2f_Equals( zVector2f_t* v1, zVector2f_t* v2 );
zBool zVector4f_Equals( zVector4f_t* v1, zVector4f_t* v2 );

int zMath_WorldIndexFromCoords( int row, int col );

#if defined( __cplusplus )
}
#endif

#endif // MATH_H
