#include <limits.h>

#include "clock.h"

void zClock_Init()
{
  zClock.frameStartMicro = 0;
  zClock.frameMicro = 1000000 / GAME_FPS;
  zClock.frameSeconds = 1.0f / GAME_FPS;
  zClock.totalFrameCount = 0;
  zClock.lagFrameCount = 0;
}

void zClock_StartFrame()
{
  zClock.frameStartMicro = micros();
}

void zClock_EndFrame()
{
  unsigned long frameEndMicro = micros();
  unsigned long elapsedMicro;

  if ( frameEndMicro < zClock.frameStartMicro )
  {
    // this means the timer has overflowed (happens after ~70 mins)
    elapsedMicro = frameEndMicro + ( ULONG_MAX - zClock.frameStartMicro );
  }
  else
  {
    elapsedMicro = frameEndMicro - zClock.frameStartMicro;
  }

  if ( elapsedMicro <= zClock.frameMicro )
  {
    // I'd like to use delayMicroseconds here, but there are some serious
    // issues with precision. regular "delay" works much better, strangely.
    delay( ( zClock.frameMicro - elapsedMicro ) / 1000 );
  }
  else
  {
    zClock.lagFrameCount++;
  }

  zClock.totalFrameCount++;
}
