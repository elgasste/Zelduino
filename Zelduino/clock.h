#if !defined( CLOCK_H )
#define CLOCK_H

#include "common.h"

typedef struct zClock_t
{
  unsigned long frameStartMicro;
  unsigned long frameMicro;
  unsigned long totalFrameCount;
  unsigned long lagFrameCount;
  float frameSeconds;
}
zClock_t;

zClock_t zClock;

#if defined( __cplusplus )
extern "C" {
#endif

void zClock_Init();
void zClock_StartFrame();
void zClock_EndFrame();

#if defined( __cplusplus )
}
#endif

#endif // CLOCK_H
